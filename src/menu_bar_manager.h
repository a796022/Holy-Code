#ifndef MENU_BAR_MANAGER
#define MENU_BAR_MANAGER

#include <gtk/gtk.h>

#include "menu_bar.h"
#include "window_manager.h"

// Menú "Archivo"
extern GtkWidget *MENUBAR_ABRIR;
extern GtkWidget *MENUBAR_SALIR;

// Menú "Ayuda"
extern GtkWidget *MENUBAR_MOSTRAR_INFO_VENTANA;

GtkWidget *inicializar_menu_bar_ventana_principal();

#endif /* MENU_BAR_MANAGER */