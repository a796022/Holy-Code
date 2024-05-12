#ifndef TREE_H
#define TREE_H

/**
 * Crea un modelo de datos para un árbol.
 * 
 * @return GtkTreeStore*
*/
GtkTreeStore *crear_modelo_datos_tree();

/**
 * Crea un TreeView partiendo de un modelo de datos.
 * 
 * @param model Modelo de datos del TreeView.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_tree_view(GtkTreeStore *store);

/**
 * Agrega un nodo al árbol.
 * 
 * @param model Modelo de datos al que se le agrega el nodo.
 * @param padre Nodo padre del nodo a agregar. Si es NULL, se agrega un nodo raíz.
 * @param texto Texto a agregar en el nodo.
 * 
 * @return GtkTreeIter
*/
GtkTreeIter agregar_nodo_tree(GtkTreeStore *store, GtkTreeIter *padre, const char *texto);

/**
 * Crea una columna para un TreeView.
 * 
 * @param tree_view TreeView al que se le agregará la columna.
 * @param titulo Título de la columna.
 * 
 * @return void
*/
void crear_columna_tree_view(GtkWidget *tree_view, const char *titulo);

/**
 * Carga un árbol de un fichero
 * 
 * @param model Modelo de datos del árbol
 * @param filename Nombre del fichero
 * 
 * @return void
*/
void cargar_arbol(GtkTreeStore *model, const char *filename);

#endif /* TREE_H */