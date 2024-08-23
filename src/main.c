#include <gtk/gtk.h>
#include <stdint.h>

// REMINDER: reasons to make an auxiliary file:
// - Working with a file
// - Managing a type of file
// - Making a wrapper of a library (only this file can access the library)

#include "window_manager.h"
#include "components_manager.h"
#include "background_keyboard_imput_wrapper.h"
#include "history.h"

int main(int argc, char *argv[]) {
    // Initialization of personal libraries
    u_int8_t (*init_functions[])() = {
        init_background_keyboard_imput_wrapper,
        init_history
    };
    for (u_int8_t i = 0; i < sizeof(init_functions) / sizeof(init_functions[0]); i++) {
        if (init_functions[i]()) {
            return 1;
        }
    }

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Initialize the components of the main window
    inicializar_componentes_ventana_principal();

    // Show the main window
    mostrar_ventana_principal();

    // Start the main GTK event loop
    gtk_main();

    // Close the personal libraries
    u_int8_t (*close_functions[])() = {
        close_background_keyboard_imput_wrapper,
        close_history
    };
    for (u_int8_t i = 0; i < sizeof(close_functions) / sizeof(close_functions[0]); i++) {
        close_functions[i]();
    }

    return 0;
}