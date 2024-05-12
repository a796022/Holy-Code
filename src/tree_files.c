#include <gtk/gtk.h>

#include "tree_files.h"
#include "tree_string.h"
#include "tree.h"

/**
 * Carga un árbol de un fichero
 * 
 * @param model Modelo de datos del árbol
 * @param filename Nombre del fichero
 * 
 * @return void
 */
void cargar_fichero_arbol(GtkTreeStore *model, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

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
    while (fgets(line, max_line_length + 1, file) != NULL) {
        // Obtengo el número de tabulaciones al inicio de la línea
        int current_node_level = obtener_numero_tabulaciones(line);

        // Elimino del string los carácteres innecesarios
        string_to_string_nodo(line);

        // Agrego el nodo al árbol
        if (current_node_level == 0) {
            if (last_node_level == -1) {
                padres[0] = agregar_nodo_tree(model, NULL, line);
                last_node_level = 0;
            } else {
                return;
            }
        } else {
            if (current_node_level > last_node_level + 1) {
                for (int i = last_node_level + 1; i < current_node_level; i++) {
                    if (i == 0) {
                        padres[i] = agregar_nodo_tree(model, NULL, "[NULL]");
                    } else {
                        padres[i] = agregar_nodo_tree(model, &padres[i - 1], "[NULL]");
                    }
                }
            }

            padres[current_node_level] = agregar_nodo_tree(model, &padres[current_node_level - 1], line);
            last_node_level = current_node_level;
        }
    }

    fclose(file);
}