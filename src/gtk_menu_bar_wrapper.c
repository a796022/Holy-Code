#include <gtk/gtk.h>

#include "window_manager.h"
#include "tree_wrapper.h"
#include "history.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Adds a tab to the menu bar.
 * 
 * @param menu_bar Menu bar.
 * @param name Name of the tab.
 * 
 * @return GtkWidget*
*/
GtkWidget *add_menu_bar_tab(GtkWidget *menu_bar, const char *name) {
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *menu_item = gtk_menu_item_new_with_label(name);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    return menu;
}

/**
 * @brief Adds an element to a tab of the menu bar.
 * 
 * @param tab Tab of the menu bar.
 * @param name Name of the element.
 * 
 * @return GtkWidget*
*/
GtkWidget *add_menu_bar_item(GtkWidget *tab, const char *name) {
    GtkWidget *menu_item = gtk_menu_item_new_with_label(name);
    gtk_menu_shell_append(GTK_MENU_SHELL(tab), menu_item);

    return menu_item;
}

/**
 * @brief Adds a separator to a tab of the menu bar.
 * 
 * @param tab Tab of the menu bar.
 * 
 * @return void
 */
void add_menu_bar_separator(GtkWidget *tab) {
    GtkWidget *separator = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(tab), separator);
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// "Archivo" Menu
GtkWidget *MENUBAR_NEW_FILE;
GtkWidget *MENUBAR_OPEN_FILE;
GtkWidget *MENUBAR_SAVE;
GtkWidget *MENUBAR_CLOSE_WINDOW;
GtkWidget *MENUBAR_EXIT;

// "Editar" Menu
GtkWidget *MENUBAR_UNDO;
GtkWidget *MENUBAR_REDO;
GtkWidget *MENUBAR_DELETE;

// "Ayuda" Menu
GtkWidget *MENUBAR_SHOW_WINDOW_INFORMATION;

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
GtkWidget *init_menu_bar(GtkWidget *window) {
    // Create the menu
    GtkWidget *menu_bar = gtk_menu_bar_new();

    // Create the tabs and add the elements and separators
    GtkWidget *menu_file = add_menu_bar_tab(menu_bar, "Archivo");
    MENUBAR_NEW_FILE = add_menu_bar_item(menu_file, "Nuevo");
    MENUBAR_OPEN_FILE = add_menu_bar_item(menu_file, "Abrir");
    MENUBAR_SAVE = add_menu_bar_item(menu_file, "Guardar");
    add_menu_bar_separator(menu_file);
    MENUBAR_CLOSE_WINDOW = add_menu_bar_item(menu_file, "Cerrar Ventana");

    add_menu_bar_separator(menu_file);
    MENUBAR_EXIT = add_menu_bar_item(menu_file, "Salir");

    GtkWidget *menu_edit = add_menu_bar_tab(menu_bar, "Editar");
    MENUBAR_UNDO = add_menu_bar_item(menu_edit, "Deshacer");
    MENUBAR_REDO = add_menu_bar_item(menu_edit, "Rehacer");
    add_menu_bar_separator(menu_edit);
    MENUBAR_DELETE = add_menu_bar_item(menu_edit, "Eliminar");

    GtkWidget *menu_tools = add_menu_bar_tab(menu_bar, "Ayuda");
    MENUBAR_SHOW_WINDOW_INFORMATION = add_menu_bar_item(menu_tools, "Mostrar información de la ventana");

    // Connect the signals
    g_signal_connect(MENUBAR_NEW_FILE, "activate", G_CALLBACK(create_new_window), NULL);
    g_signal_connect(MENUBAR_OPEN_FILE, "activate", G_CALLBACK(open_tree_file), window);
    g_signal_connect(MENUBAR_SAVE, "activate", G_CALLBACK(save_tree), NULL);
    g_signal_connect(MENUBAR_CLOSE_WINDOW, "activate", G_CALLBACK(close_window), window);
    g_signal_connect(MENUBAR_EXIT, "activate", G_CALLBACK(close_window), window);

    g_signal_connect(MENUBAR_UNDO, "activate", G_CALLBACK(undo), NULL);
    g_signal_connect(MENUBAR_REDO, "activate", G_CALLBACK(redo), NULL);
    g_signal_connect(MENUBAR_DELETE, "activate", G_CALLBACK(delete_selected_node), NULL);

    g_signal_connect(MENUBAR_SHOW_WINDOW_INFORMATION, "activate", G_CALLBACK(show_window_info), window);

    return menu_bar;
}