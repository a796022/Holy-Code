#include <gtk/gtk.h>

#include "window_manager.h"
#include "box.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const char *NOMBRE_VENTANA = "Wizard";
const int ANCHO_VENTANA = 900;
const int ALTO_VENTANA = 500;
const gboolean REDIMENSIONABLE = TRUE;
const int ANCHO_MINIMO_VENTANA = 300;
const int ALTO_MINIMO_VENTANA = 200;

/**
 * Obtiene el ancho de la ventana.
 * 
 * @param window Ventana de la que se obtendrá el ancho.
 * 
 * @return int
*/
int obtener_ancho_ventana(GtkWindow *window) {
    gint width, height;
    gtk_window_get_size(window, &width, &height);
    return width;
}

/**
 * Obtiene el alto de la ventana.
 * 
 * @param window Ventana de la que se obtendrá el alto.
 * 
 * @return int
*/
int obtener_alto_ventana(GtkWindow *window) {
    gint width, height;
    gtk_window_get_size(window, &width, &height);
    return height;
}

/**
 * Obtiene el ancho de la ventana principal.
 * 
 * @return int
*/
int obtener_ancho_ventana_principal() {
    return obtener_ancho_ventana(GTK_WINDOW(MAIN_WINDOW));
}

/**
 * Obtiene el alto de la ventana principal.
 * 
 * @return int
*/
int obtener_alto_ventana_principal() {
    return obtener_alto_ventana(GTK_WINDOW(MAIN_WINDOW));
}

/**
 * Crea y devuelve una ventana.
 * 
 * @return GtkWidget*
*/
GtkWidget *crear_ventana() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
 * Conecta la señal "destroy" de la ventana a la función gtk_main_quit() para que, cuando se cierre la ventana, también se termine el bucle principal de eventos de GTK (y por lo tanto, termine el programa).
 * 
 * @param window Ventana a la que se le establecerá la señal "destroy".
 * 
 * @return void
*/
void establecer_terminar_programa_cerrado_ventana(GtkWidget *window) {
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
 * Muestra la ventana.
 * 
 * @param window Ventana a mostrar.
 * 
 * @return void
*/
void mostrar_ventana(GtkWidget *window) {
    gtk_widget_show_all(window);
}

/**
 * Cierra la ventana.
 * 
 * @param window Ventana a cerrar.
 * 
 * @return void
*/
void cerrar_ventana(GtkWidget *window) {
    gtk_widget_destroy(window);
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
 * Inicializa la ventana principal.
 * 
 * @param box Caja principal que contendrá el resto de widgets.
 * 
 * @return void
*/
GtkWidget *inicializar_ventana_principal() {
    // Caja que contendrá todos los widgets
    GtkWidget *main_vbox;

    // Crear y configurar la ventana
    MAIN_WINDOW = crear_ventana();
    establecer_nombre_ventana(MAIN_WINDOW, "Wizard");
    establecer_tamano_por_defecto_ventana(MAIN_WINDOW, 900, 500);
    establecer_redimensionable_ventana(MAIN_WINDOW, TRUE);
    establecer_tamano_minimo_ventana(MAIN_WINDOW, 300, 200);
    establecer_terminar_programa_cerrado_ventana(MAIN_WINDOW);

    // Crear un contenedor de caja vertical para el menu_bar y lo demás
    main_vbox = crear_box(GTK_ORIENTATION_VERTICAL, 0);

    // Agregar el contenedor principal a la ventana
    agregar_widget_ventana(MAIN_WINDOW, main_vbox);

    return main_vbox;
}

/**
 * Muestra la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_principal() {
    mostrar_ventana(MAIN_WINDOW);
}

/**
 * Cierra la ventana principal.
 * 
 * @return void
*/
void cerrar_ventana_principal() {
    cerrar_ventana(MAIN_WINDOW);
}

/**
 * Muestra una ventana emergente con la información del ancho y alto de la ventana principal.
 * 
 * @return void
*/
void mostrar_ventana_info_ventana() {
    const int ancho = obtener_ancho_ventana_principal();
    const int alto = obtener_alto_ventana_principal();

    char mensaje[100]; // Ajusta el tamaño según sea necesario
    sprintf(mensaje,    "Anchura: %dpx\n"
                        "Altura: %dpx",
                        ancho, alto);
    
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