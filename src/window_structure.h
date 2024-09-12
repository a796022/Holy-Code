#pragma once

#include <gtk/gtk.h>

struct WindowStructure {
    // Window widget
    GtkWidget* window;

    // Visualization and data model of the tree
    GtkWidget* tree_view;
    GtkTreeStore* tree_model;

    // Menu bar
    struct MenuBar *menu_bar;

    // Main box widget that contains the rest of the widgets
    GtkWidget *main_box;

    // History of operations
    struct History *history;
};

/**
 * @brief Creates a new empty window structure.
 * 
 * @return struct WindowStructure The new empty window structure
 */
struct WindowStructure* new_window_structure();

/**
 * @brief Initializes the window structure.
 * 
 * @param window_structure The window structure to initialize
 * 
 * @return void
 */
void init_window_structure(struct WindowStructure* window_structure);

/**
 * @brief Closes the window structure.
 * 
 * @param window_structure The window structure to close
 * 
 * @return void
 */
void close_window_structure(struct WindowStructure* window_structure);

/**
 * @brief Tells the history that the changes have been saved and modifies the window title to reflect this.
 * 
 * @param window_structure Window structure where the changes have been saved
 * 
 * @return void
 */
void set_changes_as_saved(struct WindowStructure* window_structure);