#pragma once

#include <gtk/gtk.h>
#include <time.h>

struct BgKeyInput {
    // State of the Ctrl keys
    uint8_t ctrl_pressed;

    // Time of the last presses of the Ctrl+C shortcut
    time_t last_ctrlc_press;
};

/**
 * @brief Creates a new empty background keyboard imput structure.
 * 
 * @return struct BgKeyInput The new empty background keyboard imput structure
 */
struct BgKeyInput* new_bg_key_input();

/**
 * @brief Closes the background keyboard imput structure.
 * 
 * @param bg_key_input The background keyboard imput structure to close
 * 
 * @return void
 */
void close_bg_key_input(struct BgKeyInput* bg_key_input);