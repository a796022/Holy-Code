#include <gtk/gtk.h>

#include "operations.h"

/**
 * @brief Creates a new operation.
 * 
 * @param id Identifier of the operation
 * @param set Set of the operation
 * @param data Data of the operation
 * 
 * @return struct Operation The new operation
 */
struct Operation* new_operation(uint8_t id, uint8_t set, void *data) {
    struct Operation *operation = g_new(struct Operation, 1);

    // id
    operation->id = id;

    // set
    operation->set = set;

    // data
    operation->data = data;

    return operation;
}

/**
 * @brief Free the memory of an aggregate operation.
 * 
 * @param aggregate_operation Aggregate operation to free
 * 
 * @return void
 */
static void free_aggregate_operation(struct AggregateOperation *aggregate_operation) {
    // g_free(aggregate_operation->node_text);
    // g_free(aggregate_operation->node_path);
    g_free(aggregate_operation);
}

/**
 * @brief Free the memory of a delete operation.
 * 
 * @param delete_operation Delete operation to free
 * 
 * @return void
 */
static void free_delete_operation(struct DeleteOperation *delete_operation) {
    // g_free(delete_operation->node_text);
    // g_free(delete_operation->node_path);
    g_free(delete_operation);
}

/**
 * @brief Frees the memory of an operation.
 * 
 * @param operation Operation to free
 * 
 * @return void
 */
void free_operation(struct Operation *operation) {
    // Free the data of the operation
    switch (operation->id) {
        case AGGREGATE_OP:
            free_aggregate_operation(operation->data);
            break;
        case DELETE_OP:
            free_delete_operation(operation->data);
            break;
        default:
            perror("Error: Unknown operation\n");
            break;
    }

    // Free the data
    g_free(operation);
}

/**
 * @brief Frees the memory of an operation.
 * 
 * @param data Operation to free
 * 
 * @return void
 */
void free_operation_wrapper(gpointer operation, gpointer data) {
    free_operation((struct Operation *)operation);
}