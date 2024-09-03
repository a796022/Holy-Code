#include "background_keyboard_imput_manager.h"
#include "GList_manager.h"
#include "global_structure.h"

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Creates a global structure.
 * 
 * @return struct new empty global structure
 */
struct GlobalStructure* new_global_structure() {
    struct GlobalStructure* global_structure = g_malloc(sizeof(struct GlobalStructure));

    global_structure->window_structures = NULL;
    global_structure->bg_key_input = new_bg_key_input();

    return global_structure;
}

/**
 * @brief Initializes a global structure.
 * 
 * @param global_structure The global structure to initialize
 * 
 * @return void
 */
void init_global_structure(struct GlobalStructure* global_structure) {
    // Add the first main window to the list of windows
    GList_add_new_window_structure(&global_structure->window_structures);

    // Initialize the background keyboard imput structure
    init_bg_key_input(global_structure->bg_key_input);

    // Initializes the corresponding libraries
    init_background_keyboard_imput_manager(global_structure);
}

/**
 * @brief Closes a global structure.
 * 
 * @param global_structure The global structure to close
 * 
 * @return void
 */
void close_global_structure(struct GlobalStructure* global_structure) {
    // Close the list of window structures
    GList_close_window_structures(global_structure->window_structures);

    // Close the background keyboard imput structure
    close_bg_key_input(global_structure->bg_key_input);

    // Close the corresponding libraries
    close_background_keyboard_imput_manager();

    // Free the memory allocated for the global structure
    g_free(global_structure);
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// None