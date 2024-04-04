#include "window.h"

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

void establecer_terminar_programa_cerrado_ventana(GtkWidget *window) {
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void agregar_widget_ventana(GtkWidget *window, GtkWidget *widget) {
    gtk_container_add(GTK_CONTAINER(window), widget);
}

void mostrar_ventana(GtkWidget *window) {
    gtk_widget_show_all(window);
}

void cerrar_ventana(GtkWidget *window) {
    gtk_widget_destroy(window);
}

// Mostrar diálogo
void mostrar_dialogo(GtkWidget *window, const char *mensaje, const char *titulo) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               mensaje);

    if (titulo != NULL) {
        gtk_window_set_title(GTK_WINDOW(dialog), titulo);
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int obtener_ancho_ventana(GtkWindow *window) {
    gint width, height;
    gtk_window_get_size(window, &width, &height);
    return width;
}

int obtener_alto_ventana(GtkWindow *window) {
    gint width, height;
    gtk_window_get_size(window, &width, &height);
    return height;
}