#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <gtk/gtk.h>

extern GtkWidget *MAIN_WINDOW;

/**
 * @brief Initializes the main window.
 * 
 * @param window Reference to a pointer to GtkWidget. The pointer to the created window will be returned by reference in this variable.
 * 
 * @return GtkWidget* Main box that will contain the rest of the widgets.
*/
GtkWidget *init_window(GtkWidget **window);

/**
 * Muestra la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_principal();

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
 * Muestra una ventana emergente con la información del ancho y alto de la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_info_ventana();

/**
 * Muestra una ventana de selector de archivos y devuelve la ruta del archivo seleccionado.
 * 
 * @return char*
*/
char *mostrar_ventana_selector_archivos();

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