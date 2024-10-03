#include <gtk/gtk.h>

// #include "../external/sds/sds.h"

// #include "gtk_box_manager.h"
// #include "gtk_progress_bar.h"
// #include "history.h"
// #include "tree_wrapper.h"
// #include "window_manager.h"
// #include "window_structure.h"

#define MAIN_WINDOW_HEIGHT 500
#define MAIN_WINDOW_MIN_HEIGHT 200
#define MAIN_WINDOW_MIN_WIDTH 300
#define MAIN_WINDOW_RESIZABILITY TRUE
#define MAIN_WINDOW_TITLE "Sin Título - Wizard"
#define MAIN_WINDOW_WIDTH 900

// MAIN WINDOW /////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the GtkWidget* pointed by main_window as a new main
 * window.
 * 
 * @param main_window Pointer to the GtkWidget* that will be initialized as a
 * new main window.
 * 
 * @return void
*/
void new_main_window(GtkWidget** main_window) {
    // Create the window
    *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Set the window properties
    gtk_window_set_title(GTK_WINDOW(*main_window), MAIN_WINDOW_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(*main_window), MAIN_WINDOW_WIDTH,
                                MAIN_WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(*main_window), MAIN_WINDOW_RESIZABILITY);
    gtk_widget_set_size_request(*main_window, MAIN_WINDOW_MIN_WIDTH,
                                MAIN_WINDOW_MIN_HEIGHT);

    /* NOTE: the behavior of the window when it is closed is programmed in the
    WindowStructure's part of GList. This is because closing a window means also
    deleting its corresponding WindowStructure from the GList, moreover, a query
    to the history -which is at the WindowStructure level- is required to know
    if it is necessary to ask the user if he wants to save changes without
    saving.*/

    // Show the window
    gtk_widget_show(*main_window);
}

/**
 * @brief Shows a dialog asking the user if they want to save the changes in
 * case there are unsaved changes. The dialog shows the options save (save and
 * quit), discard (discard changes and quit) and cancel (do not quit).
 * 
 * @param widget Window to which the "delete-event" signal will be set.
 * @param event Event that triggered the signal.
 * @param data Data passed to the signal.
 * 
 * @return gboolean TRUE if the window should not be closed, FALSE if the window should be closed.
 */
gboolean on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    // Get the data
    struct WindowStructure* window_structure = (struct WindowStructure*)data;
    struct History *history = window_structure->history;

    // If there are unsaved changes, ask the user if they want to save the changes
    if (there_are_unsaved_changes(history)) {

        // Show a dialog asking the user if they want to save the changes
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(widget),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_WARNING,
                                                   GTK_BUTTONS_NONE,
                                                   "¿Guardar cambios?");
        
        gtk_dialog_add_buttons(GTK_DIALOG(dialog),
                               "Cancelar", GTK_RESPONSE_CANCEL,
                               "Descartar", GTK_RESPONSE_REJECT,
                               "Guardar", GTK_RESPONSE_ACCEPT,
                               NULL);

        gint response = gtk_dialog_run(GTK_DIALOG(dialog));

        // Close the dialog
        gtk_widget_destroy(dialog);

        // Process the response
        switch (response) {
            case GTK_RESPONSE_ACCEPT:
                save_tree(NULL, window_structure);
                return FALSE;
            case GTK_RESPONSE_REJECT:
                return FALSE;
            case GTK_RESPONSE_CANCEL:
            default:
                return TRUE;
        }
    }

    // If there are no unsaved changes, close the window
    return FALSE;
}

// /**
//  * Muestra un diálogo general y devuelve la respuesta.
//  * 
//  * @param dialog Diálogo a mostrar.
//  * 
//  * @return gint
// */
// gint mostrar_dialogo(GtkWidget *dialog) {
//     return gtk_dialog_run(GTK_DIALOG(dialog));
// }

// /**
//  * Muestra un diálogo con un mensaje.
//  * 
//  * @param window Ventana a la que se asociará el diálogo.
//  * @param mensaje Mensaje a mostrar en el diálogo.
//  * @param titulo Título del diálogo.
//  * 
//  * @return void
// */
// void mostrar_dialogo_mensaje(GtkWidget *window, const char *mensaje, const char *titulo) {
//     GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
//                                                GTK_DIALOG_MODAL,
//                                                GTK_MESSAGE_INFO,
//                                                GTK_BUTTONS_OK,
//                                                mensaje);

//     if (titulo != NULL) {
//         gtk_window_set_title(GTK_WINDOW(dialog), titulo);
//     }

//     mostrar_dialogo(dialog);
//     gtk_widget_destroy(dialog);
// }

// /**
//  * Crea un diálogo selector de archivos.
//  * 
//  * @param parent Ventana padre del diálogo.
//  * 
//  * @return GtkWidget*
// */
// GtkWidget *crear_dialogo_selector_archivos(GtkWidget *parent) {
//     return gtk_file_chooser_dialog_new("Abrir archivo",
//                                        GTK_WINDOW(parent),
//                                        GTK_FILE_CHOOSER_ACTION_OPEN,
//                                        "Cancelar",
//                                        GTK_RESPONSE_CANCEL,
//                                        "Abrir",
//                                        GTK_RESPONSE_ACCEPT,
//                                        NULL);
// }

