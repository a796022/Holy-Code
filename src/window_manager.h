#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

extern GtkWidget *MAIN_WINDOW;

/**
 * Inicializa la ventana principal.
 * 
 * @param box Caja principal que contendrá el resto de widgets.
 * 
 * @return void
*/
GtkWidget *inicializar_ventana_principal();

/**
 * Muestra la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_principal();

/**
 * Cierra la ventana principal.
 * 
 * @return void
*/
void cerrar_ventana_principal();

/**
 * Muestra una ventana emergente con la información del ancho y alto de la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_info_ventana();

/**
 * Muestra una ventana de selector de archivos y devuelve la ruta del archivo seleccionado.
 * 
 * @return char*
*/
char *mostrar_ventana_selector_archivos();

#endif /* WINDOW_MANAGER_H */