#include <gtk/gtk.h>

#include "window.h"
#include "window_manager.h"
#include "box.h"

const char *NOMBRE_VENTANA = "Wizard";
const int ANCHO_VENTANA = 900;
const int ALTO_VENTANA = 500;
const gboolean REDIMENSIONABLE = TRUE;
const int ANCHO_MINIMO_VENTANA = 300;
const int ALTO_MINIMO_VENTANA = 200;

GtkWidget *MAIN_WINDOW;

/**
 * Inicializa la ventana principal.
 * 
 * @param box Caja principal que contendrá el resto de widgets.
 * 
 * @return void
*/
GtkWidget *inicializar_ventana_principal() {
    // Caja que contendrá todos los widgets
    GtkWidget *main_vbox;

    // Crear y configurar la ventana
    MAIN_WINDOW = crear_ventana();
    establecer_nombre_ventana(MAIN_WINDOW, "Wizard");
    establecer_tamano_por_defecto_ventana(MAIN_WINDOW, 900, 500);
    establecer_redimensionable_ventana(MAIN_WINDOW, TRUE);
    establecer_tamano_minimo_ventana(MAIN_WINDOW, 300, 200);
    establecer_terminar_programa_cerrado_ventana(MAIN_WINDOW);

    // Crear un contenedor de caja vertical para el menu_bar y lo demás
    main_vbox = crear_box(GTK_ORIENTATION_VERTICAL, 0);

    // Agregar el contenedor principal a la ventana
    agregar_widget_ventana(MAIN_WINDOW, main_vbox);

    return main_vbox;
}

/**
 * Muestra la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_principal() {
    mostrar_ventana(MAIN_WINDOW);
}

/**
 * Cierra la ventana principal.
 * 
 * @return void
*/
void cerrar_ventana_principal() {
    cerrar_ventana(MAIN_WINDOW);
}

/**
 * Obtiene el ancho de la ventana principal.
 * 
 * @return int
*/
int obtener_ancho_ventana_principal() {
    return obtener_ancho_ventana(GTK_WINDOW(MAIN_WINDOW));
}

/**
 * Obtiene el alto de la ventana principal.
 * 
 * @return int
*/
int obtener_alto_ventana_principal() {
    return obtener_alto_ventana(GTK_WINDOW(MAIN_WINDOW));
}

/**
 * Muestra una ventana emergente con la información del ancho y alto de la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_info_ventana() {
    const int ancho = obtener_ancho_ventana_principal();
    const int alto = obtener_alto_ventana_principal();

    char mensaje[100]; // Ajusta el tamaño según sea necesario
    sprintf(mensaje,    "Anchura: %dpx\n"
                        "Altura: %dpx",
                        ancho, alto);
    
    const char* titulo = "Información de la ventana";
    
    mostrar_dialogo(MAIN_WINDOW, mensaje, titulo);
}