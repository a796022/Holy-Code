#include <gtk/gtk.h>

#include "gtk_box_manager.h"
#include "gtk_menu_bar_wrapper.h"
#include "gtk_progress_bar.h"
#include "gtk_scrolled_window_wrapper.h"
#include "GtkAccelGroup_wrapper.h"
#include "history.h"
#include "operations.h"
#include "paned_manager.h"
#include "tree_wrapper.h"
#include "window_manager.h"
#include "window_structure.h"

/**
 * @brief Creates a new empty window structure
 * 
 * @return struct WindowStructure The new empty window structure
 */
struct WindowStructure* new_window_structure() {
    struct WindowStructure* window_structure = g_new(struct WindowStructure, 1);

    // window
    window_structure->window = new_window(window_structure);

    // tree_model
    window_structure->tree_model = gtk_tree_store_new(1, G_TYPE_STRING);

    // tree_view
    window_structure->tree_view = new_tree_view(window_structure);

    // main_box
    window_structure->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window_structure->window),
                      window_structure->main_box);

    // history
    window_structure->history = new_history();

    // menu_bar
    window_structure->menu_bar = NULL;

    // progress_bar
    window_structure->progress_bar = NULL;

    return window_structure;
}

/**
 * @brief Initializes the window structure.
 * 
 * @param window_structure The window structure to initialize
 * 
 * @return void
 */
void init_window_structure(struct WindowStructure* window_structure) {
    // Vertical divider
    GtkWidget* paned;

    // Scrolleable container for the treeview
    GtkWidget* scrolled_window;

    // Create the menu_bar
    window_structure->menu_bar = new_menu_bar(window_structure);
    agregar_widget_box(window_structure->main_box, window_structure->menu_bar->main_widget, FALSE, FALSE, 0);

    // Create the GtkPaned (divider)
    paned = crear_paned_horizontal();
    agregar_widget_box(window_structure->main_box, paned, TRUE, TRUE, 0);

    // Include the progress bar
    window_structure->progress_bar = gtk_progress_bar_new();
    agregar_widget_box(window_structure->main_box, window_structure->progress_bar, FALSE, FALSE, 0);

    // Create the content for the left side of the divider (the scrolled window)
    scrolled_window = init_scrolled_window();
    agregar_widget_paned_izquierda(paned, scrolled_window, TRUE, FALSE);

    // Add the tree to the scrolled window
    add_widget_to_scrolled_window(scrolled_window, window_structure->tree_view);

    // Create content for the right area of the divider
    GtkWidget *right_label_panel = gtk_label_new("Contenido derecho");
    agregar_widget_paned_derecha(paned, right_label_panel, TRUE, FALSE);

    // Initialize the keyboard shortcuts
    init_keyboard_shortcuts(window_structure);

    // Show the window
    show_window(window_structure);
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