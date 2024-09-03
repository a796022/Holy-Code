#include <gtk/gtk.h>

#include "global_structure.h"
#include "history.h"

int main(int argc, char *argv[]) {
    // Initialization of personal libraries
    u_int8_t (*init_functions[])() = {
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
    struct GlobalStructure* global_structure = new_global_structure();
    init_global_structure(global_structure);

    // Start the main GTK event loop
    gtk_main();

    // Close the personal libraries
    u_int8_t (*close_functions[])() = {
        close_history
    };
    for (u_int8_t i = 0; i < sizeof(close_functions) / sizeof(close_functions[0]); i++) {
        close_functions[i]();
    }

    return 0;
}