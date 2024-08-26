#include <gtk/gtk.h>

#include "tree_wrapper.h"
#include "window_manager.h"
#include "session_manager.h"
#include "tree_files.h"
#include "history.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Path of the file in session
char *TREE_PATH_FILE = NULL;

/**
 * @brief Load a tree from a file.
 * 
 * - Clear the model.
 * - Load the tree from the file.
 * 
 * @param model Tree data model where the tree is loaded
 * @param filename File name to load
 * 
 * @return int
*/
int load_tree(GtkTreeStore *model, const char *filename) {
    // Clear the model
    gtk_tree_store_clear(model);
    
    // Load the tree from the file
    return read_tree_file(model, filename);
}

/**
 * Crea una columna para un TreeView.
 * 
 * @param tree_view TreeView al que se le agregará la columna.
 * @param titulo Título de la columna.
 * 
 * @return void
*/
void create_treeview_column(GtkWidget *tree_view, const char *title) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(title, renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
}

/**
 * @brief Deletes a node recursively.
 * 
 * - Deletes the children of the node.
 * - Deletes the node.
 * 
 * @param store Data model of the tree
 * @param iter Iterator of the node
 * 
 * @return void
 */
void delete_node_recursive(GtkTreeStore *store, GtkTreeIter *iter) {
    GtkTreeIter child;
    while (gtk_tree_model_iter_children(GTK_TREE_MODEL(store), &child, iter)) {
        delete_node_recursive(store, &child);
    }
    
    // Get the text of the node
    gchar *node_text;
    gtk_tree_model_get(GTK_TREE_MODEL(store), iter, 0, &node_text, -1);

    // Add the action to the history
    GtkTreePath *path = gtk_tree_model_get_path(GTK_TREE_MODEL(store), iter);
    gchar *path_str = gtk_tree_path_to_string(path);
    gtk_tree_path_free(path);
    store_delete_operation(node_text, path_str);

    // Delete the node
    gtk_tree_store_remove(store, iter);
}

/**
 * @brief Count the nodes of a tree.
 * 
 * - Counts the nodes of the tree.
 * 
 * @param model Tree data model
 * @param iter Iterator of the node
 * 
 * @return int Number of nodes
 */
int count_nodes(GtkTreeModel *model, GtkTreeIter *iter)
{
    int counter = 1; 
    GtkTreeIter hijo;

    // Check if the current node has children
    if (gtk_tree_model_iter_children(model, &hijo, iter))
    {
        // Call recursively for each child
        do {
            counter += count_nodes(model, &hijo);
        } while (gtk_tree_model_iter_next(model, &hijo));
    }

    return counter;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Widget of the main window tree
GtkWidget *MAIN_TREE_VIEW;

// Main window tree data model
GtkTreeStore *MAIN_TREE_MODEL;

/**
 * @brief Initializes the main window tree.
 * 
 * - Creates a tree model for the TreeView.
 * - Creates the TreeView.
 * - Gets the last opened file.
 * - If there is a file in session, it is loaded.
 * 
 * @return GtkWidget* The TreeView widget
*/
GtkWidget *init_main_tree() {
    // Create a data model for the tree (with one column of type string)
    MAIN_TREE_MODEL = gtk_tree_store_new(1, G_TYPE_STRING);

    // Create the TreeView
    MAIN_TREE_VIEW = gtk_tree_view_new_with_model(GTK_TREE_MODEL(MAIN_TREE_MODEL));

    // Get the last opened file
    TREE_PATH_FILE = read_last_opened_file();
    
    // If there is a file in session, it is loaded
    if (TREE_PATH_FILE != NULL) {
        load_tree(MAIN_TREE_MODEL, TREE_PATH_FILE);
    }

    // Create a column for the TreeView
    create_treeview_column(MAIN_TREE_VIEW, "Árbol sin nombre");

    return MAIN_TREE_VIEW;
}

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
void save_tree() {
    // If this is a new file, ask for the file name
    if (TREE_PATH_FILE == NULL) {
        // TODO: Ask for the file name
    }

    // If the user has not selected a file, do nothing
    if (TREE_PATH_FILE == NULL) {
        return;
    }

    // Get the number of nodes
    GtkTreeIter iter;
    int num_nodes = 0;
    if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(MAIN_TREE_MODEL), &iter)) {
        num_nodes = count_nodes(GTK_TREE_MODEL(MAIN_TREE_MODEL), &iter);
    } else {
        return;
    }

    // Save the file
    int status = write_tree_file(MAIN_TREE_MODEL, TREE_PATH_FILE, num_nodes);
    if (status == -1) {
        return;
    }

    // Save the last opened file, it is done again in case it is a new file.
    write_last_opened_file(TREE_PATH_FILE);

    // Reset the last saved distance
    set_changes_as_saved();
}

