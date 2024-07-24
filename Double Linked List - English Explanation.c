#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//make a node so it can be a linked list
struct node {
    char n[50];
    int value;
    struct node *next;
    struct node *prev;
} *nnode, *head = NULL, *tail = NULL, *t = NULL, *t1 = NULL;//for the sake of easier access we can make this (optional move)

//remember this function because it will be very needed (this is the absolutely starter) if you're studying data structures
struct node *new_node(int value, char name[50]) {
    nnode = (struct node*)malloc(sizeof(struct node));
    strcpy(nnode->n, name);
    nnode->value = value;
    nnode->next = NULL;
    nnode->prev = NULL;
    
    return nnode;
}

//feel free to compare this with single linked list, it will be the same with extra steps since prev exist now
void insert_front(int value, char name[50]) {
    if (head != NULL) {
        nnode = new_node(value, name);
        nnode->next = head;
        head->prev = nnode;//the extra step, you need to navigate the prev as well
        head = nnode;
    } else {
        head = tail = new_node(value, name);
    }
}

void insert_back(int value, char name[50]) {
    if (tail != NULL) {
        nnode = new_node(value, name);
        tail->next = nnode;
        nnode->prev = tail;//the extra step, you need to navigate the prev as well
        tail = nnode;
    } else {
        head = tail = new_node(value, name);
    }
}

void insert_middle(int value, char name[50]) {
    t = head;
    nnode = new_node(value, name);
    
    while (t != NULL && t->value < value) {
        t = t->next;
    }
    
    if (t == head) {
        insert_front(value, name);
    } else if (t == NULL) {
        insert_back(value, name);
    } else {
        t1 = t->prev;
        //link the new node with the t and t1 first
        nnode->next = t;
        nnode->prev = t1;
        //then modify the t1 and t
        t1->next = nnode;
        t->prev = nnode;
    }
}

//with double linked list delete became somewhat easier since prev exist

void delete_front() {
    if (head != NULL) {
        t = head;
        head = head->next;//move the head to the next data
        if (head != NULL) {
            head->prev = NULL;//unlink the node
        } else {
            tail = NULL;//if there was only one node to begin with so head = NULL that means tail is also NULL
        }
        free(t);//free the t --> original head
    }
}

//has the same pattern with delete_front but it's with tail this time
void delete_back() {
    if (tail != NULL) {
        t = tail;//the t is tail
        tail = tail->prev;//move the tail
        if (tail != NULL) {
            tail->next = NULL;//unlink it
        } else {
            head = NULL;//if theres only one node
        }
        free(t);//free the original tail
    }
}


void delete_value(int value) {
    t = head;//t is for the variable we're going to loop without touching the head / tail
    while (t != NULL && t->value != value) {
        t = t->next;
    }
    if (t == head) {
        delete_front();
    } else if (t == tail) {
        delete_back();
    } else if (t != NULL) {
    	//modify the t1 first, unlink
        t1 = t->prev;
        t1->next = t->next;
        //modify the t1->prev
        t->next->prev = t1;
        free(t);//free the node that we are going to delete
    }
}

//this is just style you can use whatever layout you prefer
void print_list() {
    t = head;
    while (t != NULL) {
        printf("%s, %d <-> ", t->n, t->value);
        t = t->next;
    }
    printf("NULL\n");
}

//just print the head
void print_head() {
    if (head != NULL) {
        printf("%s, %d\n", head->n, head->value);
    } else {
        printf("No Linked List detected\n");
    }
}

int main() {
    int choice, value;
    char name[50];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at front\n");
        printf("2. Insert at back\n");
        printf("3. Insert in middle\n");
        printf("4. Delete from front\n");
        printf("5. Delete from back\n");
        printf("6. Delete a specific value (delete mid)\n");
        printf("7. Print list\n");
        printf("8. Print head\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter value: ");
                scanf("%d", &value);
                insert_front(value, name);
                break;
            case 2:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter value: ");
                scanf("%d", &value);
                insert_back(value, name);
                break;
            case 3:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter value: ");
                scanf("%d", &value);
                insert_middle(value, name);
                break;
            case 4:
                delete_front();
                break;
            case 5:
                delete_back();
                break;
            case 6:
            	//this is basically delete mid just depends on the value
                printf("Enter value to delete: ");
                scanf("%d", &value);
                delete_value(value);
                break;
            case 7:
                print_list();
                break;
            case 8:
                print_head();
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
