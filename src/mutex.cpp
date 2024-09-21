#include "obsc/debug.h"
#include "obsc/mutex.h"

namespace obsc {

Mutex::~Mutex()
{
    PRINTLN("Dropping the mutex");
    if (handle != nullptr) {
        CloseHandle(handle);
    }
}

std::unique_ptr<Mutex> Mutex::create(const std::string& name)
{
    HANDLE handle = CreateMutexA(nullptr, FALSE, name.c_str());
    if (handle == nullptr) {
        PRINTLN("Failed to create mutex ({}, 0x{:x})", name, GetLastError());
        return nullptr;
    }
    
    PRINTLN("Created the mutex {} = 0x{:x}", name, reinterpret_cast<uintptr_t>(handle));
    return std::unique_ptr<Mutex>(new Mutex(handle));
}

}  // namespace obsc