/**
 * @file utils.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief Several utilities for the obsc library.
 * 
 * Note: These utilities ideally should be moved somewhere else.
 *       but for now they are here. 
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once
#include <windows.h>
#include <string>
#include <d3d11.h>
#include <wrl/client.h>
#include <stdexcept>

#include "obsc/obsc_export.hpp"

using Microsoft::WRL::ComPtr;

namespace obsc {

std::string OBSC_EXPORT runProcessAndCaptureOutput(const std::string& cmd);
void OBSC_EXPORT injectGraphicsHook(uint32_t pid, bool antiCheatCompatible, bool is32Bit);
std::pair<ComPtr<ID3D11Device>, ComPtr<ID3D11DeviceContext>> OBSC_EXPORT createDevice();
ComPtr<ID3D11Resource> OBSC_EXPORT openResource(ComPtr<ID3D11Device> device, uint32_t handle);
bool OBSC_EXPORT is32BitProcess(uint32_t pid);

} // namespace obsc