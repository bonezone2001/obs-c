#include <stdexcept>
#include <vector>

#include "obsc/debug.h"
#include "obsc/event.h"
#include "obsc/pipe.h"

namespace obsc {

constexpr DWORD IPC_PIPE_BUFFER_SIZE = 1024;

std::unique_ptr<NamedPipe> NamedPipe::create(const std::string& name)
{
    HANDLE pipeHandle = createPipe(name);
    auto threadRunning = std::make_shared<std::atomic<bool>>(true);

    std::thread thread([pipeHandle, threadRunning]() {
        OVERLAPPED overlap = {0};
        Event readyEvent = Event::create();

        if (!waitForConnection(pipeHandle, readyEvent.getHandle(), overlap)) {
            PRINTLN("Failed to wait for connection");
            return;
        }

        if (WaitForSingleObject(readyEvent.getHandle(), INFINITE) != WAIT_OBJECT_0) {
            PRINTLN("Wait for connection failed");
            return;
        }

        std::vector<char> buffer;
        buffer.reserve(IPC_PIPE_BUFFER_SIZE);
        char temp[IPC_PIPE_BUFFER_SIZE];

        while (threadRunning->load(std::memory_order_relaxed)) {
            DWORD bytesRead = 0;
            if (!ReadFile(pipeHandle, temp, IPC_PIPE_BUFFER_SIZE, NULL, &overlap) && !ioPending()) {
                PRINTLN("ReadFile failed");
                break;
            }

            if (WaitForSingleObject(readyEvent.getHandle(), INFINITE) != WAIT_OBJECT_0) {
                PRINTLN("WaitForSingleObject failed");
                break;
            }

            if (!GetOverlappedResult(pipeHandle, &overlap, &bytesRead, TRUE) || bytesRead == 0) {
                PRINTLN("GetOverlappedResult failed");
                break;
            }

            buffer.insert(buffer.end(), temp, temp + bytesRead);

            PRINTLN("[pipe] {}", std::string(buffer.begin(), buffer.end()));
            buffer.clear();
        }
    });

    return std::unique_ptr<NamedPipe>(new NamedPipe(pipeHandle, std::move(thread), threadRunning));
}

NamedPipe::NamedPipe(HANDLE handle, std::thread&& thread, std::shared_ptr<std::atomic<bool>> threadRunning)
    : handle(handle), thread(std::move(thread)), threadRunning(threadRunning) {}

NamedPipe::~NamedPipe() {
    threadRunning->store(false, std::memory_order_relaxed);

    if (handle != INVALID_HANDLE_VALUE)
        CloseHandle(handle);

    if (thread.joinable())
        thread.join();
}

SECURITY_DESCRIPTOR NamedPipe::createFullAccessSecurityDescriptor()
{
    SECURITY_DESCRIPTOR sd;
    if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
        throw std::runtime_error("Failed to initialize security descriptor");

    if (!SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE))
        throw std::runtime_error("Failed to set security descriptor DACL");

    return sd;
}

HANDLE NamedPipe::createPipe(const std::string& name)
{
    SECURITY_DESCRIPTOR sd = createFullAccessSecurityDescriptor();

    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = &sd;
    sa.bInheritHandle = FALSE;

    std::string pipeName = fmt::format("\\\\.\\pipe\\{}1", name);
    HANDLE handle = CreateNamedPipeA(
        pipeName.c_str(),
        PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        IPC_PIPE_BUFFER_SIZE,
        IPC_PIPE_BUFFER_SIZE,
        0,
        &sa
    );

    if (handle == INVALID_HANDLE_VALUE) {
        throw std::runtime_error(fmt::format("Failed to create named pipe: {}", GetLastError()));
    }

    return handle;
}

bool NamedPipe::waitForConnection(HANDLE pipeHandle,
                                  HANDLE eventHandle,
                                  OVERLAPPED& overlap)
{
    ZeroMemory(&overlap, sizeof(OVERLAPPED));
    overlap.hEvent = eventHandle;

    if (!ConnectNamedPipe(pipeHandle, &overlap) && !ioPending()) {
        return false;
    }

    return true;
}

bool NamedPipe::ioPending()
{
    return GetLastError() == ERROR_IO_PENDING;
}


}  // namespace obsc