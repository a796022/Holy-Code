#include <gtk/gtk.h>

#include "window.c"

int main(int argc, char *argv[]) {
    // Ventana principal
    GtkWidget *window;

    GtkWidget *tree_view;
    GtkListStore *store;
    GtkTreeIter iter;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear y configurar la ventana
    window = crear_ventana();
    establecer_nombre_ventana(window, "Wizard");
    establecer_tamano_por_defecto_ventana(window, 300, 200);
    establecer_redimensionable_ventana(window, TRUE);
    establecer_tamano_minimo_ventana(window, 300, 200);
    establecer_terminar_programa_cerrado_ventana(window);
    
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
    agregar_widget_ventana(window, tree_view);

    // Mostrar la ventana
    mostrar_ventana(window);

    // Iniciar el bucle principal de eventos de GTK
    gtk_main();

    return 0;
}
