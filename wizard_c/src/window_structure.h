#pragma once

// #include <gtk/gtk.h>

struct WindowStructure {
    // struct History* history;
    // GtkWidget*  main_box;
    struct MenuBar* menu_bar;
    GtkWidget*  progress_bar;
    // GtkTreeStore*   tree_model;
    char*   tree_path_file;
    GtkWidget*  tree_view;
    GtkWidget*  window;
};

/**
 * @brief Initializes the WindowStructure* pointed by window_structure.
 * 
 * @param window_structure Pointer to the WindowStructure* to initialize.
 * 
 * @return void
 */
void new_window_structure(struct WindowStructure** window_structure);

// /**
//  * @brief Initializes the window structure.
//  * 
//  * @param window_structure The window structure to initialize
//  * 
//  * @return void
//  */
// void init_window_structure(struct WindowStructure* window_structure);

/**
 * @brief Closes a WindowStructure*.
 * 
 * @param window_structure The WindowStructure to close.
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