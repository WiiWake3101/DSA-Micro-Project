#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 50

struct Node {
    char task[MAX_TASK_LENGTH];
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

struct LinkedList* initializeLinkedList() {
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    list->head = NULL;
    return list;
}

void insertAtBeginning(struct LinkedList* list, const char task[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->task, task);

    newNode->next = list->head;
    list->head = newNode;

    printf("Task '%s' inserted at the beginning.\n", task);
}

void insertAtPosition(struct LinkedList* list, const char task[], int position) {
    if (position <= 0) {
        printf("Invalid position. Please enter a position greater than 0.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->task, task);

    if (position == 1 || list->head == NULL) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }

        if (current == NULL) {
            // Insert at the end if the position is beyond the current size
            printf("Invalid position. Inserting at the end.\n");
            current = list->head;
            while (current->next != NULL) {
                current = current->next;
            }
        }

        newNode->next = current->next;
        current->next = newNode;
    }
    printf("Task '%s' inserted at position %d.\n", task, position);
}

void insertAtEnd(struct LinkedList* list, const char task[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->task, task);
    newNode->next = NULL;

    if (list->head == NULL) {
        // If the list is empty, insert at the beginning
        printf("Head is NULL. Inserting at the beginning.\n");
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("Task '%s' inserted at the end.\n", task);
}

void removeAtBeginning(struct LinkedList* list) {
    if (list->head == NULL) {
        printf("Linked list is empty. Cannot remove.\n");
        return;
    }

    struct Node* temp = list->head;
    list->head = temp->next;
    free(temp);

    // Print the updated list
    printf("Task removed from the beginning.\n");
}

void removeAtPosition(struct LinkedList* list, int position) {
    if (list->head == NULL) {
        printf("Linked list is empty. Cannot remove.\n");
        return;
    }

    if (position == 1) {
        removeAtBeginning(list);
        return;
    }

    struct Node* current = list->head;
    struct Node* prev = NULL;

    for (int i = 1; i < position && current != NULL; i++) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid position. Nothing to remove.\n");
        return;
    }

    prev->next = current->next;
    free(current);
    printf("Task removed from position %d.\n", position);
}

void removeAtEnd(struct LinkedList* list) {
    if (list->head == NULL) {
        printf("Linked list is empty. Cannot remove.\n");
        return;
    }

    struct Node* current = list->head;
    struct Node* prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        // Only one element in the list
        list->head = NULL;
    } else {
        prev->next = NULL;
    }

    free(current);

    // Print the updated list
    printf("Task removed from the end.\n");
}

void displayList(const struct LinkedList* list) {
    const struct Node* current = list->head;
    printf("\n");
    printf("To-Do List:\n");
    while (current != NULL) {
        printf("%s\n", current->task);
        current = current->next;
    }
}

int main() {
    struct LinkedList* toDoList = initializeLinkedList();

    int mainChoice, operationChoice, position;
    char task[MAX_TASK_LENGTH];

    do {
        printf("\nMain Menu:\n1. Insert Task\n2. Remove Task\n3. Display List\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                printf("\nInsert Menu:\n1. Insert at Beginning\n2. Insert at Any Position\n3. Insert at End\n4. Back to Main Menu\n");
                printf("Enter your choice: ");
                scanf("%d", &operationChoice);

                switch (operationChoice) {
                    case 1:
                        printf("Enter the task: ");
                        getchar(); // Consume the newline character from the previous input
                        fgets(task, MAX_TASK_LENGTH, stdin);
                        task[strcspn(task, "\n")] = '\0'; // Remove the newline character from the input
                        insertAtBeginning(toDoList, task);
                        break;

                    case 2:
                        printf("Enter the task: ");
                        getchar(); // Consume the newline character from the previous input
                        fgets(task, MAX_TASK_LENGTH, stdin);
                        task[strcspn(task, "\n")] = '\0'; // Remove the newline character from the input
                        printf("Enter the position to insert (1 for beginning): ");
                        scanf("%d", &position);
                        insertAtPosition(toDoList, task, position);
                        break;

                    case 3:
                        printf("Enter the task: ");
                        getchar(); // Consume the newline character from the previous input
                        fgets(task, MAX_TASK_LENGTH, stdin);
                        task[strcspn(task, "\n")] = '\0'; // Remove the newline character from the input
                        insertAtEnd(toDoList, task);
                        break;

                    case 4:
                        printf("Returning to Main Menu.\n");
                        break;

                    default:
                        printf("Invalid choice. Returning to Main Menu.\n");
                }
                break;

            case 2:
                printf("\nRemove Menu:\n1. Remove from Beginning\n2. Remove from Any Position\n3. Remove from End\n4. Back to Main Menu\n");
                printf("Enter your choice: ");
                scanf("%d", &operationChoice);

                switch (operationChoice) {
                    case 1:
                        removeAtBeginning(toDoList);
                        break;

                    case 2:
                        printf("Enter the position to remove: ");
                        scanf("%d", &position);
                        removeAtPosition(toDoList, position);
                        break;

                    case 3:
                        removeAtEnd(toDoList);
                        break;

                    case 4:
                        printf("Returning to Main Menu.\n");
                        break;

                    default:
                        printf("Invalid choice. Returning to Main Menu.\n");
                }
                break;

            case 3:
                displayList(toDoList);
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (mainChoice != 4);

    return 0;
}