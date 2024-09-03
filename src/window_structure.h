#pragma once

#include <gtk/gtk.h>

struct WindowStructure {
    // Window widget
    GtkWidget* window;

    // Visualization and data model of the tree
    GtkWidget* tree_view;
    GtkTreeStore* tree_model;

    // Main box widget that contains the rest of the widgets
    GtkWidget *main_box;
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