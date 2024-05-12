#include <gtk/gtk.h>

#include "tree.h"

/**
 * Crea un modelo de datos para un árbol.
 * 
 * @return GtkTreeStore*
*/
GtkTreeStore *crear_modelo_datos_tree() {
    // Primer parámetro: cantidad de columnas
    // Segundo parámetro: tipo de datos de la primera columna
    GtkTreeStore *model = gtk_tree_store_new(1, G_TYPE_STRING);
    return model;
}

/**
 * Crea un TreeView partiendo de un modelo de datos.
 * 
 * @param model Modelo de datos del TreeView.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_tree_view(GtkTreeStore *model) {
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
    return tree_view;
}

/**
 * Agrega un nodo al árbol.
 * 
 * @param model Modelo de datos al que se le agrega el nodo.
 * @param padre Nodo padre del nodo a agregar. Si es NULL, se agrega un nodo raíz.
 * @param texto Texto a agregar en el nodo.
 * 
 * return GtkTreeIter
*/
GtkTreeIter agregar_nodo_tree(GtkTreeStore *model, GtkTreeIter *padre, const char *texto) {
    GtkTreeIter iter;

    /**
     * - model: modelo de datos al que se le agrega el nodo.
     * - iter: iterador que apuntará al nodo agregado.
     * - padre: iterador que apunta al nodo padre del nodo a agregar. Si es 
     * NULL, se agrega un nodo raíz.
    */
    gtk_tree_store_append(model, &iter, padre);

    /**
     * - model: modelo de datos al que se le agrega el nodo.
     * - iter: iterador que apuntará al nodo agregado.
     * - 0: columna en la que se agrega el texto (en principio, siempre 0).
     * - texto: texto a agregar en la columna.
     * - -1: fin de la lista de argumentos.
    */
    gtk_tree_store_set(model, &iter, 0, texto, -1);

    return iter;
}

/**
 * Crea una columna para un TreeView.
 * 
 * @param tree_view TreeView al que se le agregará la columna.
 * @param titulo Título de la columna.
 * 
 * @return void
*/
void crear_columna_tree_view(GtkWidget *tree_view, const char *titulo) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(titulo, renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
}

/**
 * Obtiene el máximo de caracteres y tabulaciones (considerando tabulaciones a
 * el caracter '\t' o 4 espacios seguidos) de un fichero.
 * 
 * @param filename Nombre del fichero
 * @param max_line_length Puntero a la variable donde se almacenará el máximo de caracteres
 * @param max_tabs Puntero a la variable donde se almacenará el máximo de tabulaciones
 * 
 * @return void
*/
void obtener_maximo_caracteres_tabulaciones(const char *filename, int *max_line_length, int *max_tabs) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    int current_line_length = 0;
    char c;

    int nueva_linea = 1;
    int racha_tabulaciones = 0;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            // Para obtener el máximo de caracteres
            if (current_line_length > *max_line_length) {
                *max_line_length = current_line_length;
            }
            current_line_length = 0;

            // Para obtener el máximo de tabulaciones
            if (racha_tabulaciones > *max_tabs) {
                *max_tabs = racha_tabulaciones;
            }
            racha_tabulaciones = 0;
            nueva_linea = 1;
        } else {
            // Para obtener el máximo de caracteres
            current_line_length++;

            // Para obtener el máximo de tabulaciones
            if (nueva_linea) {
                if (c == ' ') {
                    racha_tabulaciones++;
                } else if (c == '\t') {
                    racha_tabulaciones += 4;
                } else {
                    if (racha_tabulaciones > *max_tabs) {
                        *max_tabs = racha_tabulaciones;
                    }
                    racha_tabulaciones = 0;
                    nueva_linea = 0;
                }
            }
        }
    }

    if (current_line_length > *max_line_length) {
        *max_line_length = current_line_length;
    }
    if (racha_tabulaciones > *max_tabs) {
        *max_tabs = racha_tabulaciones;
    }

    *max_line_length += 1;
    *max_tabs /= 4;

    fclose(file);
}

/**
 * Devuelve el número de tabulaciones o grupos de 4 espacios al inicio de un string.
 * 
 * @param str String
 * 
 * @return int
*/
int obtener_numero_tabulaciones(const char *str) {
    int num_tabs = 0;
    for (int i = 0; str[i] == ' ' || str[i] == '\t'; i++) {
        if (str[i] == '\t') {
            num_tabs += 4;
        } else {
            num_tabs++;
        }
    }
    return num_tabs / 4;
}

/**
 * Carga un árbol de un fichero
 * 
 * @param model Modelo de datos del árbol
 * @param filename Nombre del fichero
 * 
 * @return void
*/
void cargar_arbol(GtkTreeStore *model, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    // Primero, vacío el árbol
    gtk_tree_store_clear(model);

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

        //////////////
        // Elimino el salto de línea
        line[strcspn(line, "\n")] = 0;

        // Elimino del string las tabulaciones y espacios iniciales
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') {
            i++;
        }
        char *line_content = line + i;
        //////////////

        // Agrego el nodo al árbol
        if (current_node_level == 0) {
            if (last_node_level == -1) {
                padres[0] = agregar_nodo_tree(model, NULL, line_content);
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

            padres[current_node_level] = agregar_nodo_tree(model, &padres[current_node_level - 1], line_content);
            last_node_level = current_node_level;
        }
    }

    fclose(file);
}