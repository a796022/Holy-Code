#include <gtk/gtk.h>

#include "window.h"
#include "tree.h"

int main(int argc, char *argv[]) {
    // Ventana principal
    GtkWidget *window;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear y configurar la ventana
    window = crear_ventana();
    establecer_nombre_ventana(window, "Wizard");
    establecer_tamano_por_defecto_ventana(window, 300, 200);
    establecer_redimensionable_ventana(window, TRUE);
    establecer_tamano_minimo_ventana(window, 300, 200);
    establecer_terminar_programa_cerrado_ventana(window);

    // Mostrar la ventana
    mostrar_ventana(window);

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}
