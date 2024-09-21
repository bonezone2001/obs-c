/**
 * @file mutex.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief Light wrapper around the Windows mutex object.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once

#include <windows.h>
#include <string>
#include <memory>

#include "obsc/obsc_export.hpp"

namespace obsc {

class OBSC_EXPORT Mutex {
private:
    HANDLE handle;
    explicit Mutex(HANDLE handle)
        : handle(handle) {}

public:
    ~Mutex();

    static std::unique_ptr<Mutex> create(const std::string& name);
};

}  // namespace obsc