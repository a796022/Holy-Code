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
 * To add a new operation, follow the steps listed throughout the code with the #N# syntax.
 */

#include <gtk/gtk.h>
#include <stdio.h>

#include "tree_manager.h"
#include "tree.h"

// #1# Define the operation identifier

#define AGGREGATE_OP 0
#define DELETE_OP 1

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Structure for the operation stack nodes
typedef struct OperationStackNode {
    uint8_t ids[256];
    struct OperationStackNode *next;
} OperationStackNode;

// Top of the operation stack
typedef struct OperationStack {
    OperationStackNode *top;
    uint8_t index;
} OperationStack;

// Stacks for undo and redo operations
OperationStack UNDO_STACK_OPERATIONS;
OperationStack REDO_STACK_OPERATIONS;

/**
 * @brief Initializes an operation stack.
 * 
 * @param stack Operation stack
 * 
 * @return void
 */
void init_operation_stack(OperationStack *stack) {
    // Set the index to 0
    stack->index = 0;

    // Create the top node
    stack->top = (OperationStackNode *)malloc(sizeof(OperationStackNode));
    if (stack->top == NULL) {
        printf("Error: Memory allocation failed for creating operation stack\n");
        return;
    }

    // Set the next node to NULL
    stack->top->next = NULL;
}

/**
 * @brief Pushes an operation to the stack.
 * 
 * - The operation is added to the top of the stack.
 * 
 * @param stack Operation stack
 * @param id Operation identifier
 * 
 * @return void
 */
void push_operation_stack(OperationStack *stack, uint8_t id) {
    // Add the operation to the top node
    stack->top->ids[stack->index] = id;
    stack->index++;

    // If the top node is full, create a new node
    if (stack->index >= 256) {
        // Create a new node
        OperationStackNode *new_node = (OperationStackNode *)malloc(sizeof(OperationStackNode));
        if (new_node == NULL) {
            printf("Error: Memory allocation failed for operation stack node\n");
            return;
        }

        // Add the new node to the top of the stack
        new_node->next = stack->top;
        stack->top = new_node;
        stack->index = 0;
    }
}

/**
 * @brief Pops an operation from the stack.
 * 
 * - The operation is removed from the top of the stack.
 * 
 * @param stack Operation stack
 * 
 * @return uint8_t Operation identifier
 */
uint8_t pop_operation_stack(OperationStack *stack) {
    // Check if the stack is empty
    if (stack->index == 0 && stack->top->next == NULL) {
        return -1;
    }

    // Remove the top node
    if (stack->index > 0) {
        stack->index--;
        return stack->top->ids[stack->index];
    } else {
        OperationStackNode *top_node = stack->top;
        stack->top = top_node->next;
        uint8_t id = stack->top->ids[255];
        free(top_node);
        return id;
    }
}

/**
 * @brief Returns the top operation of the stack.
 * 
 * @param stack Operation stack
 * 
 * @return uint8_t Operation identifier
 */
uint8_t peek_operation_stack(OperationStack *stack) {
    // Check if the stack is empty
    if (stack->index == 0 && stack->top == NULL) {
        return -1;
    }

    if (stack->index > 0) {
        return stack->top->ids[stack->index - 1];
    } else {
        return stack->top->next->ids[255];
    }
}

/**
 * @brief Frees the memory of the operation stack.
 * 
 * @param stack Operation stack
 * 
 * @return void
 */
void free_operation_stack(OperationStack *stack) {
    while (!(stack->index == 0 && stack->top->next == NULL)) {
        pop_operation_stack(stack);
    }
}

// #2# Create the structures, stacks and functions for the new operation

// Structure for storing aggregate operations
typedef struct AggregateOperation {
    char *node_text;
    gchar *node_path;
} AggregateOperation;

// Structure for storing delete operations
typedef struct DeleteOperation {
    char *node_text;
    gchar *node_path;
} DeleteOperation;

// Structure for the aggregate stack nodes
typedef struct AggregateStackNode {
    AggregateOperation data;
    struct AggregateStackNode *next;
} AggregateStackNode;

// Structure for the delete stack nodes
typedef struct DeleteStackNode {
    DeleteOperation data;
    struct DeleteStackNode *next;
} DeleteStackNode;

// Top of the aggregate stack
typedef struct AggregateStack {
    AggregateStackNode *top;
} AggregateStack;

