/**
 * @file history.c
 * 
 * @brief History of operations.
 * 
 * - The history of operations is stored in stacks.
 * - The stacks are used to undo and redo operations.
 * - The operations are stored in the undo stack.
 * - The redo stack is used to redo operations.
 * 
 * To add a new operation, follow the steps listed throughout the code with the ### mark.
 */

#include <gtk/gtk.h>
#include <stdio.h>

#include "history.h"
#include "operations.h" // ### Define de struct for the new operation and the operation identifier
#include "tree_wrapper.h"
#include "window_manager.h"
#include "window_structure.h"

#define SINGLE_OP 0
#define SET_EXTREME_OP 1
#define SET_INNER_OP 2

#define NO_SET 0
#define BEGGINING_SET 1
#define IN_SET 2

#define REASON_UNDO 0
#define REASON_REDO 1
#define REASON_ACTION 2

/**
 * @brief Creates a new empty history
 * 
 * @return struct History The new empty history
 */
struct History* new_history() {
    struct History *history = g_new(struct History, 1);

    // set_state
    history->set_state = NO_SET;

    // last_saved_distance
    history->last_saved_distance = 0;

    // undo_stack: initialize with an empty g_queue
    history->undo_stack = g_queue_new();

    // redo_stack: initialize with an empty g_queue
    history->redo_stack = g_queue_new();

    return history;
}

/**
 * @brief closes the history.
 * 
 * @param history History to close
 * 
 * @return void
 */
void close_history(struct History *history) {
    g_queue_free(history->undo_stack);
    g_queue_free(history->redo_stack);
    g_free(history);
}

/**
 * @brief Modifies the last saved distance and modifies the title of the window if necessary to indicate if there are unsaved changes.
 * 
 * @param history History that contains the window to which the history is associated
 * @param distance Distance to modify the last saved distance
 * 
 * @return void
 */
static void modify_last_saved_distance(struct WindowStructure* window_structure, int distance) {
    // Get the data
    struct History *history = window_structure->history;
    GtkWidget *window = window_structure->window;

    if (history->last_saved_distance == 0) {
        set_title_unsaved(window);
    }

    history->last_saved_distance += distance;

    if (history->last_saved_distance == 0) {
        set_title_as_saved(window);
    }
}

/**
 * @brief Sets the history as saved.
 * 
 * @param history History to set as saved
 * 
 * @return void
 */
void set_history_as_saved(struct History *history) {
    history->last_saved_distance = 0;
}

/**
 * @brief Returns 0 if there are unsaved changes, 1 otherwise.
 * 
 * @param history History to check if there are unsaved changes
 * 
 * @return uint8_t 0 if there are unsaved changes, 1 otherwise
 */
uint8_t there_are_unsaved_changes(struct History *history) {
    return history->last_saved_distance != 0;
}

/**
 * @brief Initializes the operations set.
 * 
 * @param history History with the operations set to initialize
 * 
 * @return void
 */
void init_operations_set(struct History *history) {
    history->set_state = BEGGINING_SET;
}

/**
 * @brief Ends the operations set.
 * 
 * - Modify the last operation to mark the end of the set.
 * 
 * @param history History with the operations set to end
 * 
 * @return void
 */
void end_operations_set(struct History *history) {
    // Get the las operation
    struct Operation *operation = g_queue_peek_head(history->undo_stack);
    if (operation == NULL) {
        return;
    }

    // Mark the end of the set in the last operation
    if (operation->set == SET_EXTREME_OP) {
        operation->set = SINGLE_OP;
    } else if (operation->set == SET_INNER_OP) {
        operation->set = SET_EXTREME_OP;
    }

    // Mark the end of the set in the global state
    history->set_state = NO_SET;
}

/**
 * @brief Undoes the last aggregate operation.
 * 
 * - The operation is removed from the undo stack.
 * - The operation is added to the redo stack.
 * - The operation is undone.
 * 
 * @return void
 */
static void undo_aggregate_operation(struct WindowStructure* window_structure, void* data) {
    // Get the data
    struct AggregateOperation *operation = (struct AggregateOperation *)data;

    // Undo the operation
    GtkTreeIter child_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(window_structure->tree_model), 
                                        &child_iter, 
                                        operation->node_path);
    gtk_tree_store_remove(window_structure->tree_model, &child_iter);
}

/**
 * @brief Redoes the last aggregate operation.
 * 
 * - The operation is removed from the redo stack.
 * - The operation is added to the undo stack.
 * - The operation is redone.
 * 
 * @return void
 */
static void redo_aggregate_operation(struct WindowStructure* window_structure, void* data) {
    // Get the data
    struct AggregateOperation *operation = (struct AggregateOperation *)data;

    // Redo the operation
    // 1- Get the path of the node
    GtkTreePath *parent_path = gtk_tree_path_new_from_string(operation->node_path);
    gtk_tree_path_up(parent_path);
    gchar *parent_path_str = gtk_tree_path_to_string(parent_path);
    gtk_tree_path_free(parent_path);

    // 2- Get the parent node
    GtkTreeIter parent_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(window_structure->tree_model), 
                                        &parent_iter, 
                                        parent_path_str);

    // 3- Add the node to the parent node
    add_node(window_structure->tree_view, window_structure->tree_model, &parent_iter, operation->node_text);
}

/**
 * @brief Undoes the last delete operation.
 * 
 * - The operation is removed from the undo stack.
 * - The operation is added to the redo stack.
 * - The operation is undone.
 * 
 * @return void
 */
