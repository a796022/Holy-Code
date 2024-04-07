#include <gtk/gtk.h>

#include "tree_manager.h"
#include "tree.h"

GtkTreeStore *MAIN_TREE_MODEL;

/**
 * Inicializa el árbol de la ventana principal.
 * 
 * @return void
*/
GtkWidget *inicializar_arbol_principal() {
    // Widget del TreeView
    GtkWidget *tree_view;

    // Crear un modelo de árbol para el TreeView
    MAIN_TREE_MODEL = crear_modelo_datos_tree();

    // Agregar algunos elementos al modelo de árbol
    agregar_nodo_tree(MAIN_TREE_MODEL, NULL, "Elemento 1");
    agregar_nodo_tree(MAIN_TREE_MODEL, NULL, "Elemento 2");

    // Crear el TreeView
    tree_view = crear_tree_view(MAIN_TREE_MODEL);

    // Crear una columna para el TreeView
    crear_columna_tree_view(tree_view, "Árbol sin nombre");

    return tree_view;
}

/**
 * Carga un árbol de un fichero
 * 
 * @return void
 */
void cargar_arbol_principal() {
    cargar_arbol(NULL, NULL);
}