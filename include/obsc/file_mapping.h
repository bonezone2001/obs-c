/**
 * @file obsc.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief The file mapping implementation.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once
#include <windows.h>
#include <memory>

#include "obsc/obsc_export.hpp"

namespace obsc {

template<typename T>
class OBSC_EXPORT FileMapping {
private:
    HANDLE handle;
    T* fileMapping;
    
    FileMapping(HANDLE handle, T* fileMapping)
        : handle(handle), fileMapping(fileMapping) {}

public:
    ~FileMapping() {
        PRINTLN("Dropping the file mapping");
        UnmapViewOfFile(fileMapping);
        CloseHandle(handle);
    }

    static FileMapping<T> open(const std::string& name)
    {
        HANDLE handle = OpenFileMappingA((FILE_MAP_READ | FILE_MAP_WRITE), FALSE, name.c_str());
        if (handle == NULL)
            throw std::runtime_error(fmt::format("Failed to open file mapping {}, 0x{:x}", name, GetLastError()));

        T* fileMapping = static_cast<T*>(MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(T)));
        if (fileMapping == nullptr) {
            CloseHandle(handle);
            throw std::runtime_error(fmt::format("Failed to map view of file {}, 0x{:x}", name, GetLastError()));
        }

        PRINTLN("Created the file mapping for {} = 0x{:x}, 0x{:x}", 
                name, reinterpret_cast<uintptr_t>(handle), reinterpret_cast<uintptr_t>(fileMapping));

        return FileMapping<T>(handle, fileMapping);
    }

    T* operator->() { return fileMapping; }
    const T* operator->() const { return fileMapping; }

    T& operator*() { return *fileMapping; }
    const T& operator*() const { return *fileMapping; }
};

} // namespace obsc