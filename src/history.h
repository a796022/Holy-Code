#pragma once

/**
 * @brief Resets the last saved distance to 0 and modifies the title of the window to indicate that there are no unsaved changes.
 * 
 * - This function is called when the file is saved, so the last saved distance is set to 0.
 * 
 * @return void
 */
void set_changes_as_saved(GtkWidget *window);

/**
 * @brief Returns 0 if there are unsaved changes, 1 otherwise.
 * 
 * @return uint8_t 0 if there are unsaved changes, 1 otherwise
 */
uint8_t there_are_unsaved_changes();

/**
 * @brief Initializes the operations set.
 * 
 * @return void
 */
void init_operations_set();

/**
 * @brief Ends the operations set.
 * 
 * - Modify the last operation to mark the end of the set.
 * 
 * @return void
 */
void end_operations_set();

/**
 * @brief Undo the last operation.
 * 
 * - The last operation is undone.
 * - The operation is added to the redo stack.
 * 
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal, in this case the window where the operation will be undone.
 * 
 * @return void
 */
void undo(GtkMenuItem *menuitem, gpointer user_data);

/**
 * @brief Redo the last operation.
 * 
 * - The last operation is redone.
 * - The operation is added to the undo stack.
 * 
 * @param menuitem Menu item that triggered the signal.
 * @param user_data Data passed to the signal, in this case the window where the operation will be redone.
 * 
 * @return void
 */
void redo(GtkMenuItem *menuitem, gpointer user_data);

/**
 * @brief Initializes the history.
 * 
 * - Initializes the undo and redo stacks of all operations.
 * 
 * @return uint8_t 0 if the initialization was successful, 1 otherwise
 */
uint8_t init_history();

/**
 * @brief Closes the history.
 * 
 * - Frees the memory of the undo and redo stacks of all operations.
 * 
 * @return uint8_t 0 if the closing was successful, 1 otherwise
 */
uint8_t close_history();

/**
 * @brief Stores an aggregate operation.
 * 
 * - The operation is stored in the undo stack.
 * - The redo stack is cleared.
 * 
 * @param window Window with the tree to which the text will be added.
 * @param node_text Text of the node
 * @param path_str Path of the added node
 * 
 * @return void
 */
void store_aggregate_operation(struct WindowStructure* window_structure, char *node_text, gchar *path_str);

/**
 * @brief Stores a delete operation.
 * 
 * - The operation is stored in the undo stack.
 * - The redo stack is cleared.
 * 
 * @param window Window with the tree to which the node belongs
 * @param node_text Text of the node
 * @param path_str Path of the deleted node
 * 
 * @return void
 */
void store_delete_operation(GtkWidget *window, char *node_text, gchar *path_str);