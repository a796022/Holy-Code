#include <gtk/gtk.h>

GtkWidget *crear_ventana() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    return window;
}

void establecer_nombre_ventana(GtkWidget *window, const char *nombre) {
    gtk_window_set_title(GTK_WINDOW(window), nombre);
}

void establecer_tamano_por_defecto_ventana(GtkWidget *window, int ancho, int alto) {
    gtk_window_set_default_size(GTK_WINDOW(window), ancho, alto);
}

void establecer_redimensionable_ventana(GtkWidget *window, gboolean redimensionable) {
    gtk_window_set_resizable(GTK_WINDOW(window), redimensionable);
}

void establecer_tamano_minimo_ventana(GtkWidget *window, int ancho, int alto) {
    gtk_widget_set_size_request(window, ancho, alto);
}

// Conecta la señal "destroy" de la ventana a la función gtk_main_quit()
// Esto hace que cuando se cierre la ventana, también se termine el bucle
// principal de eventos de GTK (y por lo tanto, termine el programa)
void establecer_terminar_programa_cerrado_ventana(GtkWidget *window) {
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void agregar_widget_ventana(GtkWidget *window, GtkWidget *widget) {
    gtk_container_add(GTK_CONTAINER(window), widget);
}

void mostrar_ventana(GtkWidget *window) {
    gtk_widget_show_all(window);
}