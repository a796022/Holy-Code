#include <gtk/gtk.h>

#include "tree_manager.h"
#include "tree.h"
#include "window_manager.h"
#include "session_manager.h"
#include "tree_files.h"
#include "history.h"

// Main window tree data model
GtkTreeStore *MAIN_TREE_MODEL;

// Widget of the main window tree
GtkWidget *MAIN_TREE_VIEW;

// Path of the file in session
char *TREE_PATH_FILE = NULL;

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
GtkWidget *inicializar_arbol_principal() {
    // Crear un modelo de árbol para el TreeView
    MAIN_TREE_MODEL = crear_modelo_datos_tree();

    // Crear el TreeView
    MAIN_TREE_VIEW = crear_tree_view(MAIN_TREE_MODEL);

    // Obtener el último fichero abierto
    TREE_PATH_FILE = read_last_opened_file();
    
    // Si hay un fichero en sesión, se carga
    if (TREE_PATH_FILE != NULL) {
        cargar_arbol(MAIN_TREE_MODEL, TREE_PATH_FILE);
    }

    // Se crea una columna para el TreeView
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
void cargar_arbol_principal() {
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

            // Delete the selected node
            gtk_tree_store_remove(store, &iter);

        }

    }
}