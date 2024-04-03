#include "box.h"

/**
 * orientation: GTK_ORIENTATION_HORIZONTAL o GTK_ORIENTATION_VERTICAL
 * spacing: Espacio entre los widgets hijos
*/
GtkWidget *crear_box(GtkOrientation orientation, int spacing) {
    GtkWidget *box = gtk_box_new(orientation, spacing);
    return box;
}

/**
 * box: Contenedor de caja
 * widget: Widget a agregar
 * expand: TRUE si el widget debe expandirse para ocupar todo el espacio disponible
 * fill: TRUE si el widget debe rellenar todo el espacio disponible
 * padding: Espacio entre el widget y los demás widgets hijos
*/
void agregar_widget_box(GtkWidget *box, GtkWidget *widget, gboolean expand, gboolean fill, guint padding) {
    gtk_box_pack_start(GTK_BOX(box), widget, expand, fill, padding);
}