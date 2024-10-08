#include <gtk/gtk.h>

// #include "history.h"
// #include "session_manager.h"
// #include "tree_files.h"
#include "tree_manager.h"
// #include "window_manager.h"
// #include "window_structure.h"

static void init_tree_view(GtkWidget* tree_view);
static void create_treeview_column(GtkWidget *tree_view, const char *title);

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
void new_tree_view(GtkWidget** tree_view) {
    // Create the model
    GtkTreeStore *model = gtk_tree_store_new(1, G_TYPE_STRING);

    // Create the TreeView
    *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
    
    // Initialize the TreeView
    init_tree_view(*tree_view);

    // Show the TreeView
    gtk_widget_show(*tree_view);
}

/**
 * @brief Initializes the TreeView.
 * 
 * - Create a column for the TreeView.
 * 
 * @param tree_view TreeView widget
 * 
 * @return void
*/
static void init_tree_view(GtkWidget* tree_view) {
    // Create a column for the TreeView
    create_treeview_column(tree_view, "Árbol sin nombre");
}

/**
 * @brief Adds a node to the tree.
 * 
 * @param tree_view TreeView widget
 * @param model Tree data model
 * @param parent_node Parent node of the new node
 * @param text Text of the new node
 * 
 * return GtkTreeIter Iterator of the new node
*/
GtkTreeIter add_node(GtkWidget* tree_view, GtkTreeStore *model, GtkTreeIter *parent_node, const char *text) {
    // Adds a new node to the tree
    GtkTreeIter iter;
    gtk_tree_store_append(model, &iter, parent_node);
    gtk_tree_store_set(model, &iter, 0, text, -1);

    // Expands the parent node
    if (parent_node != NULL) {
        GtkTreePath *path = gtk_tree_model_get_path(GTK_TREE_MODEL(model), parent_node);
        gtk_tree_view_expand_row(GTK_TREE_VIEW(tree_view), path, FALSE);
        gtk_tree_path_free(path);
    }

    return iter;
}

/**
 * @brief Creates a column for the TreeView.
 * 
 * @param tree_view TreeView widget
 * @param title Title of the column
 * 
 * @return void
*/
static void create_treeview_column(GtkWidget *tree_view, const char *title) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(title, renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
}

// /**
//  * @brief Deletes a node recursively.
//  * 
//  * - Deletes the children of the node.
//  * - Deletes the node.
//  * 
//  * @param store Data model of the tree
//  * @param iter Iterator of the node
//  * 
//  * @return void
//  */
// void delete_node_recursive(struct WindowStructure* window_structure, GtkTreeStore *store, GtkTreeIter *iter) {
//     // Recursive call to go through all the children
//     GtkTreeIter child;
//     while (gtk_tree_model_iter_children(GTK_TREE_MODEL(store), &child, iter)) {
//         delete_node_recursive(window_structure, store, &child);
//     }
    
//     // Get the text of the node
//     gchar *node_text;
//     gtk_tree_model_get(GTK_TREE_MODEL(store), iter, 0, &node_text, -1);

//     // Add the action to the history
//     GtkTreePath *path = gtk_tree_model_get_path(GTK_TREE_MODEL(store), iter);
//     gchar *path_str = gtk_tree_path_to_string(path);
//     gtk_tree_path_free(path);
    
//     // Create the operation
//     struct DeleteOperation *operation = g_new(struct DeleteOperation, 1);
//     operation->node_text = node_text;
//     operation->node_path = path_str;

//     // Add the operation to the history
//     store_operation(window_structure, DELETE_OP, operation);

//     // Delete the node
//     gtk_tree_store_remove(store, iter);
// }

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
    GtkTreeStore *tree_model = window_structure->tree_model;

    // If this is a new file, ask for the file name
    if (window_structure->tree_path_file == NULL) {
        // TODO: Ask for the file name
    }

    // If the user has not selected a file, do nothing
    if (window_structure->tree_path_file == NULL) {
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
    int status = write_tree_file(window_structure, window_structure->tree_path_file, num_nodes);
    if (status == -1) {
        return;
    }

    // Save the last opened file, it is done again in case it is a new file.
    write_last_opened_file(window_structure->tree_path_file);

    // Reset the last saved distance
    set_changes_as_saved(window_structure);
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
    GtkWidget* window = window_structure->window;
    GtkWidget* tree_view = window_structure->tree_view;

    // Select the file from the file selector
    char* filename = show_file_selector_window(window);

    // If the user has not selected a file, do nothing
    if (filename == NULL) {
        return;
    }

    load_tree(window_structure, filename, tree_view);

    // Save the last opened file
    write_last_opened_file(filename);

    // Free the last opened file if it exists
    if (window_structure->tree_path_file != NULL) {
        g_free(window_structure->tree_path_file);
    }

    // Make a copy of the filename
    window_structure->tree_path_file = strdup(filename);

    // Free the filename
    free(filename);
}

