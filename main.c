#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkCssProvider *provider;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear una nueva ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Wizard");
    
    // Establecer el tamaño mínimo de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE); // Permitir que la ventana sea redimensionable

    // Establecer el tamaño mínimo de la ventana
    gtk_widget_set_size_request(window, 300, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Agregación de widgets
    // ...

    // Mostrar la ventana
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}
