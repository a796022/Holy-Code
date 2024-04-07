#include <gtk/gtk.h>

#include "atajos_teclado_manager.h"
#include "atajos_teclado.h"
#include "window_manager.h"
#include "menu_bar_manager.h"

// Grupos de aceleracion
GtkAccelGroup *main_window_accel_group;

/**
 * Inicializa los atajos de teclado de la aplicación
 * 
 * @return void
*/
void inicializar_atajos_teclado() {
    // Inicializar los grupos de aceleración (uno por ventana)
    main_window_accel_group = crear_grupo_aceleracion(GTK_WINDOW(MAIN_WINDOW));

    // Atajos de teclado de la ventana principal
    asociar_atajo_senial(main_window_accel_group, MENUBAR_SALIR, "activate", GDK_KEY_Q, GDK_CONTROL_MASK);
}