// /**
//  * @brief Add the input text to the selected node.
//  * 
//  * @param window Window with the tree to which the text will be added.
//  * @param data Text to add
//  * 
//  * @return void
//  */
// void add_text_to_selected_node(struct WindowStructure* window_structure, void *data) {
//     // Get the data
//     GtkWidget* tree_view = window_structure->tree_view;

//     // Get the text to add
//     char *node_text = (char *)data;

//     // Get the selected node
//     GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
//     GtkTreeIter selected_node_iter;
//     GtkTreeIter added_node_iter;
//     GtkTreeModel *model;
//     if (gtk_tree_selection_get_selected(selection, &model, &selected_node_iter)) {

//         // Add the text to the selected node
//         GtkTreeStore *store = GTK_TREE_STORE(model);
//         added_node_iter = add_node(tree_view, store, &selected_node_iter, node_text);

//         // Add the action to the history
//         GtkTreePath *path = gtk_tree_model_get_path(model, &added_node_iter);
//         gchar *path_str = gtk_tree_path_to_string(path);
//         gtk_tree_path_free(path);

//         // Create the operation
//         struct AggregateOperation *operation = g_new(struct AggregateOperation, 1);
//         operation->node_text = node_text;
//         operation->node_path = path_str;

//         // Add the operation to the history
//         store_operation(window_structure, AGGREGATE_OP, operation);

//     } else {
//         perror("Error: did not find any selected node\n");
//     }
// }

// /**
//  * @brief Inserts a new node in the tree.
//  * 
//  * @param parent_iter Parent node of the new node
//  * @param position Position of the new node
//  * @param text Text of the new node
//  * 
//  * @return GtkTreeIter Iterator of the new node
//  */
// GtkTreeIter insert_node_at_position(struct WindowStructure* window_structure, GtkTreeIter *parent_iter, gint position, const gchar *text) {
//     // Get the data
//     GtkWidget* tree_view = window_structure->tree_view;
//     GtkTreeStore* tree_model = window_structure->tree_model;

//     // Insert a new node in the tree "store" (main tree model), under the parent node "parent_iter", at position "position"
//     GtkTreeIter new_iter;
//     gtk_tree_store_insert(tree_model, &new_iter, parent_iter, position);

//     // Set the values of the new node
//     gtk_tree_store_set(tree_model, &new_iter, 0, text, -1);

//     // Expand the parent node
//     GtkTreePath *path = gtk_tree_model_get_path(GTK_TREE_MODEL(tree_model), parent_iter);
//     gtk_tree_view_expand_row(GTK_TREE_VIEW(tree_view), path, FALSE);
//     gtk_tree_path_free(path);

//     return new_iter;
// }

// /**
//  * @brief Deletes the selected node.
//  * 
//  * - Checks if the selected node is a root node.
//  * - If it is a root node, it is deleted.
//  * 
//  * @param menuitem Menu item that triggered the signal.
//  * @param user_data Data passed to the signal. In this case, the window with the tree to which the node belongs.
//  * 
//  * @return void
//  */
// void delete_selected_node(GtkMenuItem *menuitem, gpointer user_data) {
//     // Get the window data
//     struct WindowStructure* window_structure = (struct WindowStructure*)user_data;
//     GtkWidget* tree_view = window_structure->tree_view;
//     struct History *history = window_structure->history;

//     // Get the selected node
//     GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
//     GtkTreeIter iter;
//     GtkTreeModel *model;
//     if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        
//         // Check if the selected node is a root node
//         GtkTreeStore *store = GTK_TREE_STORE(model);
//         GtkTreeIter parent;
//         if (gtk_tree_model_iter_parent(model, &parent, &iter)) {

//             // Call the recursive delete function
//             init_operations_set(history);
//             delete_node_recursive(window_structure, store, &iter);
//             end_operations_set(history);

//         }

//     }
// }