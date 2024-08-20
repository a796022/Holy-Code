#include <gtk/gtk.h>

#include "tree_string.h"

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
 * Elimina del string el salto de línea y las tabulaciones y espacios iniciales.
 * 
 * @param line String
 * 
 * @return void
*/
void string_to_string_nodo(char *line) {
    line[strcspn(line, "\n")] = 0;

    int i = 0;
    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }
    char *line_content = line + i;

    strcpy(line, line_content);
}

/**
 * @brief Remove all line breaks from the string. Then, remove leading tabs and leading spaces.
 * 
 * @param line String to be cleaned
 * 
 * @return void
 */
void clean_string(char *line) {
    // Remove all line breaks
    char *src = line, *dst = line;
    while (*src) {
        if (*src != '\n' && *src != '\r') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';  // Null-terminate the cleaned string

    // Remove leading tabs and leading spaces
    src = line;
    while (*src == ' ' || *src == '\t') {
        src++;
    }

    // If src moved, shift the string to the left
    if (src != line) {
        memmove(line, src, strlen(src) + 1);
    }
}