#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

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

#endif /* SESSION_MANAGER_H */