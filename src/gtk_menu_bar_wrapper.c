#include <gtk/gtk.h>

#include "gtk_menu_bar_wrapper.h"
#include "history.h"
#include "tree_wrapper.h"
#include "window_manager.h"

/**
 * @brief Adds a tab to the menu bar.
 * 
 * @param menu_bar Menu bar.
 * @param name Name of the tab.
 * 
 * @return GtkWidget*
*/
GtkWidget* add_menu_bar_tab(GtkWidget *menu_bar, const char *name) {
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
struct MenuBar* new_menu_bar(struct WindowStructure* window_structure) {
    // Get the window
    GtkWidget* window = window_structure->window;

    // Create the menu
    struct MenuBar* menu_bar = g_new(struct MenuBar, 1);

    // Create the menu
    GtkWidget *menu_bar_widget = gtk_menu_bar_new();

    // Create the tabs and add the elements and separators
    GtkWidget *menu_file = add_menu_bar_tab(menu_bar_widget, "Archivo");
    menu_bar->new_file = add_menu_bar_item(menu_file, "Nuevo");
    menu_bar->open_file = add_menu_bar_item(menu_file, "Abrir");
    menu_bar->save = add_menu_bar_item(menu_file, "Guardar");
    add_menu_bar_separator(menu_file);
    menu_bar->close_window = add_menu_bar_item(menu_file, "Cerrar Ventana");

    add_menu_bar_separator(menu_file);
    menu_bar->exit = add_menu_bar_item(menu_file, "Salir");

    GtkWidget *menu_edit = add_menu_bar_tab(menu_bar_widget, "Editar");
    menu_bar->undo = add_menu_bar_item(menu_edit, "Deshacer");
    menu_bar->redo = add_menu_bar_item(menu_edit, "Rehacer");
    add_menu_bar_separator(menu_edit);
    menu_bar->delete = add_menu_bar_item(menu_edit, "Eliminar");

    GtkWidget *menu_tools = add_menu_bar_tab(menu_bar_widget, "Ayuda");
    menu_bar->show_window_information = add_menu_bar_item(menu_tools, "Mostrar información de la ventana");

    // Connect the signals
    g_signal_connect(menu_bar->new_file, "activate", G_CALLBACK(create_new_window), NULL);
    g_signal_connect(menu_bar->open_file, "activate", G_CALLBACK(open_tree_file), window_structure);
    g_signal_connect(menu_bar->save, "activate", G_CALLBACK(save_tree), window_structure);
    g_signal_connect(menu_bar->close_window, "activate", G_CALLBACK(close_window), window_structure);
    g_signal_connect(menu_bar->exit, "activate", G_CALLBACK(close_window), window_structure);

    g_signal_connect(menu_bar->undo, "activate", G_CALLBACK(undo), window_structure);
    g_signal_connect(menu_bar->redo, "activate", G_CALLBACK(redo), window_structure);
    g_signal_connect(menu_bar->delete, "activate", G_CALLBACK(delete_selected_node), window_structure);

    g_signal_connect(menu_bar->show_window_information, "activate", G_CALLBACK(show_window_info), window);

    menu_bar->main_widget = menu_bar_widget;

    return menu_bar;
}

/**
 * @brief Closes the menu bar.
 * 
 * @param menu_bar Menu bar to close
 * 
 * @return void
 */
void close_menu_bar(struct MenuBar* menu_bar) {
    g_free(menu_bar);
}