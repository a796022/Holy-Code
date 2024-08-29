#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <gtk/gtk.h>

// List of windows
extern GList *WINDOWS_LIST;

/**
 * @brief Runs a function for all windows.
 * 
 * - The function is executed for all windows.
 * - The function receives the window and the data as arguments.
 * 
 * @param funcion Function to run for all windows.
 * @param datos Data to pass to the function.
 * 
 * @return void
 */
void run_for_all_windows(void (*funcion)(GtkWidget*, void*), void *datos);

/**
 * @brief Initializes the main window.
 * 
 * @param window Reference to a pointer to GtkWidget. The pointer to the created window will be returned by reference in this variable.
 * 
 * @return GtkWidget* Main box that will contain the rest of the widgets.
*/
GtkWidget *init_window(GtkWidget **window);

/**
 * Muestra la ventana.
 * 
 * @param window Ventana a mostrar.
 * 
 * @return void
*/
void show_window(GtkWidget *window);

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

/**
 * @brief Show a popup window with the width and height information of the window.
 * 
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal.
 * 
 * @return void
*/
void show_window_info(GtkMenuItem *menuitem, gpointer user_data);

/**
 * @brief Shows a file selector window and returns the path of the selected file.
 * 
 * - Shows a file selector window.
 * - Returns the path of the selected file.
 * - If the user has not selected a file, returns NULL.
 * 
 * @param window Window to which the dialog will be associated.
 * 
 * @return char*
*/
char *show_file_selector_window(GtkWidget *window);

/**
 * @brief Sets the title of the window as unsaved.
 * 
 * - Add a bullet and a space (• ) at the beginning of the title.
 * 
 * @return void
 */
void set_title_unsaved();

/**
 * @brief Sets the title of the window as saved.
 * 
 * - Remove the bullet and the space (• ) at the beginning of the title.
 * 
 * @return void
 */
void set_title_saved();

/**
 * @brief Creates a new window with an empty tree proyect (no file is associated).
 * 
 * @return void
 */
void create_new_window();

#endif /* WINDOW_MANAGER_H */