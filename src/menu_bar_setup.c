#include "menu_bar_setup.h"

void abrir() {
    g_print("Abrir\n");
}

void salir() {
    g_print("Salir\n");
}

void mostrar_info_ventana() {
    g_print("Mostrar información de la ventana\n");
}

GtkWidget *inicializar_menu_bar_ventana_principal() {
    // Crear el menú
    GtkWidget *menu_bar_ventana_principal = crear_menu_bar();

    // Crear las pestañas y agregar los elementos
    GtkWidget *menu_file = agregar_pestania_menu_bar(menu_bar_ventana_principal, "Archivo");
    GtkWidget *opcion_abrir = agregar_elemento_menu_bar(menu_file, "Abrir");
    GtkWidget *opcion_salir = agregar_elemento_menu_bar(menu_file, "Salir");

    GtkWidget *menu_tools = agregar_pestania_menu_bar(menu_bar_ventana_principal, "Ayuda");
    GtkWidget *opcion_mostrar_info_ventana = agregar_elemento_menu_bar(menu_tools, "Mostrar información de la ventana");

    // Conectar las señales
    g_signal_connect(opcion_abrir, "activate", G_CALLBACK(abrir), NULL);
    g_signal_connect(opcion_salir, "activate", G_CALLBACK(salir), NULL);
    g_signal_connect(opcion_mostrar_info_ventana, "activate", G_CALLBACK(mostrar_info_ventana), NULL);

    return menu_bar_ventana_principal;
}