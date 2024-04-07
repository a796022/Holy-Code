#ifndef MENU_BAR
#define MENU_BAR

/**
 * Crea y devuelve un menú de barra.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_menu_bar();

/**
 * Agrega una pestaña al menú de barra.
 * 
 * @param menu_bar Menú de barra.
 * @param nombre Nombre de la pestaña.
 * 
 * @return GtkWidget*
*/
GtkWidget *agregar_pestania_menu_bar(GtkWidget *menu_bar, const char *nombre);

/**
 * Agrega un elemento a una pestaña del menú de barra.
 * 
 * @param pestaña Pestaña del menú de barra.
 * @param nombre Nombre del elemento.
 * 
 * @return GtkWidget*
*/
GtkWidget *agregar_elemento_menu_bar(GtkWidget *pestaña, const char *nombre);

#endif /* MENU_BAR */