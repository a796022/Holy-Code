#ifndef MENU_BAR
#define MENU_BAR

#include <gtk/gtk.h>

GtkWidget *crear_menu_bar();

GtkWidget *agregar_pestania_menu_bar(GtkWidget *menu_bar, const char *nombre);

GtkWidget *agregar_elemento_menu_bar(GtkWidget *pestaña, const char *nombre);

#endif /* MENU_BAR */