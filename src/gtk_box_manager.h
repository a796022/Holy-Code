#pragma once

#include <gtk/gtk.h>

#include "window_manager.h"

/**
 * Crea un contenedor de caja.
 * 
 * @param orientation Orientación de la caja (GTK_ORIENTATION_HORIZONTAL o GTK_ORIENTATION_VERTICAL).
 * @param spacing Espacio entre los widgets hijos.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_box(GtkOrientation orientation, int spacing);

/**
 * Agrega un widget a un contenedor de caja.
 * 
 * @param box Contenedor de caja.
 * @param widget Widget a agregar.
 * @param expand TRUE si el widget debe expandirse para ocupar todo el espacio disponible.
 * @param fill TRUE si el widget debe rellenar todo el espacio disponible.
 * @param padding Espacio entre el widget y los demás widgets hijos.
 * 
 * @return void
*/
void agregar_widget_box(GtkWidget *box, GtkWidget *widget, gboolean expand, gboolean fill, guint padding);