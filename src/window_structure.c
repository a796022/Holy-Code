#include "window_manager.h"
#include "window_structure.h"

/**
 * @brief Initializes the window structure.
 * 
 * @return struct WindowStructure The initialized window structure
 */
struct WindowStructure* init_window_structure() {
    // Reserve memory for the new window structure
    struct WindowStructure* window_structure = g_malloc(sizeof(struct WindowStructure));

    // Initialize the window structure
    window_structure->window = NULL;
    window_structure->tree_view = NULL;
    window_structure->tree_model = NULL;
    window_structure->main_box = NULL;

    // Add the window to the list of windows
    WINDOWS_LIST = g_list_append(WINDOWS_LIST, window_structure);

    return window_structure;
}