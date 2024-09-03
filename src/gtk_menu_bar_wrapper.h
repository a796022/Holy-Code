#pragma once

#include <gtk/gtk.h>

#include "window_structure.h"

// "Archivo" Menu
extern GtkWidget *MENUBAR_NEW_FILE;
extern GtkWidget *MENUBAR_SAVE;
extern GtkWidget *MENUBAR_OPEN_FILE;
extern GtkWidget *MENUBAR_CLOSE_WINDOW;
extern GtkWidget *MENUBAR_EXIT;

// "Editar" Menu
extern GtkWidget *MENUBAR_UNDO;
extern GtkWidget *MENUBAR_REDO;
extern GtkWidget *MENUBAR_DELETE;

// "Ayuda" Menu
extern GtkWidget *MENUBAR_SHOW_WINDOW_INFORMATION;

/**
 * @brief Initializes the main window menu.
 * 
 * - Creates the menu.
 * - Creates the tabs and adds the elements.
 * - Connects the signals.
 * 
 * @param window window to which the menu will be added.
 * 
 * @return GtkWidget* Menu bar
*/
GtkWidget *init_menu_bar(struct WindowStructure* window_structure);