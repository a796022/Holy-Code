#ifndef ATAJOS_TECLADO_H
#define ATAJOS_TECLADO_H

#include <gtk/gtk.h>

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
void asociar_atajo_senial(GtkWidget *widget, const gchar *senial, guint key, GdkModifierType modifiers);

#endif /* ATAJOS_TECLADO_H */