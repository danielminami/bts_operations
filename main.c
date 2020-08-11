#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLUSH stdin=freopen(NULL,"r",stdin)

#define MAX_LEN 20

typedef struct data {
    int number;
    char name[MAX_LEN];
} node_data_t;

typedef struct node {
    node_data_t data;
    struct node *left;
    struct node *right;
} tree_node_t;

//this function should create and return an array of five different employees. 
//You should hardcode the employees data in the function (e.g. no need to interact with the user)
node_data_t* populateEmployeesData();

//this function is supposed to take an array of struct (node_data_t) as input and 
//create a BST based of this array. The function should return a pointer to the root of the BST
tree_node_t* createTreeFromArray(node_data_t *employeesData); 

// this function should create a BST node that holds one employee. 
// This function should be called inside addEmployee function
tree_node_t* createEmployeeNode(int number, char name[MAX_LEN]);   

// function to display the employees data (in order).
void printAllEmployees(tree_node_t* root); 

// this function should and insert an employee node into the BST. 
//node is supposed to be created by createEmployeeNode function. 
//The function should print a message if an employee with the same number 
//exists in the BST (duplicates aren't allowed)
void addEmployee(tree_node_t* root, tree_node_t* employeeNode);  

// this function should search and return an employee node with specific number. 
//If not found, it should return null.
tree_node_t* findEmployeeByNumber(tree_node_t* root, int number);  

// this function should search and return an employee node with specific name. 
//If no fount, it should return null. The function should return an array of 
//pointers to all the tree nodes where the name is equal to the parameter passed to the function
tree_node_t* findEmployeeByName(tree_node_t* root, char name[MAX_LEN]);      

// this function should updated the name of an employee in the tree. number 
// parameter is used to find the employee, newName is the new name that should be assigned to the employee
void updateEmployeeName(tree_node_t* root, int number, char newName[MAX_LEN]); 

//// this function should updated the number of an employee in the tree. number 
// parameter is used to find the employee, newNumber is the new number that 
// should be assigned to the employee. When updating the number of a node the 
// tree should be changed (as the location of the node would be changed to 
// maintain thre BST structure). It would be easier to remove the node 
//(using removeEmployee function) and re-insert it in the tree (using addEmployee function)
void updateEmployeeNumber(tree_node_t* root, int number, int newNumber); 

// this function should remove a node from the tree. 
//Check out the deletion algorithm here: 
// http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete2.html
void removeEmployee(tree_node_t* root, int number); 

int main() {

    node_data_t *employeesData = populateEmployeesData();
    tree_node_t* root = createTreeFromArray(employeesData);
    printf("The employees list:\n");
    printAllEmployees(root);

    addEmployee(root, createEmployeeNode(123,"alexandra"));
    printf("\n\nThe employees list after adding Alexandra:\n");
    printAllEmployees(root);

    if(findEmployeeByNumber(root,234) !=NULL)
        printf("An employee with the number 234 exists in the tree\n");
    else
        printf("An employee with the number 234 doesn't exist in the tree\n");

    if(findEmployeeByName(root,"alexandra") !=NULL)
        printf("An employee with the name alexandra exists in the tree\n");
    else
        printf("An employee with the name alexandra doesn't exist in the tree\n");

    updateEmployeeName(root, 123, "Alex");
    printf("\n\nThe employees list after changing Alexandra name:\n");
    printAllEmployees(root);
    
    updateEmployeeNumber(root, 123, 321);
    printf("\n\nThe employees list after updaing Alex's number:\n");
    printAllEmployees(root);

    removeEmployee(root, 321);
    printf("\n\nThe employees list after removing Alex :\n");
    printAllEmployees(root);

}

node_data_t* populateEmployeesData() {
    
    node_data_t* arr = (node_data_t*) malloc(sizeof(node_data_t) * 5);
    
    node_data_t emp1 = {500, "James Logan"};
    node_data_t emp2 = {892, "Scott Summers"};
    node_data_t emp3 = {290, "Jean Grey"};
    node_data_t emp4 = {999, "Charles Xavier"};
    node_data_t emp5 = {119, "Henry McCoy"};

    arr[0]=emp1;
    arr[1]=emp2;
    arr[2]=emp3;
    arr[3]=emp4;
    arr[4]=emp5;
    
    return arr;
}

