#include <stdio.h>
#include <time.h>

#include "../lib/background_keyboard_imput/background_keyboard_imput.h"
#include "../lib/clipboard/clipboard.h"
#include "tree_wrapper.h"
#include "tree_string.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// State of the Ctrl keys
uint8_t ctrl_pressed = 0;

// Time of the last presses of the Ctrl+C shortcut
time_t last_ctrlc_press = 0;

/**
 * @brief Registers the press of the left Ctrl key
 */
void left_ctrl_press_detection() {
    ctrl_pressed |= 0x01;
}

/**
 * @brief Registers the release of the left Ctrl key
 */
void left_ctrl_release_detection() {
    ctrl_pressed &= 0xFE;
}

/**
 * @brief Registers the press of the right Ctrl key
 */
void right_ctrl_press_detection() {
    ctrl_pressed |= 0x02;
}

/**
 * @brief Registers the release of the right Ctrl key
 */
void right_ctrl_release_detection() {
    ctrl_pressed &= 0xFD;
}

void detect_double_ctrl_c() {
    if (ctrl_pressed) {
        time_t current_time = time(NULL);

        if (difftime(current_time, last_ctrlc_press) < 1) {
            char* clipboard_content = get_clipboard_content();
            clean_string(clipboard_content);
            add_node_to_selected_node(clipboard_content);
        }
        last_ctrlc_press = current_time;
    }
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the library
 * 
 * - Calls the initialization function of the library and returns its output.
 * 
 * @return uint8_t 0 if the initialization was successful, 1 otherwise
 */
uint8_t init_background_keyboard_imput_wrapper() {
    // Initialization of the library
    uint8_t lib_status =  init_background_keyboard_imput();
    if (lib_status) {
        return lib_status;
    }

    // Register keyboard events
    register_keyboard_press_event(KEY_C, detect_double_ctrl_c);
    register_keyboard_press_event(KEY_LEFTCTRL, left_ctrl_press_detection);
    register_keyboard_release_event(KEY_LEFTCTRL, left_ctrl_release_detection);
    register_keyboard_press_event(KEY_RIGHTCTRL, right_ctrl_press_detection);
    register_keyboard_release_event(KEY_RIGHTCTRL, right_ctrl_release_detection);

    return 0;
}

/**
 * @brief Closes the library
 * 
 * - Calls the closing function of the library and returns its output.
 * 
 * @return uint8_t 0 if the closing was successful, 1 otherwise
 */
uint8_t close_background_keyboard_imput_wrapper() {
    return close_background_keyboard_imput();
}