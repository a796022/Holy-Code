#ifndef TREE_FILES_H
#define TREE_FILES_H

/**
 * Carga un árbol de un fichero
 * 
 * @param model Modelo de datos del árbol
 * @param filename Nombre del fichero
 * 
 * @return void
 */
void cargar_fichero_arbol(GtkTreeStore *model, const char *filename);

#endif /* TREE_FILES_H */