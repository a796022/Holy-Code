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
 * @brief Adds a node to the tree.
 * 
 * @param model Data model to which the node is added.
 * @param parent_node Parent node of the node to be added. If it is NULL, a root node is added.
 * @param text Text to add to the node.
 * 
 * return GtkTreeIter Iterator of the new node
*/
GtkTreeIter agregar_nodo_tree(GtkTreeStore *model, GtkTreeIter *parent_node, const char *text) {
    GtkTreeIter iter;

    // Adds a new node to the tree "model" (main tree model), under the parent node "parent_node".
    // The iterator "iter" is updated to point to the new node.
    gtk_tree_store_append(model, &iter, parent_node);

    // Sets the text of the node.
    gtk_tree_store_set(model, &iter, 0, text, -1);

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