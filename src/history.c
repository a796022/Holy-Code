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

////////////////////////////////////////////////////////////////////////////////
// PRIVATE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// #1# Create the structures, stacks and functions for the new operation

// Structure for storing aggregate operations
typedef struct AggregateOperation {
    char *node_text;
    gchar *node_path;
} AggregateOperation;

// Structure for the aggregate stack nodes
typedef struct AggregateStackNode {
    AggregateOperation data;
    struct AggregateStackNode *next;
} AggregateStackNode;

// Top of the aggregate stack
typedef struct AggregateStack {
    AggregateStackNode *top;
} AggregateStack;

// Stacks for undo and redo operations
AggregateStack UNDO_STACK_AGGREGATE;
AggregateStack REDO_STACK_AGGREGATE;

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
    // Imprimo el puntero del stack y del new_node
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

// #2# Create the undo and redo functions for the new operation

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
    // 1- Get the path of the parent node
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

// #3# Modify the clear_redo_stack to clear the new operation

/**
 * @brief Clears all the redo stack.
 * 
 * @return void
 */
void clear_redo_stack() {
    free_aggregate_stack(&REDO_STACK_AGGREGATE);
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// #4# Modify the undo and redo functions to deal with the new operation

/**
 * @brief Undo the last operation.
 * 
 * @return void
 */
void undo() {
    undo_aggregate_operation();
}

/**
 * @brief Redo the last operation.
 * 
 * @return void
 */
void redo() {
    redo_aggregate_operation();
}

// #5# Modify the initialization and closing functions to deal with the new operation

/**
 * @brief Initializes the history.
 * 
 * - Initializes the undo and redo stacks of all operations.
 * 
 * @return uint8_t 0 if the initialization was successful, 1 otherwise
 */
uint8_t init_history() {
    init_aggregate_stack(&UNDO_STACK_AGGREGATE);
    init_aggregate_stack(&REDO_STACK_AGGREGATE);

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
    free_aggregate_stack(&UNDO_STACK_AGGREGATE);
    free_aggregate_stack(&REDO_STACK_AGGREGATE);
    
    return 0;
}

// #6# Add a function to store the new operation

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
}

// #7# Remember to modify the header file to include the new function
