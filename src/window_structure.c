#include <gtk/gtk.h>

#include "history.h"
#include "operations.h"
#include "tree_wrapper.h"
#include "window_manager.h"
#include "window_structure.h"

static void init_window_structure(struct WindowStructure* window_structure);

/**
 * @brief Creates a new window structure
 * 
 * - The window, with all its components, is created and shown
 * 
 * @return struct WindowStructure The new window structure
 */
struct WindowStructure* new_window_structure() {
    struct WindowStructure* window_structure = g_new(struct WindowStructure, 1);

    // tree_model
    window_structure->tree_model = gtk_tree_store_new(1, G_TYPE_STRING);

    // tree_view
    window_structure->tree_view = new_tree_view(window_structure);

    // window
    window_structure->window = new_window(window_structure);

    // history
    window_structure->history = new_history();

    // Initialize the window structure
    init_window_structure(window_structure);

    return window_structure;
}

/**
 * @brief Initializes the window structure.
 * 
 * @param window_structure The window structure to initialize
 * 
 * @return void
 */
static void init_window_structure(struct WindowStructure* window_structure) {
    
}

/**
 * @brief Closes the window structure.
 * 
 * @param window_structure The window structure to close
 * 
 * @return void
 */
void close_window_structure(struct WindowStructure* window_structure) {
    g_free(window_structure);
}

/**
 * @brief Tells the history that the changes have been saved and modifies the window title to reflect this.
 * 
 * @param window_structure Window structure where the changes have been saved
 * 
 * @return void
 */
void set_changes_as_saved(struct WindowStructure* window_structure) {
    set_history_as_saved(window_structure->history);
    set_title_as_saved(window_structure->window);
}

// /**
//  * @brief Execute the operation, register the changes in the history and modifies the window title to reflect the new changes (if necessary).
//  * 
//  * @param id id of the operation to know how to manage it (not the operation itself because the id anyway is also needed and is more natural to switch with an id rather with a function pointer)
//  * @param data parameters to the function
//  * @param is_set indicates if the operation is part of a set of operations
//  * @param window_structure Window structure where the operation is executed
//  * 
//  * @return void
//  */
// void resolve_operation(struct WindowStructure* window_structure, uint8_t id, gboolean is_set, void *data) {
//     // Get the history
//     struct History* history = window_structure->history;

//     // Change the title of the window if all changes was saved
//     if(!there_are_unsaved_changes(history)) {
//         set_title_unsaved(window_structure->window);
//     }

//     // Get the pointer to the function that will execute the operation
//     gboolean (*operation)(struct WindowStructure*, void*);
//     switch (id) {
//         case AGGREGATE_OP:
//             operation = aggregate_operation;
//             break;
//         case DELETE_OP:
//             operation = delete_operation;
//             break;
//         default:
//             perror("Error: Unknown operation\n");
//             return;
//     }

//     if (is_set) {
//         init_operations_set(history);
//     }

//     // Execute the operation
//     do {
//         store_operation(history, id, data);
//     } while (operation(window_structure, data));

//     if (is_set) {
//         end_operations_set(history);
//     }
// }