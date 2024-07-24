#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//feel free to compare this with the regular queue 
//p.s. it's at the enqueue

struct Data {
    char name[100];
    int value;
    struct Data *next, *prev;
} *head = NULL, *tail = NULL;

struct Data *create_new_node(char name[], int value) {
    struct Data *newNode = (struct Data*)malloc(sizeof(struct Data));
    strcpy(newNode->name, name);
    newNode->value = value;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

bool is_empty() {
    return head == NULL;
}

void push_head(char name[], int value) {
    struct Data *newNode = create_new_node(name, value);
    if (is_empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void push_tail(char name[], int value) {
    struct Data *newNode = create_new_node(name, value);
    if (is_empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

//pop mid --> depends on the value
void enqueue(char name[], int value) {
    struct Data *newNode = create_new_node(name, value);
    
    if (is_empty()) {
        head = tail = newNode;
    } else {
        if (value < head->value) {
            push_head(name, value);
        } else if (value >= tail->value) {
            push_tail(name, value);
        } else {
            struct Data *temp = tail;
            while (temp->value > value) {
                temp = temp->prev;
            }
            newNode->prev = temp;
            newNode->next = temp->next;
            newNode->next->prev = newNode;
            temp->next = newNode;
        }
    }
}

//pop head
void dequeue() {
    if (!is_empty()) {
        struct Data *temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        } else {
            tail = NULL;
        }
        free(temp);
    }
}

void peek() {
    if (!is_empty()) {
        printf("Peek(First data) : %s %d\n", head->name, head->value);
    } else {
        printf("Queue is empty\n");
    }
}

void view_all_data() {
    struct Data *temp = head;
    if (!is_empty()) {
        printf("Our Queue: \n");
        while (temp != NULL) {
            printf("%s - %d \n", temp->name, temp->value);
            temp = temp->next;
        }
    } else {
        printf("Queue is empty\n");
    }
}

int main() {
    int choice;
    char name[100];
    int value;

    while (true) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. View all data\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(name, value);
                break;
            case 2:
                dequeue();
                printf("Dequeued the first data.\n");
                break;
            case 3:
                peek();
                break;
            case 4:
                view_all_data();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
