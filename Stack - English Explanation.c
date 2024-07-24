#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//this is single linked list version
//do compare the difference between double and single linked list first
//if you know how to modify single to double, feel free to modify this into double linked list version
struct node{
    int value;
    struct node *next;
};

struct node *curr, *head;

struct node* new_node(int value){
    curr = (struct node*)malloc(sizeof(struct node));
    curr->value = value;
    curr->next = NULL;
    return curr;
}

//push head (remember linked list)
void push(int value){
    curr = new_node(value);
    if(head == NULL){
        head = curr;
    } else {
        curr->next = head;
        head = curr;
    }
}

//pop head (remember linked list)
void pop(){
    if(head == NULL){
        return;
    }
    if(head->next == NULL){
        free(head);
        head = NULL;
    } else {
        curr = head;
        head = head->next;
        free(curr);
    }
}

//print head
struct node* peek(){
    if(head == NULL){
        printf("There is no data.\n");
        return NULL;
    } else {
        printf("Head\'s Value : %d\n", head->value);
        return head;
    }
}

//random checking if the stack empty
bool is_empty(){
    if(head == NULL){
        printf("Stack is empty...\n");
        return true;
    }
    printf("Stack is not empty...\n");
    return false;
}

//print the stack
void view_data(){
    curr = head;
    if(head == NULL){
        printf("There\'s no data\n");
        return;
    }
    while(curr){
        printf("Value : %d \n", curr->value);
        curr = curr->next;
    }
}

int main(){
    int choice, value;
    while(true){
        printf("\nEzrela\'s Stack Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Check if empty\n");
        printf("5. View data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                printf("Top value popped.\n");
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
