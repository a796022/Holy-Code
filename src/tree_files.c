#include <gtk/gtk.h>

#include "tree_files.h"
#include "tree_string.h"
#include "tree_wrapper.h"
#include "gtk_progress_bar.h"
#include "window_structure.h"

/**
 * @brief write the current node, then call the child, then call the next sibling
 * 
 * @param model Tree data model
 * @param iter Current node
 * @param file File to write
 * @param level Level of the node
 * @param num_nodes Number of nodes
 * @param added_nodes Number of added nodes
 * 
 * @return void
 */
void write_tree_file_recursive(GtkTreeStore *model, GtkTreeIter *iter, FILE *file, int level, int num_nodes, int *added_nodes, GtkWidget* progress_bar) {
    // Write the node to the file
    gchar *text;
    gtk_tree_model_get(GTK_TREE_MODEL(model), iter, 0, &text, -1);
    for (int i = 0; i < level; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "%s\n", text);
    g_free(text);

    // Mark progress
    (*added_nodes)++;
    gdouble progress = (gdouble)(*added_nodes) / (gdouble)num_nodes;
    set_progress_bar_value(progress_bar, progress);

    // Call the child
    GtkTreeIter child;
    if (gtk_tree_model_iter_children(GTK_TREE_MODEL(model), &child, iter)) {
        write_tree_file_recursive(model, &child, file, level + 1, num_nodes, added_nodes, progress_bar);
    }

    // Call the next sibling
    GtkTreeIter sibling = *iter;
    if (gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &sibling)) {
        write_tree_file_recursive(model, &sibling, file, level, num_nodes, added_nodes, progress_bar);
    }
}

/**
 * @brief Load a tree from a file.
 * 
 * @param model Tree data model
 * @param filename File name
 * 
 * @return int status
 * 
 * status:
 * 0: success
 * 1: error in node hierarchy, two root nodes found.
 * 2: error in the node hierarchy, no parent node found
 * -1: error opening the file
 */
int read_tree_file(struct WindowStructure* window_structure, const char *filename, GtkWidget* tree_view) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    // Get the model
    GtkTreeStore* tree_model = window_structure->tree_model;

    // Hago una primera lectura del árbol para obtener el tamaño máximo de línea
    // y el número máximo de tabulaciones.
    int max_line_length = 0;
    int max_tabs = 0;
    obtener_maximo_caracteres_tabulaciones(filename, &max_line_length, &max_tabs);

    // Para construir la jerarquía de nodos necesito almacenar los nodos padres
    GtkTreeIter padres[max_tabs + 1];

    // Construcción del árbol
    char line[max_line_length + 1];
    int last_node_level = -1;
    int status = 0;
    while (fgets(line, max_line_length + 1, file) != NULL) {
        // Obtengo el número de tabulaciones al inicio de la línea
        int current_node_level = obtener_numero_tabulaciones(line);

        // Elimino del string los carácteres innecesarios
        clean_string(line);

        // Agrego el nodo al árbol
        if (current_node_level == 0) {
            if (last_node_level == -1) {
                padres[0] = add_node(tree_view, tree_model, NULL, line);
                last_node_level = 0;
            } else {
                return 1;
            }
        } else {
            if (current_node_level > last_node_level + 1) {
                for (int i = last_node_level + 1; i < current_node_level; i++) {
                    if (i == 0) {
                        padres[i] = add_node(tree_view, tree_model, NULL, "[NULL]");
                    } else {
                        padres[i] = add_node(tree_view, tree_model, &padres[i - 1], "[NULL]");
                    }
                }

                status = 2;
            }

            padres[current_node_level] = add_node(tree_view, tree_model, &padres[current_node_level - 1], line);
            last_node_level = current_node_level;
        }
    }

    fclose(file);

    return status;
}

/**
 * @brief Write a tree to a file.
 * 
 * @param model Tree data model
 * @param filename File name
 * @param num_nodes Number of nodes
 * @param added_nodes Number of added nodes
 * 
 * @return int status
 */
int write_tree_file(struct WindowStructure* window_structure, const char *filename, int num_nodes) {
    GtkTreeStore* model = window_structure->tree_model;
    GtkWidget* progress_bar = window_structure->progress_bar;

    // Open the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    // Show the progress bar
    show_progress_bar(progress_bar);

    // Write the tree to the file
    GtkTreeIter iter;
    int added_nodes = 0;
    if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &iter)) {
        write_tree_file_recursive(model, &iter, file, 0, num_nodes, &added_nodes, progress_bar);
    }

    // Hide the progress bar
    hide_progress_bar(progress_bar);

    // Close the file
    fclose(file);

    return 0;
}