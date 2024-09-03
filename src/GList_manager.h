#pragma once

#include <gtk/gtk.h>

#include "window_structure.h"

/**
 * @brief Adds a window structure to the list of window structures.
 * 
 * @param window_structures The list of window structures
 * @param window_structure The window structure to add
 * 
 * @return void
 */
void GList_add_new_window_structure(GList** window_structures);

/**
 * @brief Closes the window structures in the list of window structures.
 * 
 * @param window_structures The list of window structures
 * 
 * @return void
 */
void GList_close_window_structures(GList* window_structures);

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
void run_for_all_windows(GList *windows_list, void (*funcion)(struct WindowStructure*, void*), void *data);