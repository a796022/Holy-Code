#pragma once

#include <stdint.h>

#include "global_structure.h"

/**
 * @brief Initializes the library
 * 
 * - Calls the initialization function of the library and returns its output.
 * 
 * @return void
 */
void init_background_keyboard_imput_manager(struct GlobalStructure* global_structure);

/**
 * @brief Closes the library
 * 
 * - Calls the closing function of the library and returns its output.
 * 
 * @return void
 */
void close_background_keyboard_imput_manager();