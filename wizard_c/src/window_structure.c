#include <gtk/gtk.h>

// #include "gtk_box_manager.h"
// #include "gtk_menu_bar_wrapper.h"
// #include "gtk_progress_bar.h"
// #include "gtk_scrolled_window_wrapper.h"
// #include "GtkAccelGroup_wrapper.h"
// #include "history.h"
// #include "operations.h"
// #include "paned_manager.h"
#include "session_manager.h"
#include "tree_files.h"
#include "tree_manager.h"
#include "window_manager.h"
#include "window_structure.h"

static void init_window_structure(struct WindowStructure* window_structure);

/**
 * @brief Initializes the WindowStructure* pointed by window_structure.
 * 
 * @param window_structure Pointer to the WindowStructure* to initialize.
 * 
 * @return void
 */
void new_window_structure(struct WindowStructure** window_structure) {
    *window_structure = g_new(struct WindowStructure, 1);

    // menu_bar
    (*window_structure)->menu_bar = NULL;

    // progress_bar
    (*window_structure)->progress_bar = NULL;

    // tree_path_file
    read_last_opened_file(&(*window_structure)->tree_path_file);

    // tree_view
    new_tree_view(&(*window_structure)->tree_view);

    // window
    new_main_window(&(*window_structure)->window);

    // main_box
    window_structure->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window_structure->window),
                      window_structure->main_box);

    // // history
    // window_structure->history = new_history();

    // Initialize the window structure
    init_window_structure(*window_structure);
}

/**
 * @brief Initializes the window structure.
 * 
 * @param window_structure The window structure to initialize
 * 
 * @return void
 */
static void init_window_structure(struct WindowStructure* window_structure) {
    // PROVISIONAL!!
    gtk_container_add(GTK_CONTAINER(window_structure->window), window_structure->tree_view);
    
    // If there is a file in session, it is loaded
    if (window_structure->tree_path_file != NULL) {
        read_tree_file(window_structure->tree_view, window_structure->tree_path_file);
    }

    // // Vertical divider
    // GtkWidget* paned;

    // // Scrolleable container for the treeview
    // GtkWidget* scrolled_window;

    // // Create the menu_bar
    // window_structure->menu_bar = new_menu_bar(window_structure);
    // agregar_widget_box(window_structure->main_box, window_structure->menu_bar->main_widget, FALSE, FALSE, 0);

    // // Create the GtkPaned (divider)
    // paned = crear_paned_horizontal();
    // agregar_widget_box(window_structure->main_box, paned, TRUE, TRUE, 0);

    // Include the progress bar
    window_structure->progress_bar = gtk_progress_bar_new();
    agregar_widget_box(window_structure->main_box, window_structure->progress_bar, FALSE, FALSE, 0);

    // // Create the content for the left side of the divider (the scrolled window)
    // scrolled_window = init_scrolled_window();
    // agregar_widget_paned_izquierda(paned, scrolled_window, TRUE, FALSE);

    // // Add the tree to the scrolled window
    // add_widget_to_scrolled_window(scrolled_window, window_structure->tree_view);

    // // Create content for the right area of the divider
    // GtkWidget *right_label_panel = gtk_label_new("Contenido derecho");
    // agregar_widget_paned_derecha(paned, right_label_panel, TRUE, FALSE);

    // // Initialize the keyboard shortcuts
    // init_keyboard_shortcuts(window_structure);
}

/**
 * @brief Closes a WindowStructure*.
 * 
 * @param window_structure The WindowStructure to close.
 * 
 * @return void
 */
void close_window_structure(struct WindowStructure* window_structure) {
    // // Free the structures
    // close_history(window_structure->history);
    // close_menu_bar(window_structure->menu_bar);
    
    g_free(window_structure->tree_path_file);
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