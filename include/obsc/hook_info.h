/**
 * @file hook_info.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief The hook info structure and all it's related constants.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once

#include <windows.h>
#include <string>

#include "obsc/graphics_offsets.h"
#include "obsc/obsc_export.hpp"

namespace obsc {

// Structures
#pragma pack(push, 8)

struct OBSC_EXPORT HookInfo {
	/* hook version */
	uint32_t hook_ver_major;
	uint32_t hook_ver_minor;

	/* capture info */
	CaptureType type;
	uint32_t window;
	uint32_t format;
	uint32_t cx;
	uint32_t cy;
	uint32_t UNUSED_base_cx;
	uint32_t UNUSED_base_cy;
	uint32_t pitch;
	uint32_t map_id;
	uint32_t map_size;
	bool flip;

	/* additional options */
	uint64_t frame_interval;
	bool UNUSED_use_scale;
	bool force_shmem;
	bool capture_overlay;
	bool allow_srgb_alias;

	/* hook addresses */
	struct GraphicsOffsets offsets;
    
	uint32_t reserved[126];

    std::string toString() const {
        std::stringstream ss;
        ss << "HookInfo { "
           << "hookVerMajor: " << hook_ver_major << ", "
           << "hookVerMinor: " << hook_ver_minor << ", "
           << "captureType: " << (int)type << ", "
           << "window: " << window << ", "
           << "format: " << format << ", "
           << "cx: " << cx << ", "
           << "cy: " << cy << ", "
           << "pitch: " << pitch << ", "
           << "mapId: " << map_id << ", "
           << "mapSize: " << map_size << ", "
           << "flip: " << flip << ", "
           << "frameInterval: " << frame_interval << ", "
           << "forceShmem: " << force_shmem << ", "
           << "captureOverlay: " << capture_overlay << ", "
           << "graphicsOffsets: (omitted for brevity), "
           << "}";
        return ss.str();
    }
};
static_assert(sizeof(struct HookInfo) == 648, "ABI compatibility");

#pragma pack(pop)

} // namespace obsc