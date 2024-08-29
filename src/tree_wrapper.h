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
 * @brief Load a tree from a file.
 * 
 * - Select the file from the file selector.
 * - If the user has not selected a file, do nothing.
 * - Empty the tree.
 * - Load the tree from the file.
 * - Save the last opened file.
 * 
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal.
 * 
 * @return void
 */
void open_tree_file(GtkMenuItem *menuitem, gpointer user_data);

/**
 * @brief Adds a node to the tree.
 * 
 * @param model Data model to which the node is added.
 * @param parent_node Parent node of the node to be added. If it is NULL, a root node is added.
 * @param text Text to add to the node.
 * 
 * return GtkTreeIter Iterator of the new node
*/
GtkTreeIter add_node(GtkTreeStore *model, GtkTreeIter *parent_node, const char *text);

/**
 * @brief Add the input text to the selected node.
 * 
 * @param window Window with the tree to which the text will be added.
 * @param data Text to add
 * 
 * @return void
 */
void add_text_to_selected_node(GtkWidget *window, void *data);

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
 * - Checks if the selected node is a root node.
 * - If it is a root node, it is deleted.
 * 
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal. In this case, the window with the tree to which the node belongs.
 * 
 * @return void
 */
void delete_selected_node(GtkMenuItem *menuitem, gpointer user_data);

#endif /* TREE_MANAGER */