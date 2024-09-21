/**
 * @file context.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief The context structure.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once
#include <windows.h>
#include <dxgi.h>
#include <string>
#include <memory>
#include <stdexcept>
#include <wrl/client.h>

#pragma comment(lib,"d3d11.lib")
#include <d3d11.h>

#include "obsc/obsc_export.hpp"
#include "obsc/mutex.h"
#include "obsc/event.h"
#include "obsc/pipe.h"

using Microsoft::WRL::ComPtr;

namespace obsc {

struct OBSC_EXPORT Context {
    HWND hwnd = nullptr;
    uint32_t pid = 0;
    DWORD threadId = 0;
    uint32_t textureHandle = 0;
    bool is32Bit = false;
    
    std::unique_ptr<Mutex> keepaliveMutex;
    std::unique_ptr<Mutex> textureMutex1;
    std::unique_ptr<Mutex> textureMutex2;
    std::unique_ptr<NamedPipe> pipe;

    Event hookRestart;
    Event hookStop;
    Event hookInit;
    Event hookReady;
    Event hookExit;

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> deviceContext;
    ComPtr<ID3D11Resource> resource;

    ComPtr<IDXGISurface> surface;
};

} // namespace obsc