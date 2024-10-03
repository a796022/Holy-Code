#pragma once

/**
 * @brief Reads the last opened file from the session file.
 * 
 * @param tree_path_file Pointer to the char* where the path of the last opened
 * file will be stored.
 * 
 * @return void
 */
void read_last_opened_file(char** tree_path_file);

/**
 * Guarda el último archivo abierto.
 * En el fichero de sesión se guarda como LastOpenedFile=nombre_fichero.
 * 
 * @param filename Nombre del archivo
 * 
 * @return void
 */
void write_last_opened_file(const char *filename);