#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

struct node {
    int info;
    struct node *next;
};

void enqueue(int x, struct node **front, struct node **rear) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->info = x;
    newNode->next = NULL;
    if (*rear == NULL) {
        *front = newNode;
    } else {
        (*rear)->next = newNode;
    }
    *rear = newNode;
}

void printQueueWithPosition(struct node *front) {
    if (front == NULL) {
        printf("The queue is empty.\n");
        return;
    }
    printf("Queue Contents (Front to Rear):\n");
    int position = 1;
    while (front != NULL) {
        printf("Position %d: %d\n", position++, front->info);
        front = front->next;
    }
    printf("\n");
}

int dequeue(struct node **front, struct node **rear) {
    if (*front == NULL) {
        printf("The queue is empty.\n");
        return -1;
    }
    int info = (*front)->info;
    struct node *temp = *front;
    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    }
    free(temp);
    return info;
}

void clearQueue(struct node **front, struct node **rear) {
    struct node *current = *front;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp);
    }
    *front = *rear = NULL;
}

int queueSize(struct node *front) {
    int count = 0;
    while (front != NULL) {
        count++;
        front = front->next;
    }
    return count;
}

int isEmpty(struct node *front) {
    return (front == NULL);
}

void insertAtPosition(int x, int position, struct node **front, struct node **rear) {
    int size = queueSize(*front);
    if (position < 0 || position > size) {
        printf("Invalid position.\n");
        return;
    }
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->info = x;
    if (position == 0) {
        newNode->next = *front;
        *front = newNode;
        if (*rear == NULL) {
            *rear = newNode;
        }
        return;
    }
    struct node *current = *front;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == NULL) {
        *rear = newNode;
    }
}

void deleteAtPosition(int position, struct node **front, struct node **rear) {
    int size = queueSize(*front);
    if (position < 0 || position >= size) {
        printf("Invalid position.\n");
        return;
    }
    struct node *temp = *front;
    struct node *prev = NULL;
    int count = 0;

    while (count < position) {
        prev = temp;
        temp = temp->next;
        count++;
    }

    if (prev == NULL) {
        *front = temp->next;
    } else {
        prev->next = temp->next;
    }
    if (temp == *rear) {
        *rear = prev;
    }
    temp->next = NULL;
    free(temp);
}

void clearScreen() {
    system(CLEAR);
}

int main() {
    struct node *front = NULL;
    struct node *rear = NULL;
    int choice, value, position;

    while (1) {
        printf("Queue Operations:\n");
        printf("1. Enqueue into queue\n");
        printf("2. Dequeue from queue\n");
        printf("3. Insert at specific position\n");
        printf("4. Delete at specific position\n");
        printf("5. Print queue with position numbers\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value, &front, &rear);
                break;
            case 2:
                printf("Queue Contents:\n");
                printQueueWithPosition(front);
                printf("Dequeued element: %d\n", dequeue(&front, &rear));
                break;
            case 3:
                printf("Queue Contents:\n");
                printQueueWithPosition(front);
                printf("Enter position to insert: ");
                scanf("%d", &position);
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtPosition(value, position - 1, &front, &rear);
                break;
            case 4:
                printf("Queue Contents:\n");
                printQueueWithPosition(front);
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(position - 1, &front, &rear);
                break;
            case 5:
                printQueueWithPosition(front);
                break;
            case 6:
                clearScreen();
                printf("Exiting...\n");
                clearQueue(&front, &rear);
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
