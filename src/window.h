#ifndef WINDOW_H
#define WINDOW_H

/**
 * Crea y devuelve una ventana.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_ventana();

/**
 * Establece el nombre de la ventana, que se mostrará en la barra de título.
 * 
 * @param window Ventana a la que se le establecerá el nombre.
 * @param nombre Nombre de la ventana.
 * 
 * @return void
*/
void establecer_nombre_ventana(GtkWidget *window, const char *nombre);

/**
 * Establece el tamaño por defecto de la ventana.
 * 
 * @param window Ventana a la que se le establecerá el tamaño por defecto.
 * @param ancho Ancho de la ventana.
 * @param alto Alto de la ventana.
 * 
 * @return void
*/
void establecer_tamano_por_defecto_ventana(GtkWidget *window, int ancho, int alto);

/**
 * Establece si la ventana es redimensionable.
 * 
 * @param window Ventana a la que se le establecerá si es redimensionable.
 * @param redimensionable TRUE si la ventana es redimensionable, FALSE en caso contrario.
 * 
 * @return void
*/
void establecer_redimensionable_ventana(GtkWidget *window, gboolean redimensionable);

/**
 * Establece el tamaño mínimo de la ventana.
 * 
 * @param window Ventana a la que se le establecerá el tamaño mínimo.
 * @param ancho Ancho mínimo de la ventana.
 * @param alto Alto mínimo de la ventana.
 * 
 * @return void
*/
void establecer_tamano_minimo_ventana(GtkWidget *window, int ancho, int alto);

/**
 * Conecta la señal "destroy" de la ventana a la función gtk_main_quit() para que, cuando se cierre la ventana, también se termine el bucle principal de eventos de GTK (y por lo tanto, termine el programa).
 * 
 * @param window Ventana a la que se le establecerá la señal "destroy".
 * 
 * @return void
*/
void establecer_terminar_programa_cerrado_ventana(GtkWidget *window);

/**
 * Agrega un widget a la ventana.
 * 
 * @param window Ventana a la que se le agregará el widget.
 * @param widget Widget a agregar.
 * 
 * @return void
*/
void agregar_widget_ventana(GtkWidget *window, GtkWidget *widget);

/**
 * Muestra la ventana.
 * 
 * @param window Ventana a mostrar.
 * 
 * @return void
*/
void mostrar_ventana(GtkWidget *window);

/**
 * Cierra la ventana.
 * 
 * @param window Ventana a cerrar.
 * 
 * @return void
*/
void cerrar_ventana(GtkWidget *window);

/**
 * Muestra un diálogo general y devuelve la respuesta.
 * 
 * @param dialog Diálogo a mostrar.
 * 
 * @return gint
*/
gint mostrar_dialogo(GtkWidget *dialog);

/**
 * Muestra un diálogo con un mensaje.
 * 
 * @param window Ventana a la que se asociará el diálogo.
 * @param mensaje Mensaje a mostrar en el diálogo.
 * @param titulo Título del diálogo.
 * 
 * @return void
*/
void mostrar_dialogo_mensaje(GtkWidget *window, const char *mensaje, const char *titulo);

/**
 * Obtiene el ancho de la ventana.
 * 
 * @param window Ventana de la que se obtendrá el ancho.
 * 
 * @return int
*/
int obtener_ancho_ventana(GtkWindow *window);

/**
 * Obtiene el alto de la ventana.
 * 
 * @param window Ventana de la que se obtendrá el alto.
 * 
 * @return int
*/
int obtener_alto_ventana(GtkWindow *window);

/**
 * Crea un diálogo selector de archivos.
 * 
 * @param parent Ventana padre del diálogo.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_dialogo_selector_archivos(GtkWidget *parent);

/**
 * Obtiene el fichero seleccionado de un diálogo selector.
 * 
 * @param dialog Diálogo selector de archivos.
 * 
 * @return char*
*/
char *obtener_fichero_seleccionado(GtkWidget *dialog);

#endif /* WINDOW_H */