static void undo_delete_operation(struct WindowStructure* window_structure, void* data) {
    // Get the data
    struct DeleteOperation *operation = (struct DeleteOperation *)data;

    // Undo the operation
    // 1- Get the position of the node
    GtkTreePath *parent_path = gtk_tree_path_new_from_string(operation->node_path);
    gint *position_list = gtk_tree_path_get_indices(parent_path);
    int length = gtk_tree_path_get_depth(parent_path);
    gint position = position_list[length - 1];

    // 2- Get the path of the parent node
    gtk_tree_path_up(parent_path);
    gchar *parent_path_str = gtk_tree_path_to_string(parent_path);
    gtk_tree_path_free(parent_path);

    // 3- Get the parent node
    GtkTreeIter parent_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(window_structure->tree_model), 
                                        &parent_iter, 
                                        parent_path_str);

    // 4- Add the node to the parent node
    insert_node_at_position(window_structure, &parent_iter, position, operation->node_text);
}

/**
 * @brief Redoes the last delete operation.
 * 
 * - The operation is removed from the redo stack.
 * - The operation is added to the undo stack.
 * - The operation is redone.
 * 
 * @return void
 */
static void redo_delete_operation(struct WindowStructure* window_structure, void* data) {
    // Get the data
    struct DeleteOperation *operation = (struct DeleteOperation *)data;

    // Redo the operation
    // 1- Get the iter of the node
    GtkTreeIter child_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(window_structure->tree_model), 
                                        &child_iter, 
                                        operation->node_path);
    
    // 2- Remove the node
    gtk_tree_store_remove(window_structure->tree_model, &child_iter);
}

/**
 * @brief Undo the last operation.
 * 
 * @param menuitem Menu item that triggered the signal (the item associated with the Ctrl+Z shortcut)
 * @param user_data Data passed to the signal, in this case the window structure where the operation will be undone
 * 
 * @return void
 */
void undo(GtkMenuItem *menuitem, gpointer user_data) {
    // Get the data
    struct WindowStructure* window_structure = (struct WindowStructure*)user_data;
    struct History *history = window_structure->history;

    // If the operation stack is empty, do nothing
    if (g_queue_is_empty(history->undo_stack)) {
        return;
    }

    // Get the last operation
    struct Operation *operation = g_queue_pop_head(history->undo_stack);
    switch (operation->id) {
        case AGGREGATE_OP:
            undo_aggregate_operation(window_structure, operation->data);
            break;
        case DELETE_OP:
            undo_delete_operation(window_structure, operation->data);
            break;
        default:
            perror("Error: Unknown operation\n");
            break;
    }

    // Modify the last saved distance
    modify_last_saved_distance(window_structure, -1);

    // Add the operation to the redo stack
    g_queue_push_head(history->redo_stack, operation);

    // If there is a set of operations, undo all of them
    uint8_t set = operation->set;
    if (set == SET_EXTREME_OP) {
        if (history->set_state == NO_SET) {
            history->set_state = IN_SET;
            undo(menuitem, user_data);
        } else { // IN_SET
            history->set_state = NO_SET;
        }
    } else if (set == SET_INNER_OP) {
        undo(menuitem, user_data);
    }
}

/**
 * @brief Redo the last operation.
 * 
 * @param menuitem Menu item that triggered the signal (the item associated with the Ctrl+Y shortcut)
 * @param user_data Data passed to the signal, in this case the window structure where the operation will be redone
 * 
 * @return void
 */
void redo(GtkMenuItem *menuitem, gpointer user_data) {
    // Get the data
    struct WindowStructure* window_structure = (struct WindowStructure*)user_data;
    struct History *history = window_structure->history;

    // If the operation stack is empty, do nothing
    if (g_queue_is_empty(history->redo_stack)) {
        return;
    }

    // Get the last operation
    struct Operation *operation = g_queue_pop_head(history->redo_stack);
    switch (operation->id) {
        case AGGREGATE_OP:
            redo_aggregate_operation(window_structure, operation->data);
            break;
        case DELETE_OP:
            redo_delete_operation(window_structure, operation->data);
            break;
        default:
            perror("Error: Unknown operation\n");
            break;
    }

    // Modify the last saved distance
    modify_last_saved_distance(window_structure, 1);

    // Add the operation to the undo stack
    g_queue_push_head(history->undo_stack, operation);

    // If there is a set of operations, redo all of them
    uint8_t set = operation->set;
    if (set == SET_EXTREME_OP) {
        if (history->set_state == NO_SET) {
            history->set_state = IN_SET;
            redo(menuitem, user_data);
        } else { // IN_SET
            history->set_state = NO_SET;
        }
    } else if (set == SET_INNER_OP) {
        redo(menuitem, user_data);
    }
}

/**
 * @brief Stores an operation in the history.
 * 
 * - The operation is stored in the undo stack.
 * - The redo stack is cleared.
 * 
 * @param window_structure Window structure with the history to store the operation
 * @param id Operation identifier
 * @param data Data of the operation
 * 
 * @return void
 */
void store_operation(struct WindowStructure* window_structure, uint8_t id, void* data) {
    // Get the data
    struct History *history = window_structure->history;

    // Get the set of the operation and update the set state
    uint8_t set_state = history->set_state;
    uint8_t set;
    if (set_state == BEGGINING_SET) {
        set = SET_EXTREME_OP;
        history->set_state = IN_SET;
    } else if (set_state == IN_SET) {
        set = SET_INNER_OP;
    } else { // NO_SET
        set = SINGLE_OP;
    }

    // Create the operation
    struct Operation *operation = new_operation(id, set, data);

    // Add the operation to the undo stack
    g_queue_push_head(history->undo_stack, operation);

    // Clear the redo stack
    g_queue_foreach(history->redo_stack, (GFunc)free_operation_wrapper, NULL);
    g_queue_clear(history->redo_stack);

    // Modify the last saved distance
    modify_last_saved_distance(window_structure, 1);
}