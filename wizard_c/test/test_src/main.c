#include <gtk/gtk.h>

#include "../../src/GList_manager.h"
#include "../../src/global_structure.h"
#include "../../src/window_structure.h"

// GLIST MANAGER ///////////////////////////////////////////////////////////////

void test_GList_manager_add_close_new_window_structure();

void test_GList_manager() {
    printf("Testing GList_manager module...\n");

    test_GList_manager_add_close_new_window_structure();
}

void test_GList_manager_add_close_new_window_structure() {
    printf("\tTest: test_GList_manager_add_close_new_window_structure: ");

    GList* window_structures = NULL;
    GList_add_new_window_structure(&window_structures);

    if (g_list_length(window_structures) != 1) {
        printf("\033[0;31mFAIL\033[0m\n");
        printf("\t\033[0;31mThe length of the list is not 1\033[0m\n");
        return;
    }

    GList_close_window_structures(&window_structures);

    if (window_structures != NULL) {
        printf("\033[0;31mFAIL\033[0m\n");
        printf("\t\033[0;31mThe list is not NULL\033[0m\n");
        return;
    }

    printf("\033[0;32mOK\033[0m\n");
}

// GLOBAL STRUCTURE ////////////////////////////////////////////////////////////

void test_global_structure_new_close();

void test_global_structure() {
    printf("Testing global_structure module...\n");

    test_global_structure_new_close();
}

void test_global_structure_new_close() {
    printf("\tTest: test_global_structure_new_close: ");

    struct GlobalStructure* global_structure;
    new_global_structure(&global_structure);
    close_global_structure(global_structure);

    printf("\033[0;32mOK\033[0m\n");
}

// WINDOW STRUCTURE ////////////////////////////////////////////////////////////

void test_window_structure_new_close();

void test_window_structure() {
    printf("Testing window_structure module...\n");

    test_window_structure_new_close();
}

void test_window_structure_new_close() {
    printf("\tTest: test_window_structure_new_close: ");

    struct WindowStructure* window_structure;
    new_window_structure(&window_structure);
    close_window_structure(window_structure);

    printf("\033[0;32mOK\033[0m\n");
}

// MAIN ////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Run the tests
    test_GList_manager();
    test_global_structure();
    test_window_structure();

    return 0;
}