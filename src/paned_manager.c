#include <gtk/gtk.h>

#include "paned_manager.h"

/**
 * Crea un paned dividido horizontalmente y lo devuelve.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_paned_horizontal() {
    return gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
}

/**
 * Crea un paned dividido verticalmente y lo devuelve.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_paned_vertical() {
    return gtk_paned_new(GTK_ORIENTATION_VERTICAL);
}

/**
 * Agrega un widget a la parte izquierda del paned.
 * 
 * @param paned Paned.
 * @param widget Widget a agregar.
 * @param resize TRUE si el widget debe redimensionarse.
 * @param shrink TRUE si el widget debe reducirse.
 * 
 * @return void
*/
void agregar_widget_paned_izquierda(GtkWidget *paned, GtkWidget *widget, gboolean resize, gboolean shrink) {
    gtk_paned_pack1(GTK_PANED(paned), widget, resize, shrink);
}

/**
 * Agrega un widget a la parte derecha del paned.
 * 
 * @param paned Paned.
 * @param widget Widget a agregar.
 * @param resize TRUE si el widget debe redimensionarse.
 * @param shrink TRUE si el widget debe reducirse.
 * 
 * @return void
*/
void agregar_widget_paned_derecha(GtkWidget *paned, GtkWidget *widget, gboolean resize, gboolean shrink) {
    gtk_paned_pack2(GTK_PANED(paned), widget, resize, shrink);
}