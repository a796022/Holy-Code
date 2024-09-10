#pragma once

#include <gtk/gtk.h>
#include <stdio.h>

#include "window_structure.h"

// Storage for the state of the history
struct History {
    // State of the set
    uint8_t set_state;
    int64_t last_saved_distance;

    // Stacks for undo and redo operations
    GQueue *undo_stack;
    GQueue *redo_stack;
};

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
struct History* new_history();

/**
 * @brief closes the history.
 * 
 * @param history History to close
 * 
 * @return void
 */
void close_history(struct History *history);

/**
 * @brief Sets the history as saved.
 * 
 * @param history History to set as saved
 * 
 * @return void
 */
void set_history_as_saved(struct History *history);

/**
 * @brief Returns 0 if there are unsaved changes, 1 otherwise.
 * 
 * @param history History to check if there are unsaved changes
 * 
 * @return uint8_t 0 if there are unsaved changes, 1 otherwise
 */
uint8_t there_are_unsaved_changes(struct History *history);

/**
 * @brief Initializes the operations set.
 * 
 * @param history History with the operations set to initialize
 * 
 * @return void
 */
void init_operations_set(struct History *history);

/**
 * @brief Ends the operations set.
 * 
 * - Modify the last operation to mark the end of the set.
 * 
 * @param history History with the operations set to end
 * 
 * @return void
 */
void end_operations_set(struct History *history);

/**
 * @brief Undo the last operation.
 * 
 * @param menuitem Menu item that triggered the signal (the item associated with the Ctrl+Z shortcut)
 * @param user_data Data passed to the signal, in this case the window structure where the operation will be undone
 * 
 * @return void
 */
void undo(GtkMenuItem *menuitem, gpointer user_data);

/**
 * @brief Redo the last operation.
 * 
 * @param menuitem Menu item that triggered the signal (the item associated with the Ctrl+Y shortcut)
 * @param user_data Data passed to the signal, in this case the window structure where the operation will be redone
 * 
 * @return void
 */
void redo(GtkMenuItem *menuitem, gpointer user_data);

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
void store_operation(struct WindowStructure* window_structure, uint8_t id, void* data);