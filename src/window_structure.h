#ifndef WINDOW_STRUCTURE_H
#define WINDOW_STRUCTURE_H

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
 * @brief Initializes the window structure.
 * 
 * @return struct WindowStructure The initialized window structure
 */
struct WindowStructure* init_window_structure();

#endif /* WINDOW_STRUCTURE_H */