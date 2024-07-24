#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50
#define LENGTH 100

//feel free to compare this with thte chaining
//p.s. look at the insert and delete

struct Stuff {
    char name[LENGTH];//name = key
    int price;//price = value
} *bucket[SIZE];

int count = 0;

struct Stuff* new_node(char name[LENGTH], int price) {
    struct Stuff* node = (struct Stuff*)malloc(sizeof(struct Stuff));
    strcpy(node->name, name);
    node->price = price;
    return node;
}

int hash(char name[LENGTH]) {
    int i = 0;
    int key = 0;
    int len = strlen(name);
    
    for (i = 0; i < len; i++) {
        key += name[i];
    }
    return key % SIZE;
}

void insert(char name[LENGTH], int price) {
    int hashkey = hash(name);
    int pos = hashkey;
    
    //all slots full
    if (count == SIZE) {
        printf("Bucket Overload. \n");
        return;
    }
    
    //collision resolution using linear probing
    while (bucket[pos] != NULL) {
        pos = (pos + 1) % SIZE;
    }
    
    //empty slot
    bucket[pos] = new_node(name, price);
    count++;
}

void view() {
    int i = 0;
    
    for (i = 0; i < SIZE; i++) {
        if (bucket[i]) {
            printf("%s : %d. hashkey: %d\n", bucket[i]->name, bucket[i]->price, hash(bucket[i]->name));
        } else {
            printf("-\n");
        }
    }
}

struct Stuff* search(char name[LENGTH]) {
    int hashkey = hash(name);
    int pos = hashkey;
    
    do {
        if (bucket[pos] && strcmp(bucket[pos]->name, name) == 0) {
            return bucket[pos];
        }
        pos = (pos + 1) % SIZE;
    } while (pos != hashkey);
    
    return NULL;
}

void remove_node(char name[LENGTH]) {
    int hashkey = hash(name);
    int pos = hashkey;
    
    do {
        if (bucket[pos] && strcmp(bucket[pos]->name, name) == 0) {
            free(bucket[pos]);
            bucket[pos] = NULL; //remove
            count--;
            return;
        }
        
        pos = (pos + 1) % SIZE;//else loop until pos == hashkey or bucket[pos] && strcmp(bucket[pos]->name, name) == 0
    } while (pos != hashkey);
}

int main() {
    int choice;
    char name[LENGTH];
    int price;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Remove\n");
        printf("4. View\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter price: ");
                scanf("%d", &price);
                insert(name, price);
                break;
            case 2:
                printf("Enter name to search: ");
                scanf("%s", name);
                if (search(name)) {
                    printf("Found: %s - %d\n", name, search(name)->price);
                } else {
                    printf("Not Found\n");
                }
                break;
            case 3:
                printf("Enter name to remove: ");
                scanf("%s", name);
                remove_node(name);
                break;
            case 4:
                view();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