// Top of the delete stack
typedef struct DeleteStack {
    DeleteStackNode *top;
} DeleteStack;

// Stacks for undo and redo operations
AggregateStack UNDO_STACK_AGGREGATE;
AggregateStack REDO_STACK_AGGREGATE;
DeleteStack UNDO_STACK_DELETE;
DeleteStack REDO_STACK_DELETE;

/**
 * @brief Initializes an aggregate stack.
 * 
 * @param stack Aggregate stack
 * 
 * @return void
 */
void init_aggregate_stack(AggregateStack *stack) {
    stack->top = NULL;
}

/**
 * @brief Initializes a delete stack.
 * 
 * @param stack Delete stack
 * 
 * @return void
 */
void init_delete_stack(DeleteStack *stack) {
    stack->top = NULL;
}

/**
 * @brief Pushes an aggregate operation to the stack.
 * 
 * - The operation is added to the top of the stack.
 * 
 * @param stack Aggregate stack
 * @param data Aggregate operation
 * 
 * @return void
 */
void push_aggregate_stack(AggregateStack *stack, AggregateOperation data) {
    // Create a new node
    AggregateStackNode *new_node = (AggregateStackNode *)malloc(sizeof(AggregateStackNode));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for aggregate stack node\n");
        return;
    }
    new_node->data = data;

    // Add the new node to the top of the stack
    new_node->next = stack->top;
    stack->top = new_node;
}

/**
 * @brief Pushes a delete operation to the stack.
 * 
 * - The operation is added to the top of the stack.
 * 
 * @param stack Delete stack
 * @param data Delete operation
 * 
 * @return void
 */
void push_delete_stack(DeleteStack *stack, DeleteOperation data) {
    // Create a new node
    DeleteStackNode *new_node = (DeleteStackNode *)malloc(sizeof(DeleteStackNode));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for delete stack node\n");
        return;
    }
    new_node->data = data;

    // Add the new node to the top of the stack
    new_node->next = stack->top;
    stack->top = new_node;
}

/**
 * @brief Pops an aggregate operation from the stack.
 * 
 * - The operation is removed from the top of the stack.
 * 
 * @param stack Aggregate stack
 * 
 * @return AggregateOperation Aggregate operation
 */
AggregateOperation pop_aggregate_stack(AggregateStack *stack) {
    // Check if the stack is empty
    if (stack->top == NULL) {
        printf("Error: Aggregate stack is empty\n");
        AggregateOperation empty_operation = {NULL, NULL};
        return empty_operation;
    }

    // Remove the top node
    AggregateStackNode *top_node = stack->top;
    stack->top = top_node->next;

    // Get the data of the top node
    AggregateOperation data = top_node->data;

    // Free the memory of the top node
    free(top_node);

    return data;
}

/**
 * @brief Pops a delete operation from the stack.
 * 
 * - The operation is removed from the top of the stack.
 * 
 * @param stack Delete stack
 * 
 * @return DeleteOperation Delete operation
 */
DeleteOperation pop_delete_stack(DeleteStack *stack) {
    // Check if the stack is empty
    if (stack->top == NULL) {
        printf("Error: Delete stack is empty\n");
        DeleteOperation empty_operation = {NULL, NULL};
        return empty_operation;
    }

    // Remove the top node
    DeleteStackNode *top_node = stack->top;
    stack->top = top_node->next;

    // Get the data of the top node
    DeleteOperation data = top_node->data;

    // Free the memory of the top node
    free(top_node);

    return data;
}

/**
 * @brief Returns the top aggregate operation of the stack.
 * 
 * @param stack Aggregate stack
 * 
 * @return AggregateOperation Aggregate operation
 */
AggregateOperation peek_aggregate_stack(AggregateStack *stack) {
    // Check if the stack is empty
    if (stack->top == NULL) {
        printf("Error: Aggregate stack is empty\n");
        AggregateOperation empty_operation = {NULL, NULL};
        return empty_operation;
    }

    return stack->top->data;
}

/**
 * @brief Returns the top delete operation of the stack.
 * 
 * @param stack Delete stack
 * 
 * @return DeleteOperation Delete operation
 */
