#ifndef HISTORY
#define HISTORY

/**
 * @brief Undo the last operation.
 * 
 * @return void
 */
void undo();

/**
 * @brief Redo the last operation.
 * 
 * @return void
 */
void redo();

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
 * 
 * @param node_text Text of the node
 * @param path_str Path of the added node
 * 
 * @return void
 */
void store_aggregate_operation(char *node_text, gchar *path_str);

/**
 * @brief Stores a delete operation.
 * 
 * - The operation is stored in the undo stack.
 * - The redo stack is cleared.
 * 
 * @param node_text Text of the node
 * @param path_str Path of the deleted node
 * 
 * @return void
 */
void store_delete_operation(char *node_text, gchar *path_str);

#endif /* HISTORY */