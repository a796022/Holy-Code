#include <gtk/gtk.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "files_manager.h"

/**
 * Devuelve el directorio HOME del usuario.
 * 
 * @return char*
*/
char *get_home_dir() {
    return getenv("HOME");
}
