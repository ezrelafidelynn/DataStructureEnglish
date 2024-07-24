#include <stdio.h>
#include <stdlib.h>

struct bstnode {
    int no;
    struct bstnode *l, *r;
    //l = left
    //r = right
};

struct bstnode *newNode(int value) {
    struct bstnode* temp = (struct bstnode*)malloc(sizeof(struct bstnode));
    temp->no = value;
    temp->l = temp->r = NULL;
    return temp;
}

struct bstnode *insertNode(struct bstnode* node, int value) {
    if (node == NULL) {
        return newNode(value);
    } else if (value < node->no) {//recursive case but pay attention to the left or right of the node
        node->l = insertNode(node->l, value);
    } else if (value > node->no) {//recursive case but pay attention to the left or right of the node
        node->r = insertNode(node->r, value);
    }
    return node;
}

void inorder(struct bstnode *root) {
    if (root != NULL) {
        inorder(root->l);
        printf("%d ", root->no);
        inorder(root->r);
    }
}

void preorder(struct bstnode *root) {
    if (root != NULL) {
        printf("%d ", root->no);
        preorder(root->l);
        preorder(root->r);
    }
}

struct bstnode *findMin(struct bstnode* root) {//the minimum is at the left side of the tree
    struct bstnode *curr = root;
    while (curr && curr->l != NULL) {
        curr = curr->l;
    }
    return curr;
}

struct bstnode *findMax(struct bstnode* root) {//the maximum is at the right side of the tree
    struct bstnode *curr = root;
    while (curr && curr->r != NULL) {
        curr = curr->r;
    }
    return curr;
}

struct bstnode* findNode(struct bstnode *root, int value) {
    if (root == NULL) {
        printf("No data found.\n");
        return NULL;
    }
    if (root->no == value) {
        return root;
    } else if (value < root->no) {//recursive again
        return findNode(root->l, value);
    } else {//recursive again
        return findNode(root->r, value);
    }
}

struct bstnode* deleteNode(struct bstnode* root, int data) {
    if (root == NULL) {
        printf("There's no data\n");
        return root;
    }

    if (data < root->no) {//recursive again
        root->l = deleteNode(root->l, data);
    } else if (data > root->no) {//recursive again
        root->r = deleteNode(root->r, data);
    } else {
        if (root->l == NULL) {//one child
            struct bstnode* temp = root->r;
            free(root);
            return temp;
        } else if (root->r == NULL) {//one child
            struct bstnode* temp = root->l;
            free(root);
            return temp;
        }

        struct bstnode* temp = findMin(root->r);//the minimum that has a right child
        root->no = temp->no;
        root->r = deleteNode(root->r, temp->no);//the right child is going to be called here
    }

    return root;
}

void menu() {
    printf("1. Insert into tree\n");
    printf("2. View contents\n");
    printf("3. View min and max\n");
    printf("4. Find\n");
    printf("5. Delete\n");
    printf("0. Exit\n");
}

int main() {
    struct bstnode *rootA = NULL;
    int value, choice;
    int findValue;
    
    do {
        menu();
        printf(">> ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Enter the number to insert into the tree: "); 
                scanf("%d", &value);
                getchar();
                rootA = insertNode(rootA, value);
                break;
            case 2:
                printf("Inorder traversal result: ");
                inorder(rootA);
                printf("\n");
                
                printf("Preorder traversal result: ");
                preorder(rootA);
                printf("\n");
                break;
            case 3: {
                struct bstnode* min = findMin(rootA);
                struct bstnode* max = findMax(rootA);
                if (min != NULL) printf("Min: %d\n", min->no);
                if (max != NULL) printf("Max: %d\n", max->no);
                break;
            }
            case 4: {
                printf("Enter the number to find: "); 
                scanf("%d", &findValue);
                getchar();
                struct bstnode* foundNode = findNode(rootA, findValue);
                if (foundNode != NULL) {
                    printf("Found: %d\n", foundNode->no);
                }
                break;
            }
            case 5: {
                printf("Enter the number to delete: "); 
                scanf("%d", &value);
                getchar();
                rootA = deleteNode(rootA, value);
                break;
            }
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Please enter a valid number\n");
        }
    } while (choice != 0);

    return 0;
}
