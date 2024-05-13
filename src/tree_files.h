#ifndef TREE_FILES_H
#define TREE_FILES_H

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
int cargar_fichero_arbol(GtkTreeStore *model, const char *filename);

#endif /* TREE_FILES_H */