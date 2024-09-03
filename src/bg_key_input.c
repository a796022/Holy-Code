#include <gtk/gtk.h>
#include <time.h>

#include "background_keyboard_imput_manager.h"
#include "bg_key_input.h"

/**
 * @brief Creates a new empty background keyboard imput structure.
 * 
 * @return struct BgKeyInput The new empty background keyboard imput structure
 */
struct BgKeyInput* new_bg_key_input() {
    struct BgKeyInput* bg_key_input = g_malloc(sizeof(struct BgKeyInput));

    bg_key_input->ctrl_pressed = 0;
    bg_key_input->last_ctrlc_press = 0;

    return bg_key_input;
}

/**
 * @brief Initializes the background keyboard imput structure.
 * 
 * @param bg_key_input The background keyboard imput structure to initialize
 * 
 * @return void
 */
void init_bg_key_input(struct BgKeyInput* bg_key_input) {
    return;
}

/**
 * @brief Closes the background keyboard imput structure.
 * 
 * @param bg_key_input The background keyboard imput structure to close
 * 
 * @return void
 */
void close_bg_key_input(struct BgKeyInput* bg_key_input) {
    g_free(bg_key_input);
}