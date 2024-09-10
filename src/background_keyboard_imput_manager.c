#include <stdio.h>
#include <time.h>

#include "../lib/background_keyboard_imput/background_keyboard_imput.h"
#include "../lib/clipboard/clipboard.h"
#include "tree_wrapper.h"
#include "tree_string.h"
#include "window_manager.h"
#include "global_structure.h"
#include "bg_key_input.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Registers the press of the left Ctrl key
 * 
 * @param ctrl_pressed Pointer to where the state of the Ctrl keys is stored
 * 
 * @return void
 */
void left_ctrl_press_detection(void* ctrl_pressed) {
    *(uint8_t*)ctrl_pressed |= 0x01;
}

/**
 * @brief Registers the release of the left Ctrl key
 * 
 * @param ctrl_pressed Pointer to where the state of the Ctrl keys is stored
 * 
 * @return void
 */
void left_ctrl_release_detection(void* ctrl_pressed) {
    *(uint8_t*)ctrl_pressed &= 0xFE;
}

/**
 * @brief Registers the press of the right Ctrl key
 * 
 * @param ctrl_pressed Pointer to where the state of the Ctrl keys is stored
 * 
 * @return void
 */
void right_ctrl_press_detection(void* ctrl_pressed) {
    *(uint8_t*)ctrl_pressed |= 0x02;
}

/**
 * @brief Registers the release of the right Ctrl key
 * 
 * @param ctrl_pressed Pointer to where the state of the Ctrl keys is stored
 * 
 * @return void
 */
void right_ctrl_release_detection(void* ctrl_pressed) {
    *(uint8_t*)ctrl_pressed &= 0xFD;
}

void detect_double_ctrl_c(void* global_structure) {
    // Get the data
    struct BgKeyInput* bg_key_input = ((struct GlobalStructure*)global_structure)->bg_key_input;
    GList* window_structures = ((struct GlobalStructure*)global_structure)->window_structures;
    
    // Process the Ctrl+C key press
    if (bg_key_input->ctrl_pressed) {
        time_t current_time = time(NULL);

        if (difftime(current_time, bg_key_input->last_ctrlc_press) < 1) {
            char* clipboard_content = get_clipboard_content();
            clean_string(clipboard_content);

            run_for_all_windows(window_structures, add_text_to_selected_node, clipboard_content);
        }
        bg_key_input->last_ctrlc_press = current_time;
    }
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the library
 * 
 * @return void
 */
void init_background_keyboard_imput_manager(struct GlobalStructure* global_structure) {
    // Initialization of the library
    init_background_keyboard_imput();

    // Register keyboard events
    register_keyboard_press_event(KEY_C, detect_double_ctrl_c, global_structure);
    register_keyboard_press_event(KEY_LEFTCTRL, left_ctrl_press_detection, &global_structure->bg_key_input->ctrl_pressed);
    register_keyboard_release_event(KEY_LEFTCTRL, left_ctrl_release_detection, &global_structure->bg_key_input->ctrl_pressed);
    register_keyboard_press_event(KEY_RIGHTCTRL, right_ctrl_press_detection, &global_structure->bg_key_input->ctrl_pressed);
    register_keyboard_release_event(KEY_RIGHTCTRL, right_ctrl_release_detection, &global_structure->bg_key_input->ctrl_pressed);
}

/**
 * @brief Closes the library
 * 
 * - Calls the closing function of the library and returns its output.
 * 
 * @return void
 */
void close_background_keyboard_imput_manager() {
    close_background_keyboard_imput();
}