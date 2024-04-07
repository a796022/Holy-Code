#ifndef TREE_MANAGER
#define TREE_MANAGER

extern GtkTreeStore *MAIN_TREE_MODEL;

/**
 * Inicializa el árbol de la ventana principal.
 * 
 * @return void
*/
GtkWidget *inicializar_arbol_principal();

/**
 * Carga un árbol de un fichero
 * 
 * @return void
 */
void cargar_arbol_principal();

#endif /* TREE_MANAGER */