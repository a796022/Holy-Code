#include "window_manager.h"

const char *NOMBRE_VENTANA = "Wizard";
const int ANCHO_VENTANA = 900;
const int ALTO_VENTANA = 500;
const gboolean REDIMENSIONABLE = TRUE;
const int ANCHO_MINIMO_VENTANA = 300;
const int ALTO_MINIMO_VENTANA = 200;

GtkWidget *main_window;

// Inicializa la ventana con el widget pasado por parámetro
void inicializar_ventana_principal(GtkWidget *box) {
    // Crear y configurar la ventana
    main_window = crear_ventana();
    establecer_nombre_ventana(main_window, "Wizard");
    establecer_tamano_por_defecto_ventana(main_window, 900, 500);
    establecer_redimensionable_ventana(main_window, TRUE);
    establecer_tamano_minimo_ventana(main_window, 300, 200);
    establecer_terminar_programa_cerrado_ventana(main_window);

    // Agregar el componente principal a la ventana
    agregar_widget_ventana(main_window, box);
}

// Muestra la ventana principal
void mostrar_ventana_principal() {
    mostrar_ventana(main_window);
}

// Cerrar la ventana principal
void cerrar_ventana_principal() {
    cerrar_ventana(main_window);
}