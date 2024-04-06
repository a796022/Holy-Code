#include "atajos_teclado.h"
#include "window_manager.h"

/**
 * Crea un grupo de aceleración para la ventana.
 * 
 * @param window Ventana a la que se le asociará el grupo de aceleración.
 * 
 * @return GtkAccelGroup*
*/
GtkAccelGroup *crear_grupo_aceleracion(GtkWindow *window) {
    GtkAccelGroup *accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(window, accel_group);

    return accel_group;
}

/**
 * Asocia un atajo de teclado a una señal de un widget.
 * 
 * @param accel_group Grupo de aceleración al que se asociará el atajo de teclado.
 * @param widget Widget al que se le asociará el atajo de teclado.
 * @param senial Señal a la que se asociará el atajo de teclado.
 * @param key Tecla que activará el atajo de teclado.
 * @param modifiers Modificadores de teclado que activarán el atajo de teclado.
 * 
 * @return void
*/
void asociar_atajo_senial(GtkAccelGroup *accel_group, GtkWidget *widget, const gchar *senial, guint key, GdkModifierType modifiers) {
    gtk_widget_add_accelerator(widget, senial, accel_group, key, modifiers, GTK_ACCEL_VISIBLE);
}