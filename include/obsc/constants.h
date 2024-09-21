/**
 * @file constants.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief The constants used throughout the obsc library.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once
#include <windows.h>

namespace obsc {

// File names
const char* const FILE_GRAPHICS_OFFSETS_64_NAME = "get-graphics-offsets64.exe";
const char* const FILE_INJECTOR_64_NAME = "inject-helper64.exe";
const char* const FILE_HOOK_64_NAME = "graphics-hook64.dll";

const char* const FILE_GRAPHICS_OFFSETS_32_NAME = "get-graphics-offsets32.exe";
const char* const FILE_INJECTOR_32_NAME = "inject-helper32.exe";
const char* const FILE_HOOK_32_NAME = "graphics-hook32.dll";

// Event and mutex flags
constexpr DWORD EVENT_FLAGS = EVENT_MODIFY_STATE | SYNCHRONIZE;
constexpr DWORD MUTEX_FLAGS = SYNCHRONIZE;

// Event names
const char* const EVENT_CAPTURE_RESTART = "CaptureHook_Restart";
const char* const EVENT_CAPTURE_STOP = "CaptureHook_Stop";
const char* const EVENT_HOOK_READY = "CaptureHook_HookReady";
const char* const EVENT_HOOK_EXIT = "CaptureHook_Exit";
const char* const EVENT_HOOK_INIT = "CaptureHook_Initialize";

// Other constants
const char* const WINDOW_HOOK_KEEPALIVE = "CaptureHook_KeepAlive";
const char* const MUTEX_TEXTURE1 = "CaptureHook_TextureMutex1";
const char* const MUTEX_TEXTURE2 = "CaptureHook_TextureMutex2";
const char* const SHMEM_HOOK_INFO = "CaptureHook_HookInfo";
const char* const SHMEM_TEXTURE = "CaptureHook_Texture";
const char* const PIPE_NAME = "CaptureHook_Pipe";

} // namespace obsc