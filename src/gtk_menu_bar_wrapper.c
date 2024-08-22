#include <gtk/gtk.h>

#include "window_manager.h"
#include "tree_manager.h"

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

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// "Archivo" Menu
GtkWidget *MENUBAR_SAVE;
GtkWidget *MENUBAR_OPEN_FILE;
GtkWidget *MENUBAR_EXIT;

// "Editar" Menu
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
 * @return GtkWidget* Menu bar
*/
GtkWidget *initialize_menu_bar_main_window() {
    // Create the menu
    GtkWidget *menu_bar_main_window = gtk_menu_bar_new();

    // Create the tabs and add the elements
    GtkWidget *menu_file = add_menu_bar_tab(menu_bar_main_window, "Archivo");
    MENUBAR_SAVE = add_menu_bar_item(menu_file, "Guardar");
    MENUBAR_OPEN_FILE = add_menu_bar_item(menu_file, "Abrir");
    MENUBAR_EXIT = add_menu_bar_item(menu_file, "Salir");

    GtkWidget *menu_edit = add_menu_bar_tab(menu_bar_main_window, "Editar");
    MENUBAR_DELETE = add_menu_bar_item(menu_edit, "Eliminar");

    GtkWidget *menu_tools = add_menu_bar_tab(menu_bar_main_window, "Ayuda");
    MENUBAR_SHOW_WINDOW_INFORMATION = add_menu_bar_item(menu_tools, "Mostrar información de la ventana");

    // Connect the signals
    g_signal_connect(MENUBAR_SAVE, "activate", G_CALLBACK(save_tree), NULL);
    g_signal_connect(MENUBAR_OPEN_FILE, "activate", G_CALLBACK(cargar_arbol_principal), NULL);
    g_signal_connect(MENUBAR_EXIT, "activate", G_CALLBACK(cerrar_ventana_principal), NULL);
    g_signal_connect(MENUBAR_DELETE, "activate", G_CALLBACK(delete_selected_node), NULL);
    g_signal_connect(MENUBAR_SHOW_WINDOW_INFORMATION, "activate", G_CALLBACK(mostrar_ventana_info_ventana), NULL);

    return menu_bar_main_window;
}