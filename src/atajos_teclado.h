#ifndef ATAJOS_TECLADO_H
#define ATAJOS_TECLADO_H

/**
 * Crea un grupo de aceleración para la ventana.
 * 
 * @param window Ventana a la que se le asociará el grupo de aceleración.
 * 
 * @return GtkAccelGroup*
*/
GtkAccelGroup *crear_grupo_aceleracion(GtkWindow *window);

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
void asociar_atajo_senial(GtkAccelGroup *accel_group, GtkWidget *widget, const gchar *senial, guint key, GdkModifierType modifiers);

#endif /* ATAJOS_TECLADO_H */