DeleteOperation peek_delete_stack(DeleteStack *stack) {
    // Check if the stack is empty
    if (stack->top == NULL) {
        printf("Error: Delete stack is empty\n");
        DeleteOperation empty_operation = {NULL, NULL};
        return empty_operation;
    }

    return stack->top->data;
}

/**
 * @brief Frees the memory of the aggregate stack.
 * 
 * @param stack Aggregate stack
 * 
 * @return void
 */
void free_aggregate_stack(AggregateStack *stack) {
    while (stack->top != NULL) {
        pop_aggregate_stack(stack);
    }
}

/**
 * @brief Frees the memory of the delete stack.
 * 
 * @param stack Delete stack
 * 
 * @return void
 */
void free_delete_stack(DeleteStack *stack) {
    while (stack->top != NULL) {
        pop_delete_stack(stack);
    }
}

// #3# Create the undo and redo functions for the new operation

/**
 * @brief Undoes the last aggregate operation.
 * 
 * - The operation is removed from the undo stack.
 * - The operation is added to the redo stack.
 * - The operation is undone.
 * 
 * @return void
 */
void undo_aggregate_operation() {
    // Get the last operation
    AggregateOperation operation = pop_aggregate_stack(&UNDO_STACK_AGGREGATE);

    // Add the operation to the redo stack
    push_aggregate_stack(&REDO_STACK_AGGREGATE, operation);

    // Undo the operation
    GtkTreeIter child_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(MAIN_TREE_MODEL), 
                                        &child_iter, 
                                        operation.node_path);
    gtk_tree_store_remove(MAIN_TREE_MODEL, &child_iter);
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
void redo_aggregate_operation() {
    // Get the last operation
    AggregateOperation operation = pop_aggregate_stack(&REDO_STACK_AGGREGATE);

    // Add the operation to the undo stack
    push_aggregate_stack(&UNDO_STACK_AGGREGATE, operation);

    // Redo the operation
    // 1- Get the path of the node
    GtkTreePath *parent_path = gtk_tree_path_new_from_string(operation.node_path);
    gtk_tree_path_up(parent_path);
    gchar *parent_path_str = gtk_tree_path_to_string(parent_path);
    gtk_tree_path_free(parent_path);

    // 2- Get the parent node
    GtkTreeIter parent_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(MAIN_TREE_MODEL), 
                                        &parent_iter, 
                                        parent_path_str);

    // 3- Add the node to the parent node
    agregar_nodo_tree(MAIN_TREE_MODEL, &parent_iter, operation.node_text);
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
void undo_delete_operation() {
    // Get the last operation
    DeleteOperation operation = pop_delete_stack(&UNDO_STACK_DELETE);

    // Add the operation to the redo stack
    push_delete_stack(&REDO_STACK_DELETE, operation);

    // Undo the operation
    // 1- Get the position of the node
    GtkTreePath *parent_path = gtk_tree_path_new_from_string(operation.node_path);
    gint *position_list = gtk_tree_path_get_indices(parent_path);
    int length = gtk_tree_path_get_depth(parent_path);
    gint position = position_list[length - 1];

    // 2- Get the path of the parent node
    gtk_tree_path_up(parent_path);
    gchar *parent_path_str = gtk_tree_path_to_string(parent_path);
    gtk_tree_path_free(parent_path);

    // 3- Get the parent node
    GtkTreeIter parent_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(MAIN_TREE_MODEL), 
                                        &parent_iter, 
                                        parent_path_str);

    // 4- Add the node to the parent node
    insert_node_at_position(&parent_iter, position, operation.node_text);
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
void redo_delete_operation() {
    // Get the last operation
    DeleteOperation operation = pop_delete_stack(&REDO_STACK_DELETE);

    // Add the operation to the undo stack
    push_delete_stack(&UNDO_STACK_DELETE, operation);

    // Redo the operation
    // 1- Get the iter of the node
    GtkTreeIter child_iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(MAIN_TREE_MODEL), 
                                        &child_iter, 
                                        operation.node_path);
    
    // 2- Remove the node
    gtk_tree_store_remove(MAIN_TREE_MODEL, &child_iter);
}

// #4# Modify the clear_redo_stack to clear the new operation

/**
 * @brief Clears all the redo stack.
 * 
 * @return void
 */
