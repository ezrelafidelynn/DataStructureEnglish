#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tree {
    int value;
    Tree *left, *right;
    int height;
} *root = NULL;

struct Tree* createNewNode(int value) {
    struct Tree* node = (struct Tree*)malloc(sizeof(Tree));
    node->value = value;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

int height(struct Tree* curr) {
    if (!curr) return 0;
    return curr->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(struct Tree* node) {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

struct Tree* leftRotate(struct Tree* curr) {
	//before
    struct Tree* currChild = curr->right;
    struct Tree* currChildChild = currChild->left;
    
    //before
    
    //curr
    //   \
    //    \
    //    currChild
    //    /
    //   /
    //CurrChildChild
    
    //after
    currChild->left = curr;
    curr->right = currChildChild;
    
    
    //      currChild
    //     /
    //    /
    //curr
    //   \
    //    \
    //     currChildChild
    
    //update the height
    curr->height = max(height(curr->left), height(curr->right)) + 1;
    //update the child's height too
    currChild->height = max(height(currChild->left), height(currChild->right)) + 1;
    return currChild;
}

struct Tree* rightRotate(struct Tree* curr) {
	//before
    struct Tree* currChild = curr->left;
    struct Tree* currChildChild = currChild->right;
    
    
    //       curr
    //     /
    //   /
    // currChild
    //  \
    //   \
    //    CurrChildChild
    
    //after
    currChild->right = curr;
    curr->left = currChildChild;
    
    //currChild
    //   \
    //    \
    //    curr
    //    /
    //   /
    //CurrChildChild
    
    curr->height = max(height(curr->left), height(curr->right)) + 1;
    currChild->height = max(height(currChild->left), height(currChild->right)) + 1;
    return currChild;
}

struct Tree* push(struct Tree* curr, int value) {
	//recursive case to push it until it will go to !curr and createnew node
    if (!curr) {
        curr = createNewNode(value);
    } else if (value != curr->value) {
        if (value < curr->value) curr->left = push(curr->left, value);
        else curr->right = push(curr->right, value);
    }
    
    //update the height
    curr->height = max(height(curr->left), height(curr->right)) + 1;
    //get the balance
    int balance = getBalance(curr);
    
    //rebalance
    if (balance > 1 && value < curr->left->value) {//LL
        return rightRotate(curr);
    }
    if (balance < -1 && value > curr->right->value) {//RR
        return leftRotate(curr);
    }
    if (balance > 1 && value > curr->left->value) {//LR
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if (balance < -1 && value < curr->right->value) {//RL
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

struct Tree* findMax(struct Tree* curr) {
    if (curr == NULL) return NULL;
    if (curr->right == NULL) return curr;
    return findMax(curr->right);
}

struct Tree* pop(struct Tree* curr, int value) {
    if (curr == NULL) return NULL;
    if (value > curr->value) {
        curr->right = pop(curr->right, value);//only for placement for curr/parent
    } else if (value < curr->value) {
        curr->left = pop(curr->left, value);//only for placement for curr/parent
    } else {
        if (curr->left == NULL && curr->right == NULL) {//no child
            free(curr);
            return NULL;
        } else if (curr->left == NULL || curr->right == NULL) {//one child
            struct Tree* temp = (curr->left) ? curr->left : curr->right;
            free(curr);
            return temp;
        } else {//two child
            struct Tree* temp = findMax(curr->left);
            curr->value = temp->value;
            curr->left = pop(curr->left, temp->value);
        }
    }
    
    //update the height
    curr->height = max(height(curr->left), height(curr->right)) + 1;
    
	//get the balance
    int balance = getBalance(curr);
    
    //rebalance
    if (balance > 1 && value < curr->left->value) {//LL
        return rightRotate(curr);
    }
    if (balance < -1 && value > curr->right->value) {//RR
        return leftRotate(curr);
    }
    if (balance > 1 && value > curr->left->value) {//LR
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if (balance < -1 && value < curr->right->value) {//RL
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

void view(struct Tree* curr) {//inorder print style
    if (!curr) return;
    if (curr->left != NULL) view(curr->left);
    printf("%d ", curr->value);
    if (curr->right != NULL) view(curr->right);
}

void preOrder(struct Tree* curr) {
    if (!curr) return;
    printf("%d ", curr->value);
    if (curr->left != NULL) preOrder(curr->left);
    if (curr->right != NULL) preOrder(curr->right);
}

void postOrder(struct Tree* curr) {
    if (!curr) return;
    if (curr->left != NULL) postOrder(curr->left);
    if (curr->right != NULL) postOrder(curr->right);
    printf("%d ", curr->value);
}

void printIndented(struct Tree* curr, int level) {//feel free to test this function out although it wont look like a tree
    if (curr == NULL) {
        return;
    }
    level++;
    printIndented(curr->right, level);
    for (int i = 0; i < level - 1; i++) {
        printf("    ");
    }
    printf("%d\n", curr->value, getBalance(curr));
    printIndented(curr->left, level);
}

void viewAVLTree(struct Tree* root) {
    if (root == NULL) {
        printf("AVL Tree is empty.\n");
        return;
    }
    printf("AVL Tree (in tree structure):\n\n");
    printIndented(root, 0);
}

int treeSize = 0;

void menu() {
    int choice, value, size;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. View Tree\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the number of values to insert: ");
                scanf("%d", &size);
                treeSize += size;
                for (int i = 0; i < size; i++) {
                    printf("Enter value %d: ", i + 1);
                    scanf("%d", &value);
                    root = push(root, value);
                }
                break;
            case 2:
                printf("Enter the number of values to delete: ");
                scanf("%d", &size);
                if (size > treeSize) {
                    printf("Invalid number of values to delete. There are only %d values in the tree.\n", treeSize);
                    break;
                }
                treeSize -= size;
                for (int i = 0; i < size; i++) {
                    printf("Enter value to delete %d: ", i + 1);
                    scanf("%d", &value);
                    root = pop(root, value);
                }
                break;
            case 3:
                if (treeSize == 0) {
                    printf("The tree is empty.\n");
                } else {
                    viewAVLTree(root);
                }
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
