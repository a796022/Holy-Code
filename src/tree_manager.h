#ifndef TREE_MANAGER
#define TREE_MANAGER

#include <gtk/gtk.h>

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

/**
 * @brief Add the input text to the selected node.
 * 
 * @param text Text to add
 * 
 * @return void
 */
void add_text_to_selected_node(const char *text);

#endif /* TREE_MANAGER */