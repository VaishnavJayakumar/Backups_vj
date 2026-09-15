#include <stdio.h>
#include <stdlib.h>


void clear_terminal() {printf("\e[1;1H\e[2J");}

typedef struct node{
    int data;
    struct node* prev;
    struct node* next;
}node;

node* createnode(int given_value){
    node* n = (node*)malloc(sizeof(node));

    if(n == NULL){printf("createnode failed");exit(1);}

    n->data = given_value;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

typedef struct{node* head;}linkedlist;

linkedlist* createlist() {
    linkedlist* L = (linkedlist*)malloc(sizeof(linkedlist));

    if(L == NULL){printf("createlist failed\n");exit(1);}

    L->head = NULL;
    return L;
}

void prependnode(linkedlist* L, int given_value){
    node* new_node = createnode(given_value);

    new_node->next = L->head;
    new_node->prev = NULL;

    if (L->head != NULL) {
        L->head->prev = new_node;
    }

    L->head = new_node;
}

void appendnode(linkedlist* L, int given_value){
    node* new_node = createnode(given_value);

    if (L->head == NULL) {
        L->head = new_node;
        return;
    }

    node* curr = L->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    new_node->prev = curr;
    curr->next = new_node;
}

void insertnode(linkedlist* L, int given_value, int pos){
    if (pos < 0) {
        printf("Position out of bounds\n");
        return;
    }

    if (pos == 0) {
        prependnode(L, given_value);
        printf("Inserted %d at position %d\n", given_value, pos);
        return;
    }

    node* curr = L->head;
    for (int i = 0; i < pos - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    node* new_node = createnode(given_value);

    new_node->next = curr->next;
    new_node->prev = curr;

    if (curr->next != NULL) {          /* not inserting at the tail */
        curr->next->prev = new_node;
    }
    curr->next = new_node;

    printf("Inserted %d at position %d\n", given_value, pos);
}

void popnode(linkedlist* L){
    if (L->head == NULL) {
        printf("No elements to pop");
        return;
    }

    if (L->head->next == NULL) {
        printf("Popped value: %d", L->head->data);
        free(L->head);
        L->head = NULL;
        return;
    }

    node* curr = L->head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }

    printf("Popped value: %d", curr->next->data);
    free(curr->next);
    curr->next = NULL;
}

void deletenode(linkedlist* L, int pos){
    if (L->head == NULL) {
        printf("No elements to delete");
        return;
    }

    if (pos < 0) {
        printf("Invalid position %d, node does not exist", pos);
        return;
    }

    node* curr = L->head;
    for (int i = 0; i < pos && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Invalid position %d, node does not exist", pos);
        return;
    }

    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    } else {
        L->head = curr->next;          /* deleting the head */
    }

    if (curr->next != NULL) {
        curr->next->prev = curr->prev; /* not deleting the tail */
    }

    free(curr);
    printf("element index %d deleted", pos);
}


void deletevalue(linkedlist* L, int val){
    int flag = 0;
    int pos = 0;

    if (L->head == NULL){
        printf("\nEmpty linked list\n");
        return;
    }

    node* curr = L->head;

    while (curr != NULL){
        node* nextnode = curr->next;

        if (curr->data == val){
            if (curr->prev != NULL) {
                curr->prev->next = curr->next;
            } else {
                L->head = curr->next;
            }

            if (curr->next != NULL) {
                curr->next->prev = curr->prev;
            }

            free(curr);
            printf("\nelement index %d deleted", pos);
            flag = 1;
        }

        curr = nextnode;
        pos++;
    }

    if (!flag){
        printf("No elements are deleted");
    }
}

void display(linkedlist* L){

    if (L->head == NULL) {
        printf("\nEmpty linked list\n");
        return;
    }

    node* curr = L->head;
    printf("\nll state: >|");
    while (curr != NULL) {
        printf(" <--> %d", curr->data);
        curr = curr->next;
    }

    printf(" <--> |<\n");
}

int main(){

    linkedlist* A = createlist();

    int opcode = 0;
    int operand = 0;
    int operand2 = 0;

    while(1){
    display(A);
    printf("\nSelect action : \
        \n1 insert node at beginning\
        \n2 insert node at a position\
        \n3 insert node at end\
        \n4 delete node at a position\
        \n5 delete node by a particular value\
        \n6 exit\
        \n\t\t:");

    if (scanf("%d",&opcode) != 1) {
        clear_terminal();
        printf("\nInvalid input\n");
        exit(1);
    }

    switch (opcode)
    {
    case 1:
        printf("\nnewnode value:");
        scanf("%d",&operand);

        clear_terminal();

        prependnode(A,operand);

        break;

    case 2:
        printf("\nnewnode position:");
        scanf("%d",&operand2);

        printf("\nnewnode value:");
        scanf("%d",&operand);

        clear_terminal();

        insertnode(A,operand,operand2);

        break;

    case 3:
        printf("\nnewnode value:");
        scanf("%d",&operand);

        clear_terminal();

        appendnode(A,operand);

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