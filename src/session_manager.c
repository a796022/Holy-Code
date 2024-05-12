#include <gtk/gtk.h>
#include <sys/stat.h>

#include "session_manager.h"
#include "files_manager.h"

const char *SESSION_FILE_PATH_FROM_HOME = "/.config/wizard/session.txt";
const int MAX_PATH_LENGTH = 256;

/**
 * Comprueba si existe el archivo de sesión y lo crea si no existe.
 * 
 * @return void
 */
void check_session_file() {
    // Obtengo el directori HOME del usuario
    const char *home_dir = get_home_dir();
    if (home_dir == NULL) {
        g_printerr("Error: HOME environment variable not set.\n");
        return;
    }

    // Si no existe el directorio ~/.config, lo creo
    char config_dir[MAX_PATH_LENGTH];
    snprintf(config_dir, sizeof(config_dir), "%s/.config", home_dir);
    if (mkdir(config_dir, 0755) == -1 && errno != EEXIST) {
        g_printerr("Error creating directory: %s\n", strerror(errno));
        return;
    }

    // Si no existe el directorio ~/.config/wizard, lo creo
    char wizard_dir[MAX_PATH_LENGTH];
    snprintf(wizard_dir, sizeof(wizard_dir), "%s/wizard", config_dir);
    if (mkdir(wizard_dir, 0755) == -1 && errno != EEXIST) {
        g_printerr("Error creating directory: %s\n", strerror(errno));
        return;
    }

    // Si no existe el archivo de configuración, lo creo
    char session_file[MAX_PATH_LENGTH];
    snprintf(session_file, sizeof(session_file), "%s/session.txt", wizard_dir);
    if (access(session_file, F_OK) == -1) {
        FILE *file = fopen(session_file, "w");
        if (file == NULL) {
            g_printerr("Error creating session file: %s\n", strerror(errno));
            return;
        }
        fclose(file);
    }
}

/**
 * Obtiene el último archivo abierto.
 * En el fichero de sesión se guarda como LastOpenedFile=nombre_fichero.
 * 
 * @return char*
 */
char *read_last_opened_file() {
    // Compruebo el archivo de sesión
    check_session_file();
    
    // Obtengo el directorio HOME del usuario
    const char *home_dir = get_home_dir();
    if (home_dir == NULL) {
        g_printerr("Error: HOME environment variable not set.\n");
        return NULL;
    }
    
    // Obtengo el archivo de sesión
    char session_file[MAX_PATH_LENGTH];
    snprintf(session_file, sizeof(session_file), "%s%s", home_dir, SESSION_FILE_PATH_FROM_HOME);
    FILE *file = fopen(session_file, "r");
    if (file == NULL) {
        g_printerr("Error opening session file: %s\n", strerror(errno));
        return NULL;
    }

    // Obtengo el valor de la línea "LastOpenedFile=path"
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        if (strncmp(line, "LastOpenedFile=", 15) == 0) {
            char *path = line + 15;
            path[strlen(path) - 1] = '\0';
            fclose(file);
            
            // Si la línea está vacía, devuelvo NULL
            if (strlen(path) == 0) {
                return NULL;
            }

            return path;
        }
    }
    fclose(file);

    // Si no se ha encontrado la línea, la escribo y devuelvo NULL
    file = fopen(session_file, "a");
    if (file == NULL) {
        g_printerr("Error opening session file: %s\n", strerror(errno));
        return NULL;
    }
    fprintf(file, "LastOpenedFile=\n");
    fclose(file);

    return NULL;
}

/**
 * Guarda el último archivo abierto.
 * En el fichero de sesión se guarda como LastOpenedFile=nombre_fichero.
 * 
 * @param filename Nombre del archivo
 * 
 * @return void
 */
void write_last_opened_file(const char *filename) {
    // Compruebo el archivo de sesión
    check_session_file();
    
    // Obtengo el directorio HOME del usuario
    const char *home_dir = get_home_dir();
    if (home_dir == NULL) {
        g_printerr("Error: HOME environment variable not set.\n");
        return;
    }
    
    // Obtengo el archivo de sesión
    char session_file[MAX_PATH_LENGTH];
    snprintf(session_file, sizeof(session_file), "%s%s", home_dir, SESSION_FILE_PATH_FROM_HOME);
    FILE *file = fopen(session_file, "r");
    if (file == NULL) {
        g_printerr("Error opening session file: %s\n", strerror(errno));
        return;
    }

    // Creo un archivo temporal
    char temp_file[MAX_PATH_LENGTH];
    snprintf(temp_file, sizeof(temp_file), "%s.tmp", session_file);
    FILE *temp = fopen(temp_file, "w");
    if (temp == NULL) {
        g_printerr("Error opening temporary file: %s\n", strerror(errno));
        fclose(file);
        return;
    }

    // Copio el contenido del archivo de sesión al temporal
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int found = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        if (strncmp(line, "LastOpenedFile=", 15) == 0) {
            fprintf(temp, "LastOpenedFile=%s\n", filename);
            found = 1;
        } else {
            fprintf(temp, "%s", line);
        }
    }

    // Si no se ha encontrado la línea, la escribo
    if (!found) {
        fprintf(temp, "LastOpenedFile=%s\n", filename);
    }
    
    fclose(file);
    fclose(temp);

    // Reemplazo el archivo de sesión por el temporal
    if (rename(temp_file, session_file) == -1) {
        g_printerr("Error renaming temporary file: %s\n", strerror(errno));
    }
}