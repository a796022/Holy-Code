#include <gtk/gtk.h>

#include "window_manager.h"
#include "tree.h"
#include "menu_bar_manager.h"
#include "box.h"

int main(int argc, char *argv[]) {
    // Modelo de datos del arbol
    GtkTreeStore *model;

    // Widget del TreeView
    GtkWidget *tree_view;

    // Caja que contendrá la barra de menú y el resto de widgets
    GtkWidget *vbox;

    // Menú superior
    GtkWidget *menu_bar;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear un contenedor de caja vertical para el menu_bar y lo demás
    vbox = crear_box(GTK_ORIENTATION_VERTICAL, 0);

    // Crear y configurar la ventana
    inicializar_ventana_principal(vbox);

    // Crear el menu_bar
    menu_bar = inicializar_menu_bar_ventana_principal();

    // Agregar el menu_bar al contenedor de la caja vertical
    agregar_widget_box(vbox, menu_bar, FALSE, FALSE, 0);

    // Crear un modelo de árbol para el TreeView
    model = crear_modelo_datos_tree();

    // Agregar algunos elementos al modelo de árbol
    agregar_nodo_tree(model, NULL, "Elemento 1");
    agregar_nodo_tree(model, NULL, "Elemento 2");

    // Crear el TreeView
    tree_view = crear_tree_view(model);

    // Crear una columna para el TreeView
    crear_columna_tree_view(tree_view, "Elementos");

    // Agregar el TreeView al contenedor de la caja vertical
    agregar_widget_box(vbox, tree_view, TRUE, TRUE, 0);

    // Mostrar la ventana
    mostrar_ventana_principal();

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}