// /**
//  * Obtiene el fichero seleccionado de un diálogo selector.
//  * 
//  * @param dialog Diálogo selector de archivos.
//  * 
//  * @return char*
// */
// char *obtener_fichero_seleccionado(GtkWidget *dialog) {
//     return gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
// }

// /**
//  * Muestra la ventana.
//  * 
//  * @param window Ventana a mostrar.
//  * 
//  * @return void
// */
// void show_window(struct WindowStructure* window_structure) {
//     // Get the data
//     GtkWidget* window = window_structure->window;
//     GtkWidget* progress_bar = window_structure->progress_bar;

//     // Muestro todos los widgets de la ventana
//     gtk_widget_show_all(window);

//     // Oculto los windgets que deben estar ocultos al inicio
//     hide_progress_bar(progress_bar);
// }

/**
 * @brief Closes a window
 * 
 * - Displays a dialog asking the user if they want to save the changes if there are unsaved changes.
 * - The window is closed if the user chooses to save the changes or discard the changes.
 * 
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal.
 * 
 * @return void
*/
void close_window(GtkMenuItem *menuitem, gpointer user_data) {
    // Get the data
    struct WindowStructure* window_structure = (struct WindowStructure*)user_data;
    GtkWidget *window = window_structure->window;
    // there_are_unsaved_changes(window_structure->history);

    // Ask the user if they want to save the changes
    gboolean abort_closing = on_delete_event(window, NULL, window_structure);

    // Close the window if the user chooses to save the changes or discard the changes
    if (!abort_closing) {
        gtk_widget_destroy(window);
    }
}

// /**
//  * @brief Show a popup window with the width and height information of the window.
//  * 
//  * @param menuitem Menu item that triggered the signal.
//  * @param user_data Data passed to the signal.
//  * 
//  * @return void
// */
// void show_window_info(GtkMenuItem *menuitem, gpointer user_data) {
//     // Get the width and height of the window
//     gint width, height;
//     GtkWidget *window = GTK_WIDGET(user_data);
//     gtk_window_get_size(GTK_WINDOW(window), &width, &height);

//     // Calculate the size of the message
//     int size = snprintf(NULL, 0, "Anchura: %dpx\nAltura: %dpx", width, height);

//     // Allocate memory for the message
//     char* message = g_new(char, size + 1);
//     if (message == NULL) {
//         perror("Error allocating memory for the window information message");
//         return;
//     }

//     // Create the message
//     snprintf(message, size + 1, "Anchura: %dpx\nAltura: %dpx", width, height);
//     const char* title = "Información de la ventana";
    
//     mostrar_dialogo_mensaje(window, message, title);

//     // Free the memory
//     g_free(message);
// }

// /**
//  * @brief Shows a file selector window and returns the path of the selected file.
//  * 
//  * - Shows a file selector window.
//  * - Returns the path of the selected file.
//  * - If the user has not selected a file, returns NULL.
//  * 
//  * @param window Window to which the dialog will be associated.
//  * 
//  * @return char*
// */
// char *show_file_selector_window(GtkWidget *window) {
//     // Seleccionar un fichero desde el sistema de archivos
//     GtkWidget *dialog = crear_dialogo_selector_archivos(window);

//     // Mostrar el diálogo
//     gint res = mostrar_dialogo(dialog);

//     // Si el usuario ha seleccionado un archivo
//     if (res == GTK_RESPONSE_ACCEPT) {
//         // Obtener la ruta del archivo
//         char *filename = obtener_fichero_seleccionado(dialog);

//         // Cerrar el diálogo
//         gtk_widget_destroy(dialog);

//         return filename;
//     }

//     // Cerrar el diálogo
//     gtk_widget_destroy(dialog);

//     return NULL;
// }

// /**
//  * @brief Sets the title of the window as unsaved.
//  * 
//  * - Add a bullet and a space (• ) at the beginning of the title.
//  * 
//  * @return void
//  */
// void set_title_unsaved(GtkWidget *window) {
//     // Get the title of the window
//     const char *title = gtk_window_get_title(GTK_WINDOW(window));

//     // Add a bullet and a space (• ) at the beginning of the title
//     sds new_title = sdsnew("• ");
//     new_title = sdscat(new_title, title);

//     // Set the new title
//     gtk_window_set_title(GTK_WINDOW(window), new_title);

//     // Free the memory
//     sdsfree(new_title);
// }

// /**
//  * @brief Sets the title of the window as saved.
//  * 
//  * - Remove the bullet and the space (• ) at the beginning of the title.
//  * 
//  * @return void
//  */
// void set_title_as_saved(GtkWidget *window) {
//     // Get the title of the window
//     const char *title = gtk_window_get_title(GTK_WINDOW(window));

//     // Remove the bullet and the space (• ) at the beginning of the title
//     sds new_title = sdsnew(title + 4);

//     // Set the new title
//     gtk_window_set_title(GTK_WINDOW(window), new_title);

//     // Free the memory
//     sdsfree(new_title);
// }

// /**
//  * @brief Creates a new window with an empty tree proyect (no file is associated).
//  * 
//  * @return void
//  */
// void create_new_window() {
//     printf("Creating new window...\n");
// }