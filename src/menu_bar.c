#include <gtk/gtk.h>

#include "menu_bar.h"

/**
 * Crea y devuelve un menú de barra.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_menu_bar() {
    GtkWidget *menu_bar = gtk_menu_bar_new();
    return menu_bar;
}

/**
 * Agrega una pestaña al menú de barra.
 * 
 * @param menu_bar Menú de barra.
 * @param nombre Nombre de la pestaña.
 * 
 * @return GtkWidget*
*/
GtkWidget *agregar_pestania_menu_bar(GtkWidget *menu_bar, const char *nombre) {
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *menu_item = gtk_menu_item_new_with_label(nombre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    return menu;
}

/**
 * Agrega un elemento a una pestaña del menú de barra.
 * 
 * @param pestaña Pestaña del menú de barra.
 * @param nombre Nombre del elemento.
 * 
 * @return GtkWidget*
*/
GtkWidget *agregar_elemento_menu_bar(GtkWidget *pestaña, const char *nombre) {
    GtkWidget *menu_item = gtk_menu_item_new_with_label(nombre);
    gtk_menu_shell_append(GTK_MENU_SHELL(pestaña), menu_item);

    return menu_item;
}