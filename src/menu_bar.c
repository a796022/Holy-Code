#include <gtk/gtk.h>

#include "menu_bar.h"

GtkWidget *crear_menu_bar() {
    GtkWidget *menu_bar = gtk_menu_bar_new();
    return menu_bar;
}

// Agregar pestaña a la barra de menú
GtkWidget *agregar_pestania_menu_bar(GtkWidget *menu_bar, const char *nombre) {
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *menu_item = gtk_menu_item_new_with_label(nombre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    return menu;
}

// Agregar elemento a la pestaña
GtkWidget *agregar_elemento_menu_bar(GtkWidget *pestaña, const char *nombre) {
    GtkWidget *menu_item = gtk_menu_item_new_with_label(nombre);
    gtk_menu_shell_append(GTK_MENU_SHELL(pestaña), menu_item);

    return menu_item;
}