tree_node_t* createTreeFromArray(node_data_t *employeesData) {
    
    tree_node_t* root = NULL;
    tree_node_t* current = root;
    for (int i=0; i<5; i++) {
        current = root;
        tree_node_t* newNode = (tree_node_t*) malloc(sizeof(tree_node_t));
        newNode->data = employeesData[i];
        newNode->left = NULL;
        newNode->right = NULL;
        if (root == NULL) {
            root = newNode;
        } else {
            while (current != NULL) {
                if (newNode->data.number < current->data.number) {
                    if (current->left == NULL) {
                        current->left = newNode;
                        break;
                    } else {
                        current = current->left;
                    }
                } else if (newNode->data.number > current->data.number) {
                    if (current->right == NULL) {
                        current->right = newNode;
                        break;
                    } else {
                        current = current->right;
                    }
                } else {
                    break;
                }
            }
        }
    }
    return root;
}

tree_node_t* createEmployeeNode(int number, char name[MAX_LEN]) {
    
    tree_node_t* newNode = (tree_node_t*) malloc(sizeof(tree_node_t));
    newNode->data.number = number;
    strcpy(newNode->data.name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
    
}

void addEmployee(tree_node_t* root, tree_node_t* employeeNode) {

    tree_node_t* current = root;
        if (root == NULL) {
            root = employeeNode;
        } else {
            while (current != NULL) {
                if (employeeNode->data.number < current->data.number) {
                    if (current->left == NULL) {
                        current->left = employeeNode;
                        break;
                    } else {
                        current = current->left;
                    }
                } else if (employeeNode->data.number > current->data.number) {
                    if (current->right == NULL) {
                        current->right = employeeNode;
                        break;
                    } else {
                        current = current->right;
                    }
                } else {
                    printf("Error: this employee number is duplicated.");
                    break;
                }
            }
        }
}

void printAllEmployees(tree_node_t* root) {
    if (root != NULL) {
        printAllEmployees(root->left);
        printf("%d - %s\n", root->data.number, root->data.name);
        printAllEmployees(root->right);
    }
}

tree_node_t* findEmployeeByNumber(tree_node_t* root, int number) {
    
    if(root==NULL || root->data.number == number) return root;
    
    if(number < root->data.number)
        findEmployeeByNumber (root->left, number);
    else 
        findEmployeeByNumber (root->right, number);

}

tree_node_t* findEmployeeByName(tree_node_t* root, char name[MAX_LEN]) {
    
    if(root==NULL || strcmp(root->data.name, name) == 0) return root;
    
    if(strcmp(root->data.name, name) < 0)
        findEmployeeByName (root->left, name);
    else 
        findEmployeeByName (root->right, name);
} 

void updateEmployeeName(tree_node_t* root, int number, char newName[MAX_LEN]) {
    tree_node_t* emp = findEmployeeByNumber(root, number);
    if (emp == NULL) { 
        printf("Error: this employee number not found.");
        return;
    }
    strcpy(emp->data.name, newName);
}

void updateEmployeeNumber(tree_node_t* root, int number, int newNumber) {
    
    tree_node_t* emp = findEmployeeByNumber(root, number);
    if (emp == NULL) { 
        printf("Error: this employee number not found.");
        return;
    }
    
    char name[MAX_LEN];
    strcpy(name, emp->data.name);
    removeEmployee(root, number);
    addEmployee(root, createEmployeeNode(newNumber, name));
}

void removeEmployee(tree_node_t* root, int number) {
    tree_node_t* p = findEmployeeByNumber(root, number);
    tree_node_t* successor = p->right;
    
    if (successor != NULL) {
        while (successor->left != NULL) {
            successor = successor->left;
        }
        p->data = successor->data;
        
        tree_node_t* parent = p->right;
        tree_node_t* current = parent;
        
        if (successor->right == NULL) {
            p->right = NULL;
        } else {        
            while (current != NULL) {
                if (current->data.number == successor->data.number) {
                    parent->left = successor->right;
                    break;
                } else if (current->data.number > successor->data.number) {
                    parent = current;
                    current = current->left;
                } else if (current->data.number < successor->data.number) {
                    parent = current;
                    current = current->right;
                }
            }
        }
        
        if (parent != NULL) {
            while (parent->data.number != successor->data.number) {
                parent = parent->left;
            }
        } 
        
    } else {
        tree_node_t* current = root;
        tree_node_t* parent = root;
        int control = 0;
        while (current != NULL) {
            if (current->data.number == number) {
                if  (control == 0) parent->left = NULL;
                else parent->right = NULL;
                break;
            } else if (current->data.number > number) {
                parent = current;
                control = 0;
                current = current->left;
            } else if (current->data.number < number) {
                parent = current;
                control = 1;
                current = current->right;
            }
        }
    }
} 