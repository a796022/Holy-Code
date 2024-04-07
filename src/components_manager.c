#include <gtk/gtk.h>

#include "components_manager.h"
#include "window_manager.h"
#include "box.h"
#include "menu_bar_manager.h"
#include "tree_manager.h"
#include "atajos_teclado_manager.h"

/**
 * Inicializa los componentes de la ventana principal.
 * 
 * @return void
*/
void inicializar_componentes_ventana_principal() {
    // Caja que contendrá la barra de menú y el resto de widgets
    GtkWidget *main_vbox;

    // Menú superior
    GtkWidget *menu_bar;

    // Widget del TreeView
    GtkWidget *tree_view;

    // Crear y configurar la ventana
    main_vbox = inicializar_ventana_principal();

    // Crear el menu_bar
    menu_bar = inicializar_menu_bar_ventana_principal();
    agregar_widget_box(main_vbox, menu_bar, FALSE, FALSE, 0);

    // Crear el árbol principal
    tree_view = inicializar_arbol_principal();
    agregar_widget_box(main_vbox, tree_view, TRUE, TRUE, 0);

    // Inicializar los atajos de teclado
    inicializar_atajos_teclado();
}