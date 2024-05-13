#include <gtk/gtk.h>

#include "tree_manager.h"
#include "tree.h"
#include "window_manager.h"
#include "session_manager.h"

GtkTreeStore *MAIN_TREE_MODEL;

char *PATH_FICHERO_ARBOL = NULL;

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

    // Crear el TreeView
    tree_view = crear_tree_view(MAIN_TREE_MODEL);

    // Obtener el último fichero abierto
    PATH_FICHERO_ARBOL = read_last_opened_file();
    
    // Si hay un fichero en sesión, se carga
    if (PATH_FICHERO_ARBOL != NULL) {
        cargar_arbol(MAIN_TREE_MODEL, PATH_FICHERO_ARBOL);
    }

    // Se crea una columna para el TreeView
    crear_columna_tree_view(tree_view, "Árbol sin nombre");

    return tree_view;
}

/**
 * Carga un árbol de un fichero
 * 
 * @return void
 */
void cargar_arbol_principal() {
    // Seleccionar un fichero desde el sistema de archivos
    char* filename = mostrar_ventana_selector_archivos();

    // Cargar el árbol desde el fichero
    cargar_arbol(MAIN_TREE_MODEL, filename);

    // Guardar el último fichero abierto
    write_last_opened_file(filename);
    PATH_FICHERO_ARBOL = filename;
}