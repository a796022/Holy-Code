#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <gtk/gtk.h>

#include "window.h"

extern GtkWidget *MAIN_WINDOW;

void inicializar_ventana_principal(GtkWidget *box);

void mostrar_ventana_principal();

void cerrar_ventana_principal();

void mostrar_ventana_info_ventana();

#endif /* WINDOW_MANAGER_H */