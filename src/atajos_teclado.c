#include "atajos_teclado.h"
#include "window_manager.h"

/**
 * Asocia un atajo de teclado a una señal de un widget.
 * 
 * @param widget Widget al que se le asociará el atajo de teclado.
 * @param senial Señal a la que se asociará el atajo de teclado.
 * @param key Tecla que activará el atajo de teclado.
 * @param modifiers Modificadores de teclado que activarán el atajo de teclado.
 * 
 * @return void
*/
void asociar_atajo_senial(GtkWidget *widget, const gchar *senial, guint key, GdkModifierType modifiers) {
    GtkAccelGroup *accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(MAIN_WINDOW), accel_group);
    gtk_widget_add_accelerator(widget, senial, accel_group, key, modifiers, GTK_ACCEL_VISIBLE);
}