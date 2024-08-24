#include <gtk/gtk.h>

#include "tree_manager.h"
#include "tree.h"
#include "window_manager.h"
#include "session_manager.h"
#include "tree_files.h"
#include "history.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Widget of the main window tree
GtkWidget *MAIN_TREE_VIEW;

// Path of the file in session
char *TREE_PATH_FILE = NULL;

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

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
    // Create a data model for the tree
    MAIN_TREE_MODEL = crear_modelo_datos_tree();

    // Create the TreeView
    MAIN_TREE_VIEW = crear_tree_view(MAIN_TREE_MODEL);

    // Get the last opened file
    TREE_PATH_FILE = read_last_opened_file();
    
    // If there is a file in session, it is loaded
    if (TREE_PATH_FILE != NULL) {
        cargar_arbol(MAIN_TREE_MODEL, TREE_PATH_FILE);
    }

    // Create a column for the TreeView
    crear_columna_tree_view(MAIN_TREE_VIEW, "Árbol sin nombre");

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

    // Save the file
    int status = write_tree_file(MAIN_TREE_MODEL, TREE_PATH_FILE);
    if (status == -1) {
        return;
    }

    // Save the last opened file, it is done again in case it is a new file.
    write_last_opened_file(TREE_PATH_FILE);
}

/**
 * Carga un árbol de un fichero
 * 
 * @return void
 */
void load_main_tree() {
    // Seleccionar un fichero desde el sistema de archivos
    char* filename = mostrar_ventana_selector_archivos();

    // Si el usuario no ha seleccionado un archivo, no se hace nada
    if (filename == NULL) {
        return;
    }

    // Cargar el árbol desde el fichero
    cargar_arbol(MAIN_TREE_MODEL, filename);

    // Guardar el último fichero abierto
    write_last_opened_file(filename);
    TREE_PATH_FILE = filename;
}

/**
 * @brief Add the input text to the selected node.
 * 
 * @param text Text to add
 * 
 * @return void
 */
void add_text_to_selected_node(char *text) {

    // Get the selected node
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(MAIN_TREE_VIEW));
    GtkTreeIter selected_node_iter;
    GtkTreeIter added_node_iter;
    GtkTreeModel *model;
    if (gtk_tree_selection_get_selected(selection, &model, &selected_node_iter)) {

        // Add the text to the selected node
        GtkTreeStore *store = GTK_TREE_STORE(model);
        added_node_iter = agregar_nodo_tree(store, &selected_node_iter, text);

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