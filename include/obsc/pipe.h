/**
 * @file pipe.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief The named pipes implementation.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once
#include <string>
#include <thread>
#include <windows.h>

#include "obsc/obsc_export.hpp"

namespace obsc {

class OBSC_EXPORT NamedPipe {
private:
    HANDLE handle = INVALID_HANDLE_VALUE;
    std::thread thread;
    std::shared_ptr<std::atomic<bool>> threadRunning;

public:
    static std::unique_ptr<NamedPipe> create(const std::string& name);
    ~NamedPipe();

private:
    NamedPipe(HANDLE handle, std::thread&& thread, std::shared_ptr<std::atomic<bool>> threadRunning);

    static SECURITY_DESCRIPTOR createFullAccessSecurityDescriptor();
    static HANDLE createPipe(const std::string& name);
    static bool waitForConnection(HANDLE pipeHandle, HANDLE eventHandle, OVERLAPPED& overlap);
    static bool ioPending();
};

} // namespace obsc