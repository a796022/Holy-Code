#ifndef TREE_MANAGER
#define TREE_MANAGER

#include <gtk/gtk.h>

// Widget of the main window tree
extern GtkWidget *MAIN_TREE_VIEW;

// Main window tree data model
extern GtkTreeStore *MAIN_TREE_MODEL;

/**
 * Inicializa el árbol de la ventana principal.
 * 
 * @return void
*/
GtkWidget *init_main_tree();

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
void load_main_tree();

/**
 * @brief Add the input text to the selected node.
 * 
 * @param text Text to add
 * 
 * @return void
 */
void add_text_to_selected_node(char *text);

/**
 * @brief Inserts a new node in the tree.
 * 
 * @param parent_iter Parent node of the new node
 * @param position Position of the new node
 * @param text Text of the new node
 * 
 * @return GtkTreeIter Iterator of the new node
 */
GtkTreeIter insert_node_at_position(GtkTreeIter *parent_iter, gint position, const gchar *text);

/**
 * @brief Deletes the selected node.
 * 
 * @return void
 */
void delete_selected_node();

#endif /* TREE_MANAGER */