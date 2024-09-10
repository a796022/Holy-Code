#include <gtk/gtk.h>

#include "global_structure.h"
#include "history.h"

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Initialize the components of the main window
    struct GlobalStructure* global_structure = new_global_structure();
    init_global_structure(global_structure);

    // Start the main GTK event loop
    gtk_main();

    // Close the global structure
    close_global_structure(global_structure);

    return 0;
}