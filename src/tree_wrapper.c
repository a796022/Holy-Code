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
int load_tree(struct WindowStructure* window_structure, const char *filename) {
    // "Get the model"
    window_structure->tree_model = window_structure->tree_model;
    GtkTreeStore *model = window_structure->tree_model;

    // Clear the model
    gtk_tree_store_clear(model);
    
    // Load the tree from the file
    return read_tree_file(window_structure, filename);
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
void delete_node_recursive(GtkWidget *window, GtkTreeStore *store, GtkTreeIter *iter) {
    GtkTreeIter child;
    while (gtk_tree_model_iter_children(GTK_TREE_MODEL(store), &child, iter)) {
        delete_node_recursive(window, store, &child);
    }
    
    // Get the text of the node
    gchar *node_text;
    gtk_tree_model_get(GTK_TREE_MODEL(store), iter, 0, &node_text, -1);

    // Add the action to the history
    GtkTreePath *path = gtk_tree_model_get_path(GTK_TREE_MODEL(store), iter);
    gchar *path_str = gtk_tree_path_to_string(path);
    gtk_tree_path_free(path);
    store_delete_operation(window, node_text, path_str);

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
GtkWidget* init_main_tree(struct WindowStructure* window_structure) {
    // Create a data model for the tree (with one column of type string)
    window_structure->tree_model = gtk_tree_store_new(1, G_TYPE_STRING);

    // Create the TreeView
    window_structure->tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(window_structure->tree_model));

    // Get the last opened file
    TREE_PATH_FILE = read_last_opened_file();
    
    // If there is a file in session, it is loaded
    if (TREE_PATH_FILE != NULL) {
        load_tree(window_structure, TREE_PATH_FILE);
    }

    // Create a column for the TreeView
    create_treeview_column(window_structure->tree_view, "Árbol sin nombre");

    return window_structure->tree_view;
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
void save_tree(GtkMenuItem *menuitem, gpointer user_data) {
    // Get the data
    struct WindowStructure* window_structure = (struct WindowStructure*)user_data;
    GtkWidget* window = window_structure->window;
    GtkTreeStore *tree_model = window_structure->tree_model;

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
    if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(tree_model), &iter)) {
        num_nodes = count_nodes(GTK_TREE_MODEL(tree_model), &iter);
    } else {
        return;
    }

    // Save the file
    int status = write_tree_file(tree_model, TREE_PATH_FILE, num_nodes);
    if (status == -1) {
        return;
    }

    // Save the last opened file, it is done again in case it is a new file.
    write_last_opened_file(TREE_PATH_FILE);

    // Reset the last saved distance
    set_changes_as_saved(window);
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
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal.
 * 
 * @return void
 */
void open_tree_file(GtkMenuItem *menuitem, gpointer user_data) {
    // Get the window
    struct WindowStructure* window_structure = (struct WindowStructure*)user_data;
    GtkWidget *window = window_structure->window;

    // Select the file from the file selector
    char* filename = show_file_selector_window(window);

    // If the user has not selected a file, do nothing
    if (filename == NULL) {
        return;
    }

    // Empty the tree
    load_tree(window_structure, filename);

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
GtkTreeIter add_node(struct WindowStructure* window_structure, GtkTreeStore *model, GtkTreeIter *parent_node, const char *text) {
    // Get the data
    GtkWidget* tree_view = window_structure->tree_view;

    // Adds a new node to the tree "model" (main tree model), under the parent node "parent_node".
    // The iterator "iter" is updated to point to the new node.
    GtkTreeIter iter;
    gtk_tree_store_append(model, &iter, parent_node);

    // Sets the text of the node.
    gtk_tree_store_set(model, &iter, 0, text, -1);

    // Expands the parent node
    if (parent_node != NULL) {
        gtk_tree_view_expand_row(GTK_TREE_VIEW(tree_view), gtk_tree_model_get_path(GTK_TREE_MODEL(model), parent_node), FALSE);
    }

    return iter;
}

/**
 * @brief Add the input text to the selected node.
 * 
 * @param window Window with the tree to which the text will be added.
 * @param data Text to add
 * 
 * @return void
 */
void add_text_to_selected_node(struct WindowStructure* window_structure, void *data) {
    // Get the data
    GtkWidget* tree_view = window_structure->tree_view;

    // Get the text to add
    char *text = (char *)data;

    // Get the selected node
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
    GtkTreeIter selected_node_iter;
    GtkTreeIter added_node_iter;
    GtkTreeModel *model;
    if (gtk_tree_selection_get_selected(selection, &model, &selected_node_iter)) {

        // Add the text to the selected node
        GtkTreeStore *store = GTK_TREE_STORE(model);
        added_node_iter = add_node(window_structure, store, &selected_node_iter, text);

        // Add the action to the history
        GtkTreePath *path = gtk_tree_model_get_path(model, &added_node_iter);
        gchar *path_str = gtk_tree_path_to_string(path);
        gtk_tree_path_free(path);
        store_aggregate_operation(window_structure, text, path_str);

    } else {
        perror("Error: did not find any selected node\n");
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
GtkTreeIter insert_node_at_position(struct WindowStructure* window_structure, GtkTreeIter *parent_iter, gint position, const gchar *text) {
    // Get the data
    GtkWidget* tree_view = window_structure->tree_view;
    GtkTreeStore* tree_model = window_structure->tree_model;

    // Insert a new node in the tree "store" (main tree model), under the parent node "parent_iter", at position "position"
    GtkTreeIter new_iter;
    gtk_tree_store_insert(tree_model, &new_iter, parent_iter, position);

    // Set the values of the new node
    gtk_tree_store_set(tree_model, &new_iter, 0, text, -1);

    // Expand the parent node
    gtk_tree_view_expand_row(GTK_TREE_VIEW(tree_view), gtk_tree_model_get_path(GTK_TREE_MODEL(tree_model), parent_iter), FALSE);

    return new_iter;
}

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
void delete_selected_node(GtkMenuItem *menuitem, gpointer user_data) {
    // Get the window data
    struct WindowStructure* window_structure = (struct WindowStructure*)user_data;
    GtkWidget* window = window_structure->window;
    GtkWidget* tree_view = window_structure->tree_view;

    // Get the selected node
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
    GtkTreeIter iter;
    GtkTreeModel *model;
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        
        // Check if the selected node is a root node
        GtkTreeStore *store = GTK_TREE_STORE(model);
        GtkTreeIter parent;
        if (gtk_tree_model_iter_parent(model, &parent, &iter)) {

            // Call the recursive delete function
            init_operations_set();
            delete_node_recursive(window, store, &iter);
            end_operations_set();

        }

    }
    
}