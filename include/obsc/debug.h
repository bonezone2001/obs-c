/**
 * @file debug.h
 * @author Kyle Pelham (bonezone2001@gmail.com)
 * @brief Any debug related macros, utilities, or functions header file.
 * 
 * @copyright Copyright (c) 2024
*/

#pragma once
#include <fmt/core.h>

#define DEBUG

#ifdef DEBUG
#include <fmt/core.h>
#define PRINT fmt::print
#define PRINTLN fmt::println
#else
#define PRINT
#define PRINTLN
#endif