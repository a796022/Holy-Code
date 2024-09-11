#pragma once

#include "window_manager.h"

/**
 * Carga un árbol de un fichero
 * 
 * @param model Modelo de datos del árbol
 * @param filename Nombre del fichero
 * 
 * @return int status
 * 
 * status:
 * 0: éxito
 * 1: error en la jerarquía de nodos, se encontraron dos nodos raíz
 * 2: error en la jerarquía de nodos, ausencia de nodos padre
 * -1: error al abrir el fichero
 */
int read_tree_file(struct WindowStructure* window_structure, const char *filename, GtkWidget* tree_view);

/**
 * @brief Write a tree to a file.
 * 
 * @param model Tree data model
 * @param filename File name
 * @param num_nodes Number of nodes
 * 
 * @return int status
 */
int write_tree_file(GtkTreeStore *model, const char *filename, int num_nodes);