#include <gtk/gtk.h>

#include "GList_manager.h"
#include "window_structure.h"

// WINDOW_STRUCTURES ///////////////////////////////////////////////////////////

/**
 * @brief Adds a window structure to the list of window structures.
 * 
 * @param window_structures The list of window structures
 * 
 * @return void
 */
void GList_add_new_window_structure(GList** window_structures) {
    struct WindowStructure* window_structure = new_window_structure();
    *window_structures = g_list_append(*window_structures, window_structure);
}

/**
 * @brief Closes the window structures in the list of window structures and the
 * list itself
 * 
 * @param window_structures The list of window structures
 * 
 * @return void
 */
void GList_close_window_structures(GList* window_structures) {
    g_list_free_full(window_structures, (GDestroyNotify)close_window_structure);
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