void clear_redo_stack() {
    free_aggregate_stack(&REDO_STACK_AGGREGATE);
    free_delete_stack(&REDO_STACK_DELETE);
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// #5# Modify the undo and redo functions to deal with the new operation

/**
 * @brief Undo the last operation.
 * 
 * - The last operation is undone.
 * - The operation is added to the redo stack.
 * 
 * @return void
 */
void undo() {
    // If the operation stack is empty, do nothing
    if (UNDO_STACK_OPERATIONS.index == 0 && UNDO_STACK_OPERATIONS.top->next == NULL) {
        return;
    }

    // Get the last operation
    uint8_t last_operation = pop_operation_stack(&UNDO_STACK_OPERATIONS);
    switch (last_operation) {
        case AGGREGATE_OP:
            undo_aggregate_operation();
            break;
        case DELETE_OP:
            undo_delete_operation();
            break;
        default:
            printf("Error: Unknown operation\n");
            break;
    }

    // Add the operation to the operation stack
    push_operation_stack(&REDO_STACK_OPERATIONS, last_operation);
}

/**
 * @brief Redo the last operation.
 * 
 * - The last operation is redone.
 * - The operation is added to the undo stack.
 * 
 * @return void
 */
void redo() {
    // If the operation stack is empty, do nothing
    if (REDO_STACK_OPERATIONS.index == 0 && REDO_STACK_OPERATIONS.top->next == NULL) {
        return;
    }

    // Get the last operation
    uint8_t last_operation = pop_operation_stack(&REDO_STACK_OPERATIONS);
    switch (last_operation) {
        case AGGREGATE_OP:
            redo_aggregate_operation();
            break;
        case DELETE_OP:
            redo_delete_operation();
            break;
        default:
            printf("Error: Unknown operation\n");
            break;
    }

    // Add the operation to the operation stack
    push_operation_stack(&UNDO_STACK_OPERATIONS, last_operation);
}

// #6# Modify the initialization and closing functions to deal with the new operation

/**
 * @brief Initializes the history.
 * 
 * - Initializes the undo and redo stacks of all operations.
 * 
 * @return uint8_t 0 if the initialization was successful, 1 otherwise
 */
uint8_t init_history() {
    init_operation_stack(&UNDO_STACK_OPERATIONS);
    init_operation_stack(&REDO_STACK_OPERATIONS);

    init_aggregate_stack(&UNDO_STACK_AGGREGATE);
    init_aggregate_stack(&REDO_STACK_AGGREGATE);

    init_delete_stack(&UNDO_STACK_DELETE);
    init_delete_stack(&REDO_STACK_DELETE);

    return 0;
}

/**
 * @brief Closes the history.
 * 
 * - Frees the memory of the undo and redo stacks of all operations.
 * 
 * @return uint8_t 0 if the closing was successful, 1 otherwise
 */
uint8_t close_history() {
    free_operation_stack(&UNDO_STACK_OPERATIONS);
    free_operation_stack(&REDO_STACK_OPERATIONS);

    free_aggregate_stack(&UNDO_STACK_AGGREGATE);
    free_aggregate_stack(&REDO_STACK_AGGREGATE);

    free_delete_stack(&UNDO_STACK_DELETE);
    free_delete_stack(&REDO_STACK_DELETE);
    
    return 0;
}

// #7# Add a function to store the new operation

/**
 * @brief Stores an aggregate operation.
 * 
 * - The operation is stored in the undo stack.
 * - The redo stack is cleared.
 * 
 * @param node_text Text of the node
 * @param path_str Path of the added node
 * 
 * @return void
 */
void store_aggregate_operation(char *node_text, gchar *path_str) {
    // Create and store the operation
    AggregateOperation operation = {node_text, path_str};
    push_aggregate_stack(&UNDO_STACK_AGGREGATE, operation);

    // Clear the redo stack
    clear_redo_stack();

    // Add the operation to the operation stack
    push_operation_stack(&UNDO_STACK_OPERATIONS, AGGREGATE_OP);
}

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
void store_delete_operation(char *node_text, gchar *path_str) {
    // Create and store the operation
    DeleteOperation operation = {node_text, path_str};
    push_delete_stack(&UNDO_STACK_DELETE, operation);

    // Clear the redo stack
    clear_redo_stack();

    // Add the operation to the operation stack
    push_operation_stack(&UNDO_STACK_OPERATIONS, DELETE_OP);
}

// #8# Remember to modify the header file to include the new function
