#include <gtk/gtk.h>

#include "global_structure.h"

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the global structure
    struct GlobalStructure* global_structure = new_global_structure();

    // Start the main GTK event loop
    gtk_main();

    // Close the global structure
    close_global_structure(global_structure);

    return 0;
}