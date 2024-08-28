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
    // Box that will contain the menu bar and the rest of the widgets
    GtkWidget *main_vbox;

    // Top menu
    GtkWidget *menu_bar;

    // Vertical divider
    GtkWidget *paned;

    // Tree
    GtkWidget *tree_view;

    // Scrolleable container for the treeview
    GtkWidget *scrolled_window;

    // Window
    GtkWidget *window;

    // Create and configure the window
    main_vbox = init_window(&window);

    // Create the menu_bar
    menu_bar = init_menu_bar(window);
    agregar_widget_box(main_vbox, menu_bar, FALSE, FALSE, 0);

    // Create the GtkPaned (divider)
    paned = crear_paned_horizontal();
    agregar_widget_box(main_vbox, paned, TRUE, TRUE, 0);

    // Include the progress bar
    init_progress_bar();
    agregar_widget_box(main_vbox, MAIN_PROGRESS_BAR, FALSE, FALSE, 0);

    // Create the content for the left side of the divider (the scrolled window)
    scrolled_window = init_scrolled_window();
    agregar_widget_paned_izquierda(paned, scrolled_window, TRUE, FALSE);

    // Create the treeview
    tree_view = init_main_tree();
    add_widget_to_scrolled_window(scrolled_window, tree_view);

    // Create content for the right area of the divider
    GtkWidget *right_label_panel = gtk_label_new("Contenido derecho");
    agregar_widget_paned_derecha(paned, right_label_panel, TRUE, FALSE);

    // Initialize the keyboard shortcuts
    init_keyboard_shortcuts(window);

    // Show the window
    show_window(window);
}