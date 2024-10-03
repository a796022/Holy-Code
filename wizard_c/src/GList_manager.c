#include <gtk/gtk.h>

#include "GList_manager.h"
#include "window_structure.h"
// #include "history.h"

// WINDOW_STRUCTURES ///////////////////////////////////////////////////////////

static void GList_init_window_structure(GList** window_structures, struct WindowStructure* window_structure);
static gboolean on_window_delete(GtkWidget *widget, GdkEvent *event,
                                 GList **window_structures);

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
void GList_add_new_window_structure(GList** window_structures) {
    // Create the WindowStructure
    struct WindowStructure* window_structure;
    new_window_structure(&window_structure);
    
    // Add the WindowStructure to the list
    *window_structures = g_list_append(*window_structures, window_structure);

    // Initialize the window structure (in relation to the GList)
    GList_init_window_structure(window_structures, window_structure);
}

/**
 * @brief Initializes the window structure in relation to the GList.
 * 
 * - Connects the signals of the window son when on_delete_event is emitted,
 * the window is closed and the memory is freed. Also, if all the windows are
 * closed, the program is terminated.
 * 
 * @param window_structures Pointer to the GList* of WindowStructure*'s.
 * @param window_structure The WindowStructure* to initialize.
 * 
 * @return void
 */
static void GList_init_window_structure(GList** window_structures, struct WindowStructure* window_structure) {
    /* Connect the signals of the window son when on_delete_event is emitted,
    the window is closed and the memory is freed. Also, if all the windows are
    closed, the program is terminated. */
    g_signal_connect(window_structure->window, "delete-event",
                     G_CALLBACK(on_window_delete), window_structures);
    
}

/**
 * @brief Closes all the WindowStructure*'s in the GList pointed by 
 * window_structures and frees the GList itself.
 * 
 * @param window_structures Pointer to the GList* of WindowStructure*'s to
 * close.
 * 
 * @return void
 */
void GList_close_window_structures(GList** window_structures) {
    /* The use of g_steal_pointer() ensures that after releasing the list, the
    original pointer (window_structures) is set to NULL. */
    g_list_free_full(g_steal_pointer(window_structures), (GDestroyNotify)close_window_structure);
}

/**
 * @brief Callback function for the "delete-event" signal of a window.
 * 
 * - When the window is closed, the corresponding WindowStructure* is removed
 * from the list of WindowStructure*'s and the memory is freed.
 * - If all windows are closed, the program is terminated.
 * 
 * @param widget The window that emitted the signal.
 * @param event The event that triggered the signal.
 * @param window_structures Pointer to the GList* of WindowStructure*'s.
 * 
 * @return gboolean FALSE to ensure the default handler runs, so the window is
 * destroyed.
 */
static gboolean on_window_delete(GtkWidget *widget, GdkEvent *event,
                                 GList **window_structures) {
    (void)event;

    struct WindowStructure* window_structure = NULL;
    GList* node = *window_structures;

    // Find the window structure corresponding to the widget being destroyed
    while (node) {
        window_structure = node->data;
        if (window_structure->window == widget) {
            break;
        }
        node = node->next;
    }

    if (window_structure) {
        // Remove the window structure from the list
        *window_structures = g_list_remove(*window_structures,
                                           window_structure);
        // Free the memory for the window structure
        close_window_structure(window_structure);
    }

    // If all windows are closed, quit the program
    if (g_list_length(*window_structures) == 0) {
        gtk_main_quit();
    }

    // Returning FALSE ensures the default handler runs, so destroys the window
    return FALSE;
}

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
// void run_for_all_windows(GList *windows_list, void (*funcion)(struct WindowStructure*, void*), void *data) {
//     GList *iterator;
//     for (iterator = windows_list; iterator != NULL; iterator = iterator->next) {
//         struct WindowStructure *window_struct = (struct WindowStructure*)iterator->data;
//         funcion(window_struct, data);
//     }
// }