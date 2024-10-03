#include <gtk/gtk.h>

#include "tree_files.h"
#include "tree_manager.h"
// #include "tree_wrapper.h"
// #include "gtk_progress_bar.h"
// #include "window_structure.h"

/**
 * @brief Remove all line breaks from the string. Then, remove leading tabs and
 * leading spaces.
 * 
 * @param line String to be cleaned
 * 
 * @return void
 */
static void clean_string(char *line) {
    // Remove all line breaks
    char *src = line, *dst = line;
    while (*src) {
        if (*src != '\n' && *src != '\r') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';  // Null-terminate the cleaned string

    // Remove leading tabs and leading spaces
    src = line;
    while (*src == ' ' || *src == '\t') {
        src++;
    }

    // If src moved, shift the string to the left
    if (src != line) {
        memmove(line, src, strlen(src) + 1);
    }
}

/**
 * @brief Get the maximum number of characters and the maximum number of tabulations
 * in a file.
 * 
 * @param filename File name
 * @param max_line_length Maximum number of characters
 * @param max_tabs Maximum number of tabulations
 * 
 * @return void
 */
static void get_max_char_tab(const char *filename, int *max_line_length, int *max_tabs) {
    // If the file does not exist, return
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    int current_line_length = 0;
    char c;
    int new_line = 1;
    int tabulation_streak = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            // To get the maximum number of characters
            if (current_line_length > *max_line_length) {
                *max_line_length = current_line_length;
            }
            current_line_length = 0;

            // To get the maximum number of tabulations
            if (tabulation_streak > *max_tabs) {
                *max_tabs = tabulation_streak;
            }
            tabulation_streak = 0;
            new_line = 1;
        } else {
            // To get the maximum number of characters
            current_line_length++;

            // To get the maximum number of tabulations
            if (new_line) {
                if (c == ' ') {
                    tabulation_streak++;
                } else if (c == '\t') {
                    tabulation_streak += 4;
                } else {
                    if (tabulation_streak > *max_tabs) {
                        *max_tabs = tabulation_streak;
                    }
                    tabulation_streak = 0;
                    new_line = 0;
                }
            }
        }
    }

    if (current_line_length > *max_line_length) {
        *max_line_length = current_line_length;
    }
    if (tabulation_streak > *max_tabs) {
        *max_tabs = tabulation_streak;
    }

    *max_line_length += 1;
    *max_tabs /= 4;

    fclose(file);
}

/**
 * @brief Get the number of tabs at the beginning of a string.
 * 
 * @param str String
 * 
 * @return int Number of tabs
 */
static int get_num_tabs(const char *str) {
    int num_tabs = 0;
    for (int i = 0; str[i] == ' ' || str[i] == '\t'; i++) {
        if (str[i] == '\t') {
            num_tabs += 4;
        } else {
            num_tabs++;
        }
    }
    return num_tabs / 4;
}

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
void read_tree_file(GtkWidget* tree_view, char *filename) {
    // If the file does not exist, return
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    // Get the model from the tree view
    GtkTreeStore *tree_store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view)));

    // Clear the model
    gtk_tree_store_clear(tree_store);

    /* Make a first reading of the tree to obtain the maximum line size and the
    maximum number of tabs */
    int max_line_length = 0;
    int max_tabs = 0;
    get_max_char_tab(filename, &max_line_length, &max_tabs);

    // Array of parent nodes
    GtkTreeIter parents[max_tabs + 1];

    // Tree building
    char line[max_line_length + 1];
    int last_node_level = -1;
    while (fgets(line, max_line_length + 1, file) != NULL) {
        // Get the number of tabs at the beginning of the line
        int current_node_level = get_num_tabs(line);

        // Remove from the string the unnecesary characters
        clean_string(line);

        // Add the node to the tree
        if (current_node_level == 0) {
            if (last_node_level == -1) {
                parents[0] = add_node(tree_view, tree_store, NULL, line);
                last_node_level = 0;
            } else {
                return;
            }
        } else {
            if (current_node_level > last_node_level + 1) {
                for (int i = last_node_level + 1; i < current_node_level; i++) {
                    if (i == 0) {
                        parents[i] = add_node(tree_view, tree_store, NULL, "[NULL]");
                    } else {
                        parents[i] = add_node(tree_view, tree_store, &parents[i - 1], "[NULL]");
                    }
                }
            }

            parents[current_node_level] = add_node(tree_view, tree_store, &parents[current_node_level - 1], line);
            last_node_level = current_node_level;
        }
    }

    fclose(file);
}

/**
 * @brief write the current node, then call the child, then call the next sibling
 * 
 * @param model Tree data model
 * @param iter Current node
 * @param file File to write
 * @param level Level of the node
 * @param num_nodes Number of nodes
 * @param added_nodes Number of added nodes
 * 
 * @return void
 */
void write_tree_file_recursive(GtkTreeStore *model, GtkTreeIter *iter, FILE *file, int level, int num_nodes, int *added_nodes, GtkWidget* progress_bar) {
    // Write the node to the file
    gchar *text;
    gtk_tree_model_get(GTK_TREE_MODEL(model), iter, 0, &text, -1);
    for (int i = 0; i < level; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "%s\n", text);
    g_free(text);

    // Mark progress
    (*added_nodes)++;
    gdouble progress = (gdouble)(*added_nodes) / (gdouble)num_nodes;
    set_progress_bar_value(progress_bar, progress);

    // Call the child
    GtkTreeIter child;
    if (gtk_tree_model_iter_children(GTK_TREE_MODEL(model), &child, iter)) {
        write_tree_file_recursive(model, &child, file, level + 1, num_nodes, added_nodes, progress_bar);
    }

    // Call the next sibling
    GtkTreeIter sibling = *iter;
    if (gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &sibling)) {
        write_tree_file_recursive(model, &sibling, file, level, num_nodes, added_nodes, progress_bar);
    }
}

/**
 * @brief Write a tree to a file.
 * 
 * @param model Tree data model
 * @param filename File name
 * @param num_nodes Number of nodes
 * @param added_nodes Number of added nodes
 * 
 * @return int status
 */
int write_tree_file(struct WindowStructure* window_structure, const char *filename, int num_nodes) {
    GtkTreeStore* model = window_structure->tree_model;
    GtkWidget* progress_bar = window_structure->progress_bar;

    // Open the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    // Show the progress bar
    show_progress_bar(progress_bar);

    // Write the tree to the file
    GtkTreeIter iter;
    int added_nodes = 0;
    if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &iter)) {
        write_tree_file_recursive(model, &iter, file, 0, num_nodes, &added_nodes, progress_bar);
    }

    // Hide the progress bar
    hide_progress_bar(progress_bar);

    // Close the file
    fclose(file);

    return 0;
}