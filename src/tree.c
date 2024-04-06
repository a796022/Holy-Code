#include <gtk/gtk.h>

#include "tree.h"

GtkTreeStore *crear_modelo_datos_tree() {
    // Primer parámetro: cantidad de columnas
    // Segundo parámetro: tipo de datos de la primera columna
    GtkTreeStore *model = gtk_tree_store_new(1, G_TYPE_STRING);
    return model;
}

GtkWidget *crear_tree_view(GtkTreeStore *model) {
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
    return tree_view;
}

void agregar_nodo_tree(GtkTreeStore *model, GtkTreeIter *padre, const char *texto) {
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
}

void crear_columna_tree_view(GtkWidget *tree_view, const char *titulo) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(titulo, renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
}