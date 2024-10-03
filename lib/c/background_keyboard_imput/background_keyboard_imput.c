#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

// File descriptor to keyboard event file
int input_fd = -1;

// Flag to stop the keyboard thread
volatile uint8_t running = 1;

// Thread id
pthread_t thread_id;

// NOTE: for more information on event types, codes and values, refer to the file linux/input-event-codes.h
// Array of functions, one for each possible keyboard press event value. All of them start with NULL.
void (*keyboard_press_event_functions[KEY_MAX])(void*) = {NULL};
void* keyboard_press_event_functions_parameters[KEY_MAX] = {NULL};

// Array of functions, one for each possible keyboard release event value. All of them start with NULL.
void (*keyboard_release_event_functions[KEY_MAX])(void*) = {NULL};
void* keyboard_release_event_functions_parameters[KEY_MAX] = {NULL};

/**
 * @brief Signal handler
 * 
 * - Handles the SIGINT and SIGTERM signals to stop the keyboard thread.
 * 
 * @param[in] sig Signal number
 */
void handle_signal(int sig) {
    switch (sig) {
        case SIGINT:
        case SIGTERM:
            running = 0;
            break;
    }
}

/**
 * @brief Thread to print the keyboard events
 * 
 * - Reads the keyboard events on an infinite loop and prints the type, code and value of the event.
 * 
 * @param[in] arg Argument passed to the thread
 * 
 * @return void* NULL
 */
void* keyboard_thread() {
    struct input_event event;

    while (running) {
        read(input_fd, &event, sizeof(struct input_event));
        if (event.type == EV_KEY) {
            if (event.value == 1) {
                if (keyboard_press_event_functions[event.code] != NULL) {
                    void* parameter = keyboard_press_event_functions_parameters[event.code];
                    keyboard_press_event_functions[event.code](parameter);
                }
            } else if (event.value == 0) {
                if (keyboard_release_event_functions[event.code] != NULL) {
                    void* parameter = keyboard_release_event_functions_parameters[event.code];
                    keyboard_release_event_functions[event.code](parameter);
                }
            }
        }
    }

    return NULL;
}

/**
 * @brief Initializes the library
 * 
 * - Initializes the file descriptor to read the keyboard events.
 * - NOTE: the file descriptor is hardcoded to read the keyboard events from /dev/input/event0. This file may change depending on the system. To find out the eventX file corresponding to the keyboard, use evtest.
 * 
 * @return uint8_t 0 if the initialization was successful, 1 otherwise
 */
uint8_t init_background_keyboard_imput() {
    // Open keyboard event file
    input_fd = open("/dev/input/event0", O_RDWR);
    if (input_fd == -1) {
        perror("Could not open keyboard event file");
        return 1;
    }

    // Register signal handler
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Create thread
    if (pthread_create(&thread_id, NULL, keyboard_thread, NULL) != 0) {
        perror("Error: could not create thread to read keyboard events\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Closes the library
 * 
 * - Closes the file descriptor to read the keyboard events.
 * - Stops the keyboard reader thread.
 * 
 * @return uint8_t 0 if the closing was successful, 1 otherwise
 */
uint8_t close_background_keyboard_imput() {
    running = 0;

    close(input_fd);

    return 0;
}

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
void register_keyboard_press_event(uint16_t code, void (*function)(void*), void* parameter) {
    keyboard_press_event_functions[code] = function;
    keyboard_press_event_functions_parameters[code] = parameter;
}

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
void register_keyboard_release_event(uint16_t code, void (*function)(void*), void* parameter) {
    keyboard_release_event_functions[code] = function;
    keyboard_release_event_functions_parameters[code] = parameter;
}