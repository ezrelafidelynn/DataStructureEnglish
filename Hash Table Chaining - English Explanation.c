#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_SIZE 6

//node (single linked list)
struct Node {
    int value;
    char key[100];
    struct Node* next;
};

//from character became ascii--> hash key -> converted number from the characters
int get_hash_key(char key[]) {
    int value = 0;
    int i, len = strlen(key);
    
    for (i = 0; i < len; i++) {
        value += tolower(key[i]) - 'a';
    }
    return value % HASH_SIZE;
}

//same like the other linked list
struct Node* new_node(char key[], int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(temp->key, key);
    temp->value = value;
    temp->next = NULL;
    
    return temp;
}

struct Node* insert_node(struct Node* curr, char key[], int value) {
    if (curr == NULL) {
        return new_node(key, value);
    } else if (strcmp(curr->key, key) == 0) {//if at that [key] is empty just put it in
        curr->value = value;
        return curr;
    }
    curr->next = insert_node(curr->next, key, value);//else we just make the node next to the tail (recursive case)
    return curr;
}

void insert(struct Node* head[], char key[], int value) {
    int hash_key = get_hash_key(key);
    head[hash_key] = insert_node(head[hash_key], key, value);
}

struct Node* search_node(struct Node* curr, char key[]) {
    if (curr == NULL) {
        return NULL;//if not found it will go here since it's recursive
    } else if (strcmp(curr->key, key) == 0) {
        return curr;
    }
    return search_node(curr->next, key);
}

void search(struct Node* head[], char key[]) {
    struct Node* temp;
    int hash_key = get_hash_key(key);
    
    temp = search_node(head[hash_key], key);//temp variable to hold it
    
    if (temp == NULL) {
        printf("\nKey %s not found!\n", key);
    } else {
        printf("\nData found! Key: %s, Value: %d\n", key, temp->value);
    }
}

struct Node* delete_node(struct Node* curr, char key[]) {
    if (curr == NULL) {
        return NULL;
    } else if (strcmp(curr->key, key) == 0) {
        struct Node* temp = curr->next;
        free(curr);
        return temp;
    }
    curr->next = delete_node(curr->next, key);//recursive case --> delete the tail
    return curr;
}

void deletes(struct Node* head[], char key[]) {
    struct Node* temp;
    int hash_key = get_hash_key(key);
    
    temp = search_node(head[hash_key], key);
    
    if (temp == NULL) {
        printf("\nKey %s not found!\n", key);
    } else {
        printf("\nData deleted! Key: %s, Value: %d\n", key, temp->value);
        head[hash_key] = delete_node(head[hash_key], key);//it will delete here
    }
}

void print(struct Node* head[]) {
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        printf("%d: ", i);
        struct Node* curr = head[i];
        while (curr != NULL) {
            printf("%s, %d ", curr->key, curr->value);
            if (curr->next != NULL) {
                printf("-> ");
            }
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    struct Node* head[HASH_SIZE] = {NULL};
    
    int choice;
    char key[100];
    int value;

    while (true) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Print\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%s", key);
                printf("Enter value: ");
                scanf("%d", &value);
                insert(head, key, value);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%s", key);
                search(head, key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%s", key);
                deletes(head, key);
                break;
            case 4:
                print(head);
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
