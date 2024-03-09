#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeIter iter;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear una nueva ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Wizard");
    
    // Establecer la ventana y sus propiedades
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_widget_set_size_request(window, 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /**
     * Esta función crea un nuevo modelo de lista con una columna y especifica
     * el tipo de datos que contendrá esa columna. En este caso, el modelo de
     * lista tiene una sola columna que contendrá cadenas de texto
     * (G_TYPE_STRING). La función devuelve un puntero al nuevo modelo de lista
     * creado.
     */
    store = gtk_list_store_new(1, G_TYPE_STRING);

    // Crear el TreeView
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);

    // Crear una columna para el TreeView
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
        "Elemento", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    // Agregar algunos elementos de muestra al modelo de lista
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "Elemento 1", -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "Elemento 2", -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "Elemento 3", -1);

    // Agregar el TreeView a la ventana
    gtk_container_add(GTK_CONTAINER(window), tree_view);

    // Mostrar la ventana
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}
