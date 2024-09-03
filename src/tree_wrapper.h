#pragma once

#include <gtk/gtk.h>

#include "window_structure.h"

/**
 * @brief Initializes the main window tree.
 * 
 * - Creates a tree model for the TreeView.
 * - Creates the TreeView.
 * - Gets the last opened file.
 * - If there is a file in session, it is loaded.
 * 
 * @param window_structure Window structure with the TreeView widget
 * 
 * @return GtkWidget* The TreeView widget
*/
void init_main_tree(struct WindowStructure* window_structure);

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
void save_tree(GtkMenuItem *menuitem, gpointer user_data);

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
GtkTreeIter add_node(struct WindowStructure* window_structure, GtkTreeStore *model, GtkTreeIter *parent_node, const char *text);

/**
 * @brief Add the input text to the selected node.
 * 
 * @param window Window with the tree to which the text will be added.
 * @param data Text to add
 * 
 * @return void
 */
void add_text_to_selected_node(struct WindowStructure* window_structure, void *data);

/**
 * @brief Inserts a new node in the tree.
 * 
 * @param parent_iter Parent node of the new node
 * @param position Position of the new node
 * @param text Text of the new node
 * 
 * @return GtkTreeIter Iterator of the new node
 */
GtkTreeIter insert_node_at_position(struct WindowStructure* window_structure, GtkTreeIter *parent_iter, gint position, const gchar *text);

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