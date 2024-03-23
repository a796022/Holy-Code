#include <gtk/gtk.h>

#include "window.h"
#include "tree.h"

int main(int argc, char *argv[]) {
    // Ventana principal
    GtkWidget *window;

    // Modelo de datos del arbol
    GtkTreeStore *model;

    // Widget del TreeView
    GtkWidget *tree_view;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear y configurar la ventana
    window = crear_ventana();
    establecer_nombre_ventana(window, "Wizard");
    establecer_tamano_por_defecto_ventana(window, 300, 200);
    establecer_redimensionable_ventana(window, TRUE);
    establecer_tamano_minimo_ventana(window, 300, 200);
    establecer_terminar_programa_cerrado_ventana(window);

    // Crear un modelo de árbol para el TreeView
    model = crear_modelo_datos_tree();

    // Agregar algunos elementos al modelo de árbol
    agregar_nodo_tree(model, NULL, "Elemento 1");
    agregar_nodo_tree(model, NULL, "Elemento 2");

    // Crear el TreeView
    tree_view = crear_tree_view(model);

    // Crear una columna para el TreeView
    crear_columna_tree_view(tree_view, "Elementos");

    // Agregar el TreeView a la ventana
    agregar_widget_ventana(window, tree_view);

    // Mostrar la ventana
    mostrar_ventana(window);

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}