/**
 * @brief Load a tree from a file.
 * 
 * - Select the file from the file selector.
 * - If the user has not selected a file, do nothing.
 * - Empty the tree.
 * - Load the tree from the file.
 * - Save the last opened file.
 * 
 * @return void
 */
void select_tree() {
    // Select the file from the file selector
    char* filename = mostrar_ventana_selector_archivos();

    // If the user has not selected a file, do nothing
    if (filename == NULL) {
        return;
    }

    // Empty the tree
    load_tree(MAIN_TREE_MODEL, filename);

    // Save the last opened file
    write_last_opened_file(filename);
    TREE_PATH_FILE = filename;
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
GtkTreeIter add_node(GtkTreeStore *model, GtkTreeIter *parent_node, const char *text) {
    GtkTreeIter iter;

    // Adds a new node to the tree "model" (main tree model), under the parent node "parent_node".
    // The iterator "iter" is updated to point to the new node.
    gtk_tree_store_append(model, &iter, parent_node);

    // Sets the text of the node.
    gtk_tree_store_set(model, &iter, 0, text, -1);

    // Expands the parent node
    if (parent_node != NULL) {
        gtk_tree_view_expand_row(GTK_TREE_VIEW(MAIN_TREE_VIEW), gtk_tree_model_get_path(GTK_TREE_MODEL(model), parent_node), FALSE);
    }

    return iter;
}

/**
 * @brief Add the input text to the selected node.
 * 
 * @param text Text to add
 * 
 * @return void
 */
void add_node_to_selected_node(char *text) {

    // Get the selected node
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(MAIN_TREE_VIEW));
    GtkTreeIter selected_node_iter;
    GtkTreeIter added_node_iter;
    GtkTreeModel *model;
    if (gtk_tree_selection_get_selected(selection, &model, &selected_node_iter)) {

        // Add the text to the selected node
        GtkTreeStore *store = GTK_TREE_STORE(model);
        added_node_iter = add_node(store, &selected_node_iter, text);

        // Add the action to the history
        GtkTreePath *path = gtk_tree_model_get_path(model, &added_node_iter);
        gchar *path_str = gtk_tree_path_to_string(path);
        gtk_tree_path_free(path);
        store_aggregate_operation(text, path_str);

    } else {
        printf("Error: did not find any selected node\n");
    }
}

/**
 * @brief Inserts a new node in the tree.
 * 
 * @param parent_iter Parent node of the new node
 * @param position Position of the new node
 * @param text Text of the new node
 * 
 * @return GtkTreeIter Iterator of the new node
 */
GtkTreeIter insert_node_at_position(GtkTreeIter *parent_iter, gint position, const gchar *text) {
    GtkTreeIter new_iter;

    // Insert a new node in the tree "store" (main tree model), under the parent node "parent_iter", at position "position"
    gtk_tree_store_insert(MAIN_TREE_MODEL, &new_iter, parent_iter, position);

    // Set the values of the new node
    gtk_tree_store_set(MAIN_TREE_MODEL, &new_iter, 0, text, -1);

    return new_iter;
}

/**
 * @brief Deletes the selected node.
 * 
 * - Checks if the selected node is a root node.
 * - If it is a root node, it is deleted.
 * 
 * @return void
 */
void delete_selected_node() {

    // Get the selected node
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(MAIN_TREE_VIEW));
    GtkTreeIter iter;
    GtkTreeModel *model;
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        
        // Check if the selected node is a root node
        GtkTreeStore *store = GTK_TREE_STORE(model);
        GtkTreeIter parent;
        if (gtk_tree_model_iter_parent(model, &parent, &iter)) {

            // Call the recursive delete function
            init_operations_set();
            delete_node_recursive(store, &iter);
            end_operations_set();

        }

    }
    
}