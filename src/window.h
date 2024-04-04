#ifndef WINDOW_H
#define WINDOW_H

#include <gtk/gtk.h>

GtkWidget *crear_ventana();

void establecer_nombre_ventana(GtkWidget *window, const char *nombre);

void establecer_tamano_por_defecto_ventana(GtkWidget *window, int ancho, int alto);

void establecer_redimensionable_ventana(GtkWidget *window, gboolean redimensionable);

void establecer_tamano_minimo_ventana(GtkWidget *window, int ancho, int alto);

// Conecta la señal "destroy" de la ventana a la función gtk_main_quit()
// Esto hace que cuando se cierre la ventana, también se termine el bucle
// principal de eventos de GTK (y por lo tanto, termine el programa)
void establecer_terminar_programa_cerrado_ventana(GtkWidget *window);

void agregar_widget_ventana(GtkWidget *window, GtkWidget *widget);

void mostrar_ventana(GtkWidget *window);

void cerrar_ventana(GtkWidget *window);

#endif /* WINDOW_H */
