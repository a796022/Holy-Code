#include <gtk/gtk.h>

#include "gtk_box_manager.h"
#include "gtk_menu_bar_wrapper.h"
#include "gtk_progress_bar.h"
#include "gtk_scrolled_window_wrapper.h"
#include "GtkAccelGroup_wrapper.h"
#include "paned_manager.h"
#include "tree_wrapper.h"
#include "window_manager.h"
#include "window_structure.h"

/**
 * @brief Creates a new empty window structure.
 * 
 * @return struct WindowStructure The new empty window structure
 */
struct WindowStructure* new_window_structure() {
    // Reserve memory for the new window structure
    struct WindowStructure* window_structure = g_malloc(sizeof(struct WindowStructure));

    // Initialize the window structure
    window_structure->window = NULL;
    window_structure->tree_view = NULL;
    window_structure->tree_model = NULL;
    window_structure->main_box = NULL;

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
    // Top menu
    GtkWidget* menu_bar;

    // Vertical divider
    GtkWidget* paned;

    // Scrolleable container for the treeview
    GtkWidget* scrolled_window;

    // Create and configure the window
    init_window(window_structure);

    // Create the main box
    init_box(window_structure);

    // Create the tree
    init_main_tree(window_structure);

    // Create the menu_bar
    menu_bar = init_menu_bar(window_structure);
    agregar_widget_box(window_structure->main_box, menu_bar, FALSE, FALSE, 0);

    // Create the GtkPaned (divider)
    paned = crear_paned_horizontal();
    agregar_widget_box(window_structure->main_box, paned, TRUE, TRUE, 0);

    // Include the progress bar
    init_progress_bar();
    agregar_widget_box(window_structure->main_box, MAIN_PROGRESS_BAR, FALSE, FALSE, 0);

    // Create the content for the left side of the divider (the scrolled window)
    scrolled_window = init_scrolled_window();
    agregar_widget_paned_izquierda(paned, scrolled_window, TRUE, FALSE);

    // Add the tree to the scrolled window
    add_widget_to_scrolled_window(scrolled_window, window_structure->tree_view);

    // Create content for the right area of the divider
    GtkWidget *right_label_panel = gtk_label_new("Contenido derecho");
    agregar_widget_paned_derecha(paned, right_label_panel, TRUE, FALSE);

    // Initialize the keyboard shortcuts
    init_keyboard_shortcuts(window_structure->window);

    // Show the window
    show_window(window_structure->window);
}

/**
 * @brief Closes the window structure.
 * 
 * @param window_structure The window structure to close
 * 
 * @return void
 */
void close_window_structure(struct WindowStructure* window_structure) {
    // Destroy the widgets (so the memory they use is freed)
    gtk_widget_destroy(window_structure->window);

    // Unreference the tree model (so the memory it uses is freed)
    g_object_unref(window_structure->tree_model);

    // Free the memory allocated for the window structure
    g_free(window_structure);
}