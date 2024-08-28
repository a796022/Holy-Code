#include <gtk/gtk.h>

#include "../external/sds/sds.h"

#include "box.h"
#include "gtk_progress_bar.h"
#include "tree_wrapper.h"
#include "history.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const int ANCHO_VENTANA = 900;
const int ALTO_VENTANA = 500;
const gboolean REDIMENSIONABLE = TRUE;
const int ANCHO_MINIMO_VENTANA = 300;
const int ALTO_MINIMO_VENTANA = 200;

GList *WINDOWS_LIST = NULL;

/**
 * @brief Adds a window to the list of windows.
 * 
 * - Adds a window to the list of windows.
 * 
 * @return GtkWidget* Window added to the list
 */
GtkWidget *create_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    WINDOWS_LIST = g_list_append(WINDOWS_LIST, window);
    return window;
}

/**
 * Establece el nombre de la ventana, que se mostrará en la barra de título.
 * 
 * @param window Ventana a la que se le establecerá el nombre.
 * @param nombre Nombre de la ventana.
 * 
 * @return void
*/
void establecer_nombre_ventana(GtkWidget *window, const char *nombre) {
    gtk_window_set_title(GTK_WINDOW(window), nombre);
}

/**
 * Establece el tamaño por defecto de la ventana.
 * 
 * @param window Ventana a la que se le establecerá el tamaño por defecto.
 * @param ancho Ancho de la ventana.
 * @param alto Alto de la ventana.
 * 
 * @return void
*/
void establecer_tamano_por_defecto_ventana(GtkWidget *window, int ancho, int alto) {
    gtk_window_set_default_size(GTK_WINDOW(window), ancho, alto);
}

/**
 * Establece si la ventana es redimensionable.
 * 
 * @param window Ventana a la que se le establecerá si es redimensionable.
 * @param redimensionable TRUE si la ventana es redimensionable, FALSE en caso contrario.
 * 
 * @return void
*/
void establecer_redimensionable_ventana(GtkWidget *window, gboolean redimensionable) {
    gtk_window_set_resizable(GTK_WINDOW(window), redimensionable);
}

/**
 * Establece el tamaño mínimo de la ventana.
 * 
 * @param window Ventana a la que se le establecerá el tamaño mínimo.
 * @param ancho Ancho mínimo de la ventana.
 * @param alto Alto mínimo de la ventana.
 * 
 * @return void
*/
void establecer_tamano_minimo_ventana(GtkWidget *window, int ancho, int alto) {
    gtk_widget_set_size_request(window, ancho, alto);
}

/**
 * @brief Shows a dialog asking the user if they want to save the changes in case there are unsaved changes.
 * 
 * - Shows a dialog asking the user if they want to save the changes.
 * - If the user chooses to save the changes, the tree is saved and the window is closed.
 * - If the user chooses to discard the changes, the window is closed without saving.
 * - If the user chooses to cancel, the window is not closed.
 * 
 * @param widget Window to which the "delete-event" signal will be set.
 * @param event Event that triggered the signal.
 * @param data Data passed to the signal.
 * 
 * @return gboolean TRUE if the window should not be closed, FALSE if the window should be closed.
 */
gboolean on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    // If there are unsaved changes, ask the user if they want to save the changes
    if (there_are_unsaved_changes()) {

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
                save_tree();
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

/**
 * @brief Connects the window's “delete-event” signal to the on_delete_event() function.
 * 
 * - Connects the window's “delete-event” signal to the on_delete_event() function so that, when the window is closed, the user is asked if they want to save the changes if there are unsaved changes.
 * 
 * @param window Window to which the "delete-event" signal will be set.
 * 
 * @return void
 */
void configure_delete_event_signal(GtkWidget *window) {
    g_signal_connect(window, "delete-event", G_CALLBACK(on_delete_event), NULL);
}

/**
 * @brief Connects the window's “destroy” signal to the gtk_main_quit() function.
 * 
 * - Connects the window's “destroy” signal to the gtk_main_quit() function so that, when the window is closed, the GTK main event loop is also terminated (and thus terminates the program).
 * 
 * @param window Ventana a la que se le establecerá la señal "destroy".
 * 
 * @return void
*/
void configure_destroy_signal(GtkWidget *window) {
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

/**
 * Agrega un widget a la ventana.
 * 
 * @param window Ventana a la que se le agregará el widget.
 * @param widget Widget a agregar.
 * 
 * @return void
*/
void agregar_widget_ventana(GtkWidget *window, GtkWidget *widget) {
    gtk_container_add(GTK_CONTAINER(window), widget);
}

/**
 * Muestra un diálogo general y devuelve la respuesta.
 * 
 * @param dialog Diálogo a mostrar.
 * 
 * @return gint
*/
gint mostrar_dialogo(GtkWidget *dialog) {
    return gtk_dialog_run(GTK_DIALOG(dialog));
}

/**
 * Muestra un diálogo con un mensaje.
 * 
 * @param window Ventana a la que se asociará el diálogo.
 * @param mensaje Mensaje a mostrar en el diálogo.
 * @param titulo Título del diálogo.
 * 
 * @return void
*/
void mostrar_dialogo_mensaje(GtkWidget *window, const char *mensaje, const char *titulo) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               mensaje);

    if (titulo != NULL) {
        gtk_window_set_title(GTK_WINDOW(dialog), titulo);
    }

    mostrar_dialogo(dialog);
    gtk_widget_destroy(dialog);
}

