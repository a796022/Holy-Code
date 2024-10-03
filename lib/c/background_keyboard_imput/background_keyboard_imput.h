#ifndef BACKGROUND_KEYBOARD_INPUT_H
#define BACKGROUND_KEYBOARD_INPUT_H

#include <stdint.h>
#include <linux/input.h>

/**
 * @brief Initializes the library
 * 
 * - Initializes the file descriptor to read the keyboard events.
 * - NOTE: the file descriptor is hardcoded to read the keyboard events from /dev/input/event0. This file may change depending on the system. To find out the eventX file corresponding to the keyboard, use evtest.
 * 
 * @return uint8_t 0 if the initialization was successful, 1 otherwise
 */
uint8_t init_background_keyboard_imput();

/**
 * @brief Closes the library
 * 
 * - Closes the file descriptor to read the keyboard events.
 * - Stops the keyboard reader thread.
 * 
 * @return uint8_t 0 if the closing was successful, 1 otherwise
 */
uint8_t close_background_keyboard_imput();

/**
 * @brief Registers a function to be called when a keyboard press event is detected
 * 
 * - Registers a function to be called when a keyboard press event is detected.
 * - NOTE: for more information on event types, codes and values, refer to the file linux/input-event-codes.h
 * 
 * @param[in] code Keyboard event code
 * @param[in] function Function to be called when the keyboard event is detected
 * @param[in] parameter Parameter to be passed to the function
 */
void register_keyboard_press_event(uint16_t code, void (*function)(void*), void* parameter);

/**
 * @brief Registers a function to be called when a keyboard release event is detected
 * 
 * - Registers a function to be called when a keyboard release event is detected.
 * - NOTE: for more information on event types, codes and values, refer to the file linux/input-event-codes.h
 * 
 * @param[in] code Keyboard event code
 * @param[in] function Function to be called when the keyboard event is detected
 * @param[in] parameter Parameter to be passed to the function
 */
void register_keyboard_release_event(uint16_t code, void (*function)(void*), void* parameter);

#endif // BACKGROUND_KEYBOARD_INPUT_H
