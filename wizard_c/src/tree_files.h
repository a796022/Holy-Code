#pragma once

#include <gtk/gtk.h>

// #include "window_manager.h"

/**
 * @brief Load a tree from a file.
 * 
 * @param model Tree data model
 * @param filename File name
 * 
 * @return int status
 * 
 * status:
 * 0: success
 * 1: error in node hierarchy, two root nodes found.
 * 2: error in the node hierarchy, no parent node found
 * -1: error opening the file
 */
void read_tree_file(GtkWidget* tree_view, char* filename);

// /**
//  * @brief Write a tree to a file.
//  * 
//  * @param model Tree data model
//  * @param filename File name
//  * @param num_nodes Number of nodes
//  * 
//  * @return int status
//  */
// int write_tree_file(struct WindowStructure* window_structure, const char *filename, int num_nodes);