/**
 * Crea un diálogo selector de archivos.
 * 
 * @param parent Ventana padre del diálogo.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_dialogo_selector_archivos(GtkWidget *parent) {
    return gtk_file_chooser_dialog_new("Abrir archivo",
                                       GTK_WINDOW(parent),
                                       GTK_FILE_CHOOSER_ACTION_OPEN,
                                       "Cancelar",
                                       GTK_RESPONSE_CANCEL,
                                       "Abrir",
                                       GTK_RESPONSE_ACCEPT,
                                       NULL);
}

/**
 * Obtiene el fichero seleccionado de un diálogo selector.
 * 
 * @param dialog Diálogo selector de archivos.
 * 
 * @return char*
*/
char *obtener_fichero_seleccionado(GtkWidget *dialog) {
    return gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GtkWidget *MAIN_WINDOW;

/**
 * @brief Initializes the main window.
 * 
 * @param window Reference to a pointer to GtkWidget. The pointer to the created window will be returned by reference in this variable.
 * 
 * @return GtkWidget* Main box that will contain the rest of the widgets.
*/
GtkWidget *init_window(GtkWidget **window) {
    // Caja que contendrá todos los widgets
    GtkWidget *main_vbox;

    // Crear y configurar la ventana
    MAIN_WINDOW = create_window();
    establecer_nombre_ventana(MAIN_WINDOW, "Sin Título - Wizard");
    establecer_tamano_por_defecto_ventana(MAIN_WINDOW, 900, 500);
    establecer_redimensionable_ventana(MAIN_WINDOW, TRUE);
    establecer_tamano_minimo_ventana(MAIN_WINDOW, 300, 200);
    configure_destroy_signal(MAIN_WINDOW);
    configure_delete_event_signal(MAIN_WINDOW);

    // Crear un contenedor de caja vertical para el menu_bar y lo demás
    main_vbox = crear_box(GTK_ORIENTATION_VERTICAL, 0);

    // Agregar el contenedor principal a la ventana
    agregar_widget_ventana(MAIN_WINDOW, main_vbox);

    // Returns by reference the main window
    *window = MAIN_WINDOW;

    return main_vbox;
}

/**
 * Muestra la ventana.
 * 
 * @param window Ventana a mostrar.
 * 
 * @return void
*/
void show_window(GtkWidget *window) {
    // Muestro todos los widgets de la ventana
    gtk_widget_show_all(window);

    // Oculto los windgets que deben estar ocultos al inicio
    hide_progress_bar();
}

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
    GtkWidget *window = GTK_WIDGET(user_data);
    gboolean abort_closing = on_delete_event(window, NULL, NULL);

    if (!abort_closing) {
        gtk_widget_destroy(window);
    }
}

/**
 * Muestra una ventana emergente con la información del ancho y alto de la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_info_ventana() {
    gint width, height;
    gtk_window_get_size(GTK_WINDOW(MAIN_WINDOW), &width, &height);

    char mensaje[100]; // Ajusta el tamaño según sea necesario
    sprintf(mensaje,    "Anchura: %dpx\n"
                        "Altura: %dpx",
                        width, height);
    
    const char* titulo = "Información de la ventana";
    
    mostrar_dialogo_mensaje(MAIN_WINDOW, mensaje, titulo);
}

/**
 * Muestra una ventana de selector de archivos y devuelve la ruta del archivo seleccionado.
 * 
 * @return char*
*/
char *mostrar_ventana_selector_archivos() {
    // Seleccionar un fichero desde el sistema de archivos
    GtkWidget *dialog = crear_dialogo_selector_archivos(MAIN_WINDOW);

    // Mostrar el diálogo
    gint res = mostrar_dialogo(dialog);

    // Si el usuario ha seleccionado un archivo
    if (res == GTK_RESPONSE_ACCEPT) {
        // Obtener la ruta del archivo
        char *filename = obtener_fichero_seleccionado(dialog);

        // Cerrar el diálogo
        gtk_widget_destroy(dialog);

        return filename;
    }

    // Cerrar el diálogo
    gtk_widget_destroy(dialog);

    return NULL;
}

/**
 * @brief Sets the title of the window as unsaved.
 * 
 * - Add a bullet and a space (• ) at the beginning of the title.
 * 
 * @return void
 */
void set_title_unsaved() {
    // Get the title of the window
    const char *title = gtk_window_get_title(GTK_WINDOW(MAIN_WINDOW));

    // Add a bullet and a space (• ) at the beginning of the title
    sds new_title = sdsnew("• ");
    new_title = sdscat(new_title, title);

    // Set the new title
    gtk_window_set_title(GTK_WINDOW(MAIN_WINDOW), new_title);

    // Free the memory
    sdsfree(new_title);
}

/**
 * @brief Sets the title of the window as saved.
 * 
 * - Remove the bullet and the space (• ) at the beginning of the title.
 * 
 * @return void
 */
void set_title_saved() {
    // Get the title of the window
    const char *title = gtk_window_get_title(GTK_WINDOW(MAIN_WINDOW));

    // Remove the bullet and the space (• ) at the beginning of the title
    sds new_title = sdsnew(title + 4);

    // Set the new title
    gtk_window_set_title(GTK_WINDOW(MAIN_WINDOW), new_title);

    // Free the memory
    sdsfree(new_title);
}

/**
 * @brief Creates a new window with an empty tree proyect (no file is associated).
 * 
 * @return void
 */
void create_new_window() {
    printf("Creating new window...\n");
}