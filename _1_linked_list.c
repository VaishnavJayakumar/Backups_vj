#include <stdio.h>
#include <stdlib.h>

void clear_terminal() {
    // \e[1;1H moves the cursor to row 1, column 1
    // \e[2J clears the entire screen
    printf("\e[1;1H\e[2J");
}

typedef struct node{
    int data;
    struct node* link;
}node;

node* createnode(int given_value){
    node* n = (node*)malloc(sizeof(node));

    if(n == NULL){printf("createnode failed");exit(1);}

    n->data = given_value;
    n->link = NULL;
    return n;
};

typedef struct{ //linked list
    node* head;
}linkedlist;

linkedlist* createlist() {
    linkedlist* L = (linkedlist*)malloc(sizeof(linkedlist));
    
    if(L == NULL){printf("createlist failed\n");exit(1);}

    L->head = NULL; // Safely initialize
    return L;
}


void appendnode(linkedlist* L, int given_value){
    node* new_node = createnode(given_value);

    if (L->head == NULL) {
        L->head = new_node;
        return;
    }

    node* curr = L->head;
    while (curr->link != NULL) {
        curr = curr->link;
    }
    curr->link = new_node;
}

void insertnode(linkedlist* L, int given_value,int pos){
    node* new_node = createnode(given_value);

    if (pos == 0) {
        new_node->link = L->head;
        L->head = new_node;
        return;
    }

    node* curr = L->head;
    for (int i = 0; i < pos - 1 && curr != NULL; i++) {
        curr = curr->link;
    }
    
    if (curr == NULL) {
        printf("Position out of bounds\n");
        free(new_node);
        return;
    }

    new_node->link = curr->link;
    curr->link = new_node; 
    printf("Inserted %d at position %d\n",given_value,pos);
    
}

void popnode(linkedlist* L){
    if (L->head == NULL) {
        printf("No elements to pop\n");
        return;
    }

    if (L->head->link == NULL) {
        printf("Popped value: %d", L->head->data);
        free(L->head);
        L->head = NULL;
        return;
    }

    node* curr = L->head;
    while (curr->link->link != NULL) {
        curr = curr->link;
    }
    
    free(curr->link);
    curr->link = NULL;
}

void deletenode(linkedlist* L,int pos){
    if (L->head == NULL) {
        printf("No elements to delete");
        return;
    }

    if (pos == 0) {
        node* temp = L->head;
        L->head = L->head->link;
        free(temp);
        printf("element index 0 deleted");
        return;
    }

    node* prev = L->head;
    node* curr = prev->link;
    for (int i = 0; i < pos - 1 && curr != NULL; i++) {
        prev = prev->link;
        curr = curr->link;
    
    }
    
    if(curr == NULL){
        printf("Invalid position %d, node does not exist",pos);
        return;
        }
    
    prev->link = curr->link;
    free(curr);
    printf("element index %d deleted",pos);
}


void deletevalue(linkedlist* L, int val){
    int flag = 0;
    int pos = 0;

    if (L->head == NULL){
        printf("\nEmpty linked list\n");
        return;
    }

    if (L->head->data == val){
        node* temp = L->head;
        L->head = temp->link;
        free(temp);
        flag = 1;
        printf("element index 0 deleted");
        if(L->head == NULL) return;
    }

    node* prev = L->head;
    node* curr = prev->link;

    while (curr != NULL){ 
        pos++;
        if(curr->data == val){
            prev->link = curr->link;
            free(curr);
            curr = prev->link;
            printf("\nelement index %d deleted",pos);
            flag = 1;
        }else{
            prev = curr;
            curr = prev->link;
        }
    }

    if(!flag){
        printf("No elements are deleted");
    }
    return;

}

void display(linkedlist* L){

    if (L->head == NULL) {
        printf("\nEmpty linked list\n");
        return;
    }

    node* curr = L->head;
    printf("\nll node : ");
    while (curr != NULL) { 
        printf(" %d -->", curr->data);
        curr = curr->link;
    }

    printf("|<\n");
}

int main(){

    linkedlist* A = createlist();

    appendnode(A, 1);
    appendnode(A, 2);
    appendnode(A, 3);
    appendnode(A, 4);
    appendnode(A, 5);
    appendnode(A, 6);
    appendnode(A, 7);

    int opcode = 0;
    int operand = 0;
    int operand2 = 0;

    while(1){
    display(A);
    printf("\nSelect action : \
        \n1 append\
        \n2 insert\
        \n3 pop \
        \n4 delete by position\
        \n5 delete by value\
        \n6 exit\
        \n\t\t:");
    scanf("%d",&opcode);

    switch (opcode)
    {
    case 1:
        printf("\nnewnode value:");
        scanf("%d",&operand);

        clear_terminal();

        appendnode(A,operand);

        break;
    
    case 2:
        printf("\nnewnode value:");
        scanf("%d",&operand);
        printf("\nnewnode position:");
        scanf("%d",&operand2);

        clear_terminal();

        insertnode(A,operand,operand2);

        break;

    case 3:
        clear_terminal();

        popnode(A);

        break;
    
    case 4:
        printf("\ndeleting node position:");
        scanf("%d",&operand);

        clear_terminal();

        deletenode(A,operand);

        break;
    
    case 5:
        printf("\ndeleting node of value:");
        scanf("%d",&operand);

        clear_terminal();

        deletevalue(A,operand);

        break;

    case 6:
        clear_terminal();

        printf("\nprogram exiting\n");


        exit(0);
        break;

    default:
        clear_terminal();
        printf("\nInvalid option");
        break;
    }

    }

    printf("\n");
    return 0;
}