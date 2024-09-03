#include <gtk/gtk.h>

#include "GList_manager.h"
#include "window_structure.h"

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// WINDOW_STRUCTURES ///////////////////////////////////////////////////////////

/**
 * @brief Adds a window structure to the list of window structures.
 * 
 * @param window_structures The list of window structures
 * @param window_structure The window structure to add
 * 
 * @return void
 */
void GList_add_new_window_structure(GList** window_structures) {
    // Create and initialize a new window structure
    struct WindowStructure* window_structure = new_window_structure();
    init_window_structure(window_structure);

    // Add the window structure to the list of window structures
    *window_structures = g_list_append(*window_structures, window_structure);
}

/**
 * @brief Closes the window structures in the list of window structures.
 * 
 * @param window_structures The list of window structures
 * 
 * @return void
 */
void GList_close_window_structures(GList* window_structures) {
    // Close each window structure in the list of window structures
    for (GList* iterator = window_structures; iterator != NULL; iterator = iterator->next) {
        struct WindowStructure* window_structure = (struct WindowStructure*) iterator->data;
        close_window_structure(window_structure);
    }

    // Free the memory allocated for the list of window structures
    g_list_free(window_structures);
}

/**
 * @brief Runs a function for all windows.
 * 
 * - The function is executed for all windows.
 * - The function receives the window and the data as arguments.
 * 
 * @param windows_list List of windows.
 * @param funcion Function to run for all windows.
 * @param datos Data to pass to the function.
 * 
 * @return void
 */
void run_for_all_windows(GList *windows_list, void (*funcion)(struct WindowStructure*, void*), void *data) {
    GList *iterator;
    for (iterator = windows_list; iterator != NULL; iterator = iterator->next) {
        struct WindowStructure *window_struct = (struct WindowStructure*)iterator->data;
        funcion(window_struct, data);
    }
}