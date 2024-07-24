#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//make a node for the linked list
struct Node {
    char name[50];
    int age;    
    struct Node* next;//single only need next
};

//for easier access
struct Node* head = NULL;
struct Node* tail = NULL;

//print all node
void view_all_node() {
    struct Node* curr = head;
    while(curr != NULL) {
        printf("[%s | %d] -> ", curr->name, curr->age);
        curr = curr->next;
    }
    printf("NULL\n");
}

//in every node you will encounter this same pattern of create new node function so remember this
struct Node* create_new_node(char name[], int age) {
    struct Node* createdNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(createdNode->name, name);
    createdNode->age = age;
    createdNode->next = NULL;
    return createdNode;
}

//insert at the front of the linked list
void push_head(char* name, int age) {
    struct Node* toInsert = create_new_node(name, age);
    if(head == NULL) {//if there's no linked list
        head = toInsert;
        tail = toInsert;
    } else {
        toInsert->next = head;//make the front linked to the head
        head = toInsert;//head became the new node
    }
}

//insert at the back
void push_tail(char* name, int age) {
    struct Node* toInsert = create_new_node(name, age);//from the create new node function
    if(tail == NULL) {//if there's no linked list
        head = toInsert;
        tail = toInsert;
    } else {
        tail->next = toInsert;//link the tail with the new node
        tail = toInsert;//tail became the new node
    }
}

//insert by age / int value
void push_mid(char* name, int age) {
    struct Node* toInsert = create_new_node(name, age);
    if(head == NULL) {//if no linked list found
        head = toInsert;
        tail = toInsert;
    } else {
        struct Node* curr = head;//curr will be looped
        while(curr->next != NULL && curr->next->age <= age) {//loop until the value of curr > age 
            curr = curr->next;
        }
        toInsert->next = curr->next;//link the new node with the curr->next (the data after curr)
        curr->next = toInsert;//link curr with the new node, the previous curr->next is modified so new node is in between
        if(curr == tail) {
            tail = toInsert;//if only the curr = tail
        }
    }
}

//if you can do delete, search should be an easy step for you
struct Node* search_node(char name[]) {
    struct Node* curr = head;
    while(curr != NULL && strcmp(curr->name, name) != 0) {//search until the name value of the data and curr
        curr = curr->next;
    }
    return curr;//if not found it will return NULL
}

//delete by name
void pop_mid(char name[]) {
    if(head != NULL) {
        struct Node* curr = head;
        while(curr->next != NULL && strcmp(curr->next->name, name) != 0) {
			//search until the data after curr the same with the value
            curr = curr->next;
        }
        if(curr->next != NULL) {
            struct Node* toDelete = curr->next;//make the node we want to delete as toDelete
            curr->next = toDelete->next;//make the toDelete not linked with curr so it can be deleted without erasing the rest of the linked list
            free(toDelete);//you need to free it otherwise it will still have the remaining value
        }
    }
}

//delete the head
void pop_head() {
    if(head != NULL) {
        struct Node* temp = head;
        if(head == tail) {//if there's only one node
            head = NULL;
            tail = NULL;
        } else {
            head = head->next;//modify the head so it wont be NULL
        }
        free(temp);//free the original head
    }
}

//delete by the tail
void pop_tail() {
    if(tail != NULL) {
        struct Node* curr = head;
        if(head == tail) {//if there's only one node
            head = NULL;
            tail = NULL;
            free(curr);
        } else {
            while(curr->next != tail) {//loop until curr is just one node behind the tail
                curr = curr->next;
            }
            free(curr->next);
            curr->next = NULL;//make the remaining value NULL
            tail = curr;//modify the tail
        }
    }
}

int main() {
    int choice;
    char name[50];
    int age;
    struct Node* searchedNode;

    do {
        printf("Menu:\n");
        printf("1. Add Node at Head\n");
        printf("2. Add Node at Tail\n");
        printf("3. Add Node at Middle\n");
        printf("4. View All Nodes\n");
        printf("5. Search Node by Name\n");
        printf("6. Delete Node by Name (pop mid)\n");
        printf("7. Delete Head Node\n");
        printf("8. Delete Tail Node\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                push_head(name, age);
                break;
            case 2:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                push_tail(name, age);
                break;
            case 3:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                push_mid(name, age);
                break;
            case 4:
                view_all_node();
                break;
            case 5:
            	//delete by searching the name first
                printf("Enter name to search: ");
                scanf("%s", name);
                searchedNode = search_node(name);
                if(searchedNode != NULL) {
                    printf("Found node: [%s | %d]\n", searchedNode->name, searchedNode->age);
                } else {
                    printf("Node not found\n");
                }
                break;
            case 6:
                printf("Enter name to delete: ");
                scanf("%s", name);
                pop_mid(name);
                break;
            case 7:
                pop_head();
                break;
            case 8:
                pop_tail();
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != 9);
    return 0;
}
