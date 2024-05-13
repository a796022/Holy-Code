#ifndef PANED_MANAGER_H
#define PANED_MANAGER_H

/**
 * Crea un paned dividido horizontalmente y lo devuelve.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_paned_horizontal();

/**
 * Crea un paned dividido verticalmente y lo devuelve.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_paned_vertical();

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
void agregar_widget_paned_izquierda(GtkWidget *paned, GtkWidget *widget, gboolean resize, gboolean shrink);

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
void agregar_widget_paned_derecha(GtkWidget *paned, GtkWidget *widget, gboolean resize, gboolean shrink);

#endif /* PANED_MANAGER_H */