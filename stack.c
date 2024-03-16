#include <stdio.h>
#include <stdlib.h>

/**
 * This code snippet defines a preprocessor macro `CLEAR` that is used to clear the console screen.
 * On Windows, it sets `CLEAR` to "cls" which is the command to clear the console screen.
 * On other platforms, it sets `CLEAR` to "clear" which is the command to clear the console screen.
 */
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

/**
 * @struct node
 * @brief Represents a node in a linked list.
 * 
 * This struct contains an integer value and a pointer to the next node in the list.
 */
struct node {
    int info;               /**< The integer value stored in the node. */
    struct node *next;      /**< Pointer to the next node in the list. */
};

/**
 * Pushes an element onto the stack.
 *
 * This function creates a new node with the given value and adds it to the top of the stack.
 *
 * @param x The value to be pushed onto the stack.
 * @param top A pointer to the top of the stack.
 */
void push(int x, struct node **top) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->info = x;
    newNode->next = *top;
    *top = newNode;
}

/**
 * Prints the contents of a stack from top to bottom.
 *
 * @param top The top node of the stack.
 */
void printStack(struct node *top) {
    if (top == NULL) {
        printf("The stack is empty.\n");
        return;
    }
    printf("Stack Contents (Top to Bottom):\n");
    int position = 1;
    while (top != NULL) {
        printf("Position %d: %d\n", position++, top->info);
        top = top->next;
    }
    printf("\n");
}

/**
 * Removes and returns the top element from the stack.
 * If the stack is empty, it prints an error message and returns -1.
 *
 * @param top A pointer to the top of the stack.
 * @return The value of the top element that was removed, or -1 if the stack is empty.
 */
int pop(struct node **top) {
    if (*top == NULL) {
        printf("The stack is empty.\n");
        return -1;
    }
    int info = (*top)->info;
    struct node *temp = *top;
    *top = (*top)->next;
    free(temp);
    return info;
}

/**
 * Clears the stack by deallocating all the nodes.
 * 
 * @param top A pointer to the top of the stack.
 */
void clearStack(struct node **top) {
    struct node *current = *top;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp);
    }
    *top = NULL;
}

/**
 * Calculates the size of a stack.
 *
 * This function takes the top node of a stack as input and counts the number of nodes in the stack.
 *
 * @param top The top node of the stack.
 * @return The size of the stack.
 */
int stackSize(struct node *top) {
    int count = 0;
    while (top != NULL) {
        count++;
        top = top->next;
    }
    return count;
}

/**
 * Checks if the stack is empty.
 *
 * @param top The top node of the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int verifyEmpty(struct node *top) {
    return (top == NULL);
}

/**
 * Inserts an element at a specified position in the stack.
 *
 * @param x The value to be inserted.
 * @param position The position at which the element should be inserted.
 * @param top A pointer to the top of the stack.
 */
void insertAtPosition(int x, int position, struct node **top) {
    int size = stackSize(*top);
    if (position < 0 || position > size) {
        printf("Invalid position.\n");
        return;
    }
    if (position == 0) {
        push(x, top);
        return;
    }
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->info = x;
    struct node *current = *top;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

/**
 * Deletes the node at the specified position in the stack.
 *
 * @param position The position of the node to be deleted.
 * @param top A pointer to the top of the stack.
 */
void deleteAtPosition(int position, struct node **top) {
    int size = stackSize(*top);
    if (position < 0 || position >= size) {
        printf("Invalid position.\n");
        return;
    }
    struct node *tempStack = NULL;
    for (int i = 0; i < position; i++) {
        push(pop(top), &tempStack);
    }
    pop(top);
    while (!verifyEmpty(tempStack)) {
        push(pop(&tempStack), top);
    }
}

/**
 * Inserts an element at a specified position in the stack.
 *
 * @param x The element to be inserted.
 * @param position The position at which the element should be inserted.
 * @param top A pointer to the top of the stack.
 */
void insertAtNPosition(int x, int position, struct node **top) {
    // Calculate the size of the stack
    int size = stackSize(*top);
    
    // Check if the position is valid
    if (position < 0 || position > size) {
        printf("Invalid position.\n");
        return;
    }
    
    // Create a temporary stack
    struct node *tempStack = NULL;
    
    // Iterate through the original stack
    for (int i = 0; i < size; i++) {
        // If the current position matches the specified position, push the element to the temporary stack
        if (i == position) {
            push(x, &tempStack);
        }
        
        // Push the top element of the original stack to the temporary stack
        push(pop(top), &tempStack);
    }
    
    // Transfer the elements from the temporary stack back to the original stack
    while (!verifyEmpty(tempStack)) {
        push(pop(&tempStack), top);
    }
}

/**
 * Clears the screen by executing the system command to clear the console.
 */
void clearScreen() {
    system(CLEAR);
}

int main() {
    struct node *stack = NULL;
    int choice = 0, value = 0, position = 0;

    while (choice != 5) {
        printf("Stack Operations:\n");
        printf("1. Insert into stack\n");
        printf("2. Delete at specific position\n");
        printf("3. Insert at specific position using stack\n");
        printf("4. Print stack with position numbers\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch (choice) {
            case 1:
                clearScreen();
                printf("You chose to insert into stack.\n");
                printf("Enter value to insert: ");
                scanf("%d", &value);
                push(value, &stack);
                break;
            case 2:
                clearScreen();
                printf("You chose to delete at specific position.\n");
                printf("Stack Contents:\n");
                printStack(stack);
                printf("\nEnter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(position - 1, &stack);
                break;
            case 3:
                clearScreen();
                printf("You chose to insert at specific position using stack.\n");
                printf("Stack Contents:\n");
                printStack(stack);
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Enter position to insert: ");
                scanf("%d", &position);
                insertAtNPosition(value, position - 1, &stack);
                break;
            case 4:
                clearScreen();
                printStack(stack);
                break;
            case 5:
                clearScreen();
                printf("Exiting...\n");
                return 0;
            default:
                clearScreen();
                printf("Invalid option. Please try again.\n");
                break;
        }

        printf("\n");
    }

    return 0;
}
