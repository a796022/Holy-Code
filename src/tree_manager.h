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
 * @brief Saves the tree of the main window in a file.
 * 
 * - If this is a new file, ask for the file name.
 * - If the user has not selected a file, do nothing.
 * - Save the file.
 * - Save the last opened file, it is done again in case it is a new file.
 * 
 * @return void
 */
void save_tree();

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

/**
 * @brief Deletes the selected node.
 * 
 * @return void
 */
void delete_selected_node();

#endif /* TREE_MANAGER */