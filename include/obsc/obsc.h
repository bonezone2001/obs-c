/**
 * @file obsc.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief The main header file for the obsc dll wrapper.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>
#include <tuple>

#include "obsc/mutex.h"
#include "obsc/context.h"
#include "obsc/obsc_export.hpp"

namespace obsc {

struct OBSC_EXPORT CaptureConfig {
    std::string windowName;
    bool captureOverlays;
    uint32_t frames;
};

class OBSC_EXPORT Capture {
private:
    CaptureConfig config;
    Context context;

public:
    Capture(const std::string& windowName);

    void attach();
    void shutdown();
    std::tuple<std::vector<uint8_t>, std::pair<size_t, size_t>> captureFrame();

private:
    void initKeepalive();
    void initPipe();
    void initTextureMutexes();
    void initEvents();
    void initHookInfo();
    std::tuple<DXGI_MAPPED_RECT, std::pair<size_t, size_t>> mapResource();
    bool attemptExistingHook();

};

} // namespace obsc