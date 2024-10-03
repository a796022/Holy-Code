#pragma once

#include <gtk/gtk.h>
#include <stdint.h>

#define AGGREGATE_OP 0
#define DELETE_OP 1

// Storage for generic operations
struct Operation {
    uint8_t id;
    uint8_t set;
    void *data;
};

// Data of the aggregate operation
struct AggregateOperation {
    char *node_text;
    gchar *node_path;
};

// Data of the delete operation
struct DeleteOperation {
    char *node_text;
    gchar *node_path;
};

/**
 * @brief Creates a new operation.
 * 
 * @param id Identifier of the operation
 * @param set Set of the operation
 * @param data Data of the operation
 * 
 * @return struct Operation The new operation
 */
struct Operation* new_operation(uint8_t id, uint8_t set, void *data);

/**
 * @brief Frees the memory of an operation.
 * 
 * @param operation Operation to free
 * 
 * @return void
 */
void free_operation(struct Operation *operation);

/**
 * @brief Frees the memory of an operation.
 * 
 * @param data Operation to free
 * 
 * @return void
 */
void free_operation_wrapper(gpointer operation, gpointer data);