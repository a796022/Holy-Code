#pragma once

#include <gtk/gtk.h>

// #include "bg_key_input.h"
// #include "window_structure.h"

struct GlobalStructure {
    // List of window structures, one for each opened window
    GList* window_structures;

    // // Data needed to manage the background keyboard imput
    // struct BgKeyInput* bg_key_input;
};

/**
 * @brief Creates a GlobalStructure. The list of WindowStructure*'s is
 * initialized with one WindowStructure* (the first window that is opened when
 * running the program).
 * 
 * @param global_structure Pointer to the GlobalStructure* to initialize.
 * 
 * @return void
 */
void new_global_structure(struct GlobalStructure** global_structure);

// /**
//  * @brief Initializes a global structure.
//  * 
//  * @param global_structure The global structure to initialize
//  * 
//  * @return void
//  */
// void init_global_structure(struct GlobalStructure* global_structure);

/**
 * @brief Closes a GlobalStructure*.
 * 
 * @param global_structure The GlobalStructure* to close.
 * 
 * @return void
 */
void close_global_structure(struct GlobalStructure* global_structure);