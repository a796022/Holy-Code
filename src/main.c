#include <gtk/gtk.h>

#include "window_manager.h"
#include "components_manager.h"

int main(int argc, char *argv[]) {
    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Inicializar los componentes de la ventana principal
    inicializar_componentes_ventana_principal();

    // Mostrar la ventana
    mostrar_ventana_principal();

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}