// #include "background_keyboard_imput_manager.h"
#include "GList_manager.h"
#include "global_structure.h"

static void init_global_structure(struct GlobalStructure* global_structure);

/**
 * @brief Creates a GlobalStructure. The list of WindowStructure*'s is
 * initialized with one WindowStructure* (the first window that is opened when
 * running the program).
 * 
 * @param global_structure Pointer to the GlobalStructure* to initialize.
 * 
 * @return void
 */
void new_global_structure(struct GlobalStructure** global_structure) {
    *global_structure = g_new(struct GlobalStructure, 1);

    // window_structures
    (*global_structure)->window_structures = NULL;

    // // bg_key_input
    // global_structure->bg_key_input = new_bg_key_input();

    // Initialize the global structure
    init_global_structure(*global_structure);

    // // External libraries
    // init_background_keyboard_imput_manager(global_structure);
}

static void init_global_structure(struct GlobalStructure* global_structure) {
    // Add the first main window to the list of windows
    GList_add_new_window_structure(&global_structure->window_structures);
}

/**
 * @brief Closes a GlobalStructure*.
 * 
 * @param global_structure The GlobalStructure* to close.
 * 
 * @return void
 */
void close_global_structure(struct GlobalStructure* global_structure) {
    // Close the list of window structures
    GList_close_window_structures(&global_structure->window_structures);

    // // Close the background keyboard imput structure
    // close_bg_key_input(global_structure->bg_key_input);

    // // Close the corresponding libraries
    // close_background_keyboard_imput_manager();

    // Free the memory allocated for the global structure
    g_free(global_structure);
}