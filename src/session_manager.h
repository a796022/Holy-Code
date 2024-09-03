#pragma once

/**
 * Obtiene el último archivo abierto.
 * En el fichero de sesión se guarda como LastOpenedFile=nombre_fichero.
 * 
 * @return char*
 */
char *read_last_opened_file();

/**
 * Guarda el último archivo abierto.
 * En el fichero de sesión se guarda como LastOpenedFile=nombre_fichero.
 * 
 * @param filename Nombre del archivo
 * 
 * @return void
 */
void write_last_opened_file(const char *filename);