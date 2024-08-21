#include <gtk/gtk.h>

#include "tree.h"
#include "tree_files.h"

/**
 * Crea un modelo de datos para un árbol.
 * 
 * @return GtkTreeStore*
*/
GtkTreeStore *crear_modelo_datos_tree() {
    // Primer parámetro: cantidad de columnas
    // Segundo parámetro: tipo de datos de la primera columna
    GtkTreeStore *model = gtk_tree_store_new(1, G_TYPE_STRING);
    return model;
}

/**
 * Crea un TreeView partiendo de un modelo de datos.
 * 
 * @param model Modelo de datos del TreeView.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_tree_view(GtkTreeStore *model) {
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
    return tree_view;
}

/**
 * Agrega un nodo al árbol.
 * 
 * @param model Modelo de datos al que se le agrega el nodo.
 * @param padre Nodo padre del nodo a agregar. Si es NULL, se agrega un nodo raíz.
 * @param texto Texto a agregar en el nodo.
 * 
 * return GtkTreeIter
*/
GtkTreeIter agregar_nodo_tree(GtkTreeStore *model, GtkTreeIter *padre, const char *texto) {
    GtkTreeIter iter;

    /**
     * - model: modelo de datos al que se le agrega el nodo.
     * - iter: iterador que apuntará al nodo agregado.
     * - padre: iterador que apunta al nodo padre del nodo a agregar. Si es 
     * NULL, se agrega un nodo raíz.
    */
    gtk_tree_store_append(model, &iter, padre);

    /**
     * - model: modelo de datos al que se le agrega el nodo.
     * - iter: iterador que apuntará al nodo agregado.
     * - 0: columna en la que se agrega el texto (en principio, siempre 0).
     * - texto: texto a agregar en la columna.
     * - -1: fin de la lista de argumentos.
    */
    gtk_tree_store_set(model, &iter, 0, texto, -1);

    return iter;
}

/**
 * Crea una columna para un TreeView.
 * 
 * @param tree_view TreeView al que se le agregará la columna.
 * @param titulo Título de la columna.
 * 
 * @return void
*/
void crear_columna_tree_view(GtkWidget *tree_view, const char *titulo) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(titulo, renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
}

/**
 * Carga un árbol de un fichero
 * 
 * @param model Modelo de datos del árbol
 * @param filename Nombre del fichero
 * 
 * @return int
*/
int cargar_arbol(GtkTreeStore *model, const char *filename) {
    // Primero, vacío el árbol
    gtk_tree_store_clear(model);
    
    // Cargo el árbol
    return read_tree_file(model, filename);
}