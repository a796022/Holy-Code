#include <gtk/gtk.h>
#include <sys/stat.h>

#include "session_manager.h"

const char *SESSION_FILE_PATH_FROM_HOME = "/.config/wizard/session.txt";
const int MAX_PATH_LENGTH = 256;

/**
 * @brief Checks if the session file exists, if not, creates it.
 * 
 * @return void
 */
static void check_session_file() {
    // Get the HOME directory of the user
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        g_printerr("Error: HOME environment variable not set.\n");
        return;
    }

    // If the ~/.config directory does not exist, create it
    char config_dir[MAX_PATH_LENGTH];
    snprintf(config_dir, sizeof(config_dir), "%s/.config", home_dir);
    if (mkdir(config_dir, 0755) == -1 && errno != EEXIST) {
        g_printerr("Error creating directory: %s\n", strerror(errno));
        return;
    }

    // If the wizard directory does not exist, create it
    char wizard_dir[MAX_PATH_LENGTH];
    snprintf(wizard_dir, sizeof(wizard_dir), "%s/wizard", config_dir);
    if (mkdir(wizard_dir, 0755) == -1 && errno != EEXIST) {
        g_printerr("Error creating directory: %s\n", strerror(errno));
        return;
    }

    // If the session file does not exist, create it
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
 * @brief Reads the last opened file from the session file.
 * 
 * @param tree_path_file Pointer to the char* where the path of the last opened
 * file will be stored.
 * 
 * @return void
 */
void read_last_opened_file(char** tree_path_file) {
    // By default, the file is NULL
    *tree_path_file = NULL;

    // Check the session file exists, if not, create it
    check_session_file();
    
    // Get the HOME directory of the user
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        g_printerr("Error: HOME environment variable not set.\n");
        return;
    }
    
    // Get the session file
    char session_file[MAX_PATH_LENGTH];
    snprintf(session_file, sizeof(session_file), "%s%s", home_dir, SESSION_FILE_PATH_FROM_HOME);
    FILE *file = fopen(session_file, "r");
    if (file == NULL) {
        g_printerr("Error opening session file: %s\n", strerror(errno));
        return;
    }

    // Get the size of the session file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Reserve memory for file content
    *tree_path_file = malloc(file_size + 1);
    if (*tree_path_file == NULL) {
        fclose(file);
        return;
    }

    // Read the content of the file
    fread(*tree_path_file, 1, file_size, file);
    (*tree_path_file)[file_size] = '\0';
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
    const char *home_dir = getenv("HOME");
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