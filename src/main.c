#include <gtk/gtk.h>

#include "window.h"
#include "tree.h"
#include "menu_bar_setup.h"
#include "box.h"

int main(int argc, char *argv[]) {
    // Ventana principal
    GtkWidget *window;

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

    // Crear y configurar la ventana
    window = crear_ventana();
    establecer_nombre_ventana(window, "Wizard");
    establecer_tamano_por_defecto_ventana(window, 900, 500);
    establecer_redimensionable_ventana(window, TRUE);
    establecer_tamano_minimo_ventana(window, 300, 200);
    establecer_terminar_programa_cerrado_ventana(window);

    // Crear un contenedor de caja vertical para el menu_bar y lo demás
    vbox = crear_box(GTK_ORIENTATION_VERTICAL, 0);

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
    
    // Agregar la caja vertical a la ventana
    agregar_widget_ventana(window, vbox);

    // Mostrar la ventana
    mostrar_ventana(window);

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}