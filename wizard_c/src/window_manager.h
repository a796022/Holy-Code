#pragma once

#include <gtk/gtk.h>

// #include "window_structure.h"

/**
 * @brief Initializes the GtkWidget* pointed by main_window as a new main
 * window.
 * 
 * @param main_window Pointer to the GtkWidget* that will be initialized as a
 * new main window.
 * 
 * @return void
*/
void new_main_window(GtkWidget** main_window);

// /**
//  * Muestra la ventana.
//  * 
//  * @param window Ventana a mostrar.
//  * 
//  * @return void
// */
// void show_window(struct WindowStructure* window_structure);

/**
 * @brief Closes the main window
 * 
 * - Displays a dialog asking the user if they want to save the changes if there are unsaved changes.
 * - The window is closed if the user chooses to save the changes or discard the changes.
 * 
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal.
 * 
 * @return void
*/
void close_window(GtkMenuItem *menuitem, gpointer user_data);

// /**
//  * @brief Show a popup window with the width and height information of the window.
//  * 
//  * @param menuitem Menu item that triggered the signal.
//  * @param user_data Data passed to the signal.
//  * 
//  * @return void
// */
// void show_window_info(GtkMenuItem *menuitem, gpointer user_data);

// /**
//  * @brief Shows a file selector window and returns the path of the selected file.
//  * 
//  * - Shows a file selector window.
//  * - Returns the path of the selected file.
//  * - If the user has not selected a file, returns NULL.
//  * 
//  * @param window Window to which the dialog will be associated.
//  * 
//  * @return char*
// */
// char *show_file_selector_window(GtkWidget *window);

// /**
//  * @brief Sets the title of the window as unsaved.
//  * 
//  * - Add a bullet and a space (• ) at the beginning of the title.
//  * 
//  * @return void
//  */
// void set_title_unsaved();

// /**
//  * @brief Sets the title of the window as saved.
//  * 
//  * - Remove the bullet and the space (• ) at the beginning of the title.
//  * 
//  * @return void
//  */
// void set_title_as_saved(GtkWidget *window);

// /**
//  * @brief Creates a new window with an empty tree proyect (no file is associated).
//  * 
//  * @return void
//  */
// void create_new_window();