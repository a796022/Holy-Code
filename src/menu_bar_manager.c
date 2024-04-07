#include <gtk/gtk.h>

#include "menu_bar_manager.h"
#include "menu_bar.h"
#include "window_manager.h"
#include "tree_manager.h"

// Menú "Archivo"
GtkWidget *MENUBAR_ABRIR;
GtkWidget *MENUBAR_SALIR;

// Menú "Ayuda"
GtkWidget *MENUBAR_MOSTRAR_INFO_VENTANA;

/**
 * Carga el árbol de la ventana principal de un fichero.
 * 
 * @return void
*/
void abrir() {
    cargar_arbol_principal();
}

/**
 * Cierra la ventana principal.
 * 
 * @return void
*/
void salir() {
    cerrar_ventana_principal();
}

/**
 * Muestra una ventana emergente con la información del ancho y alto de la ventana principal.
 * 
 * @return void
*/
void mostrar_info_ventana() {
    mostrar_ventana_info_ventana();
}

/**
 * Inicializa el menú de la ventana principal.
 * 
 * @return GtkWidget*
*/
GtkWidget *inicializar_menu_bar_ventana_principal() {
    // Crear el menú
    GtkWidget *menu_bar_ventana_principal = crear_menu_bar();

    // Crear las pestañas y agregar los elementos
    GtkWidget *menu_file = agregar_pestania_menu_bar(menu_bar_ventana_principal, "Archivo");
    MENUBAR_ABRIR = agregar_elemento_menu_bar(menu_file, "Abrir");
    MENUBAR_SALIR = agregar_elemento_menu_bar(menu_file, "Salir");

    GtkWidget *menu_tools = agregar_pestania_menu_bar(menu_bar_ventana_principal, "Ayuda");
    MENUBAR_MOSTRAR_INFO_VENTANA = agregar_elemento_menu_bar(menu_tools, "Mostrar información de la ventana");

    // Conectar las señales
    g_signal_connect(MENUBAR_ABRIR, "activate", G_CALLBACK(abrir), NULL);
    g_signal_connect(MENUBAR_SALIR, "activate", G_CALLBACK(salir), NULL);
    g_signal_connect(MENUBAR_MOSTRAR_INFO_VENTANA, "activate", G_CALLBACK(mostrar_info_ventana), NULL);

    return menu_bar_ventana_principal;
}