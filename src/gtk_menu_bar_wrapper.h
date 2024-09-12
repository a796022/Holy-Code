#pragma once

#include <gtk/gtk.h>

#include "window_structure.h"

struct MenuBar {
    // Widget
    GtkWidget *main_widget;

    // "Archivo" Menu
    GtkWidget *new_file;
    GtkWidget *save;
    GtkWidget *open_file;
    GtkWidget *close_window;
    GtkWidget *exit;

    // "Editar" Menu
    GtkWidget *undo;
    GtkWidget *redo;
    GtkWidget *delete;

    // "Ayuda" Menu
    GtkWidget *show_window_information;
};

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
struct MenuBar *new_menu_bar(struct WindowStructure* window_structure);