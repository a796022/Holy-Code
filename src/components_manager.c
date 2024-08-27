#include <gtk/gtk.h>

#include "components_manager.h"
#include "window_manager.h"
#include "box.h"
#include "gtk_menu_bar_wrapper.h"
#include "tree_wrapper.h"
#include "GtkAccelGroup_wrapper.h"
#include "paned_manager.h"
#include "gtk_progress_bar.h"
#include "gtk_scrolled_window_wrapper.h"

/**
 * @brief Initializes the main window components.
 * 
 * @return void
*/
void inicializar_componentes_ventana_principal() {
    // Caja que contendrá la barra de menú y el resto de widgets
    GtkWidget *main_vbox;

    // Menú superior
    GtkWidget *menu_bar;

    // Divisor vertical
    GtkWidget *paned;

    // Árbol treeview
    GtkWidget *tree_view;

    // Scrolleable container for the treeview
    GtkWidget *scrolled_window;

    // Crear y configurar la ventana
    main_vbox = inicializar_ventana_principal();

    // Crear el menu_bar
    menu_bar = initialize_menu_bar_main_window();
    agregar_widget_box(main_vbox, menu_bar, FALSE, FALSE, 0);

    // Crear el GtkPaned (divisor)
    paned = crear_paned_horizontal();
    agregar_widget_box(main_vbox, paned, TRUE, TRUE, 0);

    // Include the progress bar
    init_progress_bar();
    agregar_widget_box(main_vbox, MAIN_PROGRESS_BAR, FALSE, FALSE, 0);

    // // Crear contenido para el área izquierda del divisor (el treeview)
    // tree_view = init_main_tree();
    // agregar_widget_paned_izquierda(paned, tree_view, TRUE, FALSE);

    // Create the content for the left side of the divider (the scrolled window)
    scrolled_window = init_scrolled_window();
    agregar_widget_paned_izquierda(paned, scrolled_window, TRUE, FALSE);

    // Create the treeview
    tree_view = init_main_tree();
    add_widget_to_scrolled_window(scrolled_window, tree_view);

    // Crear contenido para el área derecha del divisor
    GtkWidget *right_label_panel = gtk_label_new("Contenido derecho");
    agregar_widget_paned_derecha(paned, right_label_panel, TRUE, FALSE);

    // Inicializar los atajos de teclado
    initialize_keyboard_shortcuts();
}