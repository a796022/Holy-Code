#pragma once

#include <gtk/gtk.h>

// #include "window_structure.h"

// WINDOW_STRUCTURES ///////////////////////////////////////////////////////////

/**
 * @brief Adds a WindowStructure* to the list of WindowStructure*'s pointed by
 * window_structures.
 * 
 * @param window_structures Pointer to the GList* of WindowStructure*'s where
 * the WindowStructure* will be added. If it is the first WindowStructure* to be
 * added, the GList* pointed by window_structures must be NULL.
 * 
 * @return void
 */
void GList_add_new_window_structure(GList** window_structures);

/**
 * @brief Closes all the WindowStructure*'s in the GList window_structures and
 * frees the GList itself.
 * 
 * @param window_structures The GList of WindowStructure*'s to close.
 * 
 * @return void
 */
void GList_close_window_structures(GList** window_structures);

// /**
//  * @brief Runs a function for all windows.
//  * 
//  * - The function is executed for all windows.
//  * - The function receives the window and the data as arguments.
//  * 
//  * @param windows_list List of windows.
//  * @param funcion Function to run for all windows.
//  * @param datos Data to pass to the function.
//  * 
//  * @return void
//  */
// void run_for_all_windows(GList *windows_list, void (*funcion)(struct WindowStructure*, void*), void *data);