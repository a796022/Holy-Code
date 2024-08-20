#ifndef BACKGROUND_KEYBOARD_INPUT_WRAPPER_H
#define BACKGROUND_KEYBOARD_INPUT_WRAPPER_H

#include <stdint.h>

/**
 * @brief Initializes the library
 * 
 * - Calls the initialization function of the library and returns its output.
 * 
 * @return uint8_t 0 if the initialization was successful, 1 otherwise
 */
uint8_t init_background_keyboard_imput_wrapper();

/**
 * @brief Closes the library
 * 
 * - Calls the closing function of the library and returns its output.
 * 
 * @return uint8_t 0 if the closing was successful, 1 otherwise
 */
uint8_t close_background_keyboard_imput_wrapper();

#endif /* BACKGROUND_KEYBOARD_INPUT_WRAPPER_H */
