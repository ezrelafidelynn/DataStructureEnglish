#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//please study double linked list before studying stack or queue

struct node {
    int value;
    struct node *next, *prev;    
};

struct node *curr, *head, *tail;

struct node* new_node(int value) {
    curr = (struct node*)malloc(sizeof(struct node));
    curr->value = value;
    curr->next = curr->prev = NULL;
    return curr;
}

//push tail
void enqueue(int value) {
    curr = new_node(value);
    if (head == NULL) {
        head = tail = curr;
    } else {
        tail->next = curr;
        curr->prev = tail;
        tail = curr;
    }
}

//pop head
void dequeue() {
    if (head == NULL) {
        return;
    }
    if (head == tail) {
        free(head);
        head = tail = NULL;
    } else {
        curr = head;
        head = head->next;
        free(curr);
        head->prev = NULL;
    }
}

struct node* peek() {
    if (head == NULL) {
        printf("There is no data\n");
    } else {
        printf("Head's Value : %d \n", head->value);
    }
    return head;
}

bool is_empty() {
    if (head == NULL) {
        printf("Queue is empty\n");
        return true;
    }
    printf("Queue is not empty\n");
    return false;
}

void view_data() {
    curr = head;
    if (head == NULL) {
        printf("There is no data...\n");
        return;
    }
    while (curr) {
        printf("Value : %d \n", curr->value);
        curr = curr->next;
    }
}

int main() {
    int choice, value;
    while (true) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Check if empty\n");
        printf("5. View data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                printf("Head value dequeued.\n");
                break;
            case 3:
                peek();
                break;
            case 4:
                is_empty();
                break;
            case 5:
                view_data();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
