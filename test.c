#include <stdio.h>
#include <stdlib.h>

void clear_terminal() {
    // \e[1;1H moves the cursor to row 1, column 1
    // \e[2J clears the entire screen
    printf("\e[1;1H\e[2J");
}

typedef struct node{
    int exp;
    int cof;
    struct node* link;
}node;

node* createnode(int given_exp, int given_cof){
    node* n = (node*)malloc(sizeof(node));

    if(n == NULL){printf("createnode failed");exit(1);}

    n->exp = given_exp;
    n->cof = given_cof;
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


linkedlist* mergelist(linkedlist* LA,linkedlist* LB){

    if(LA->head == NULL){
        LA->head = LB->head;
        free(LB);
        return LA;
    }

    node* curr = LA->head;
    while(curr->link!=NULL){
        curr = curr->link;
    }

    curr->link = LB->head;
    free(LB);

    return LA;
}

void insertionSortList(linkedlist* L) {
    if (!L || !L->head || !L->head->link) {
        return;
    }

    node* sorted = NULL; 
    node* curr = L->head;  

    while (curr != NULL) {
        node* next_node = curr->link; 
        if (sorted == NULL || curr->exp < sorted->exp) {
            curr->link = sorted;
            sorted = curr;
        }
        else {
            node* search = sorted;
            while (search->link != NULL && search->link->exp < curr->exp) {
                search = search->link;
            }
            curr->link = search->link;
            search->link = curr;
        }

        curr = next_node; 
    }
    
    L->head = sorted;
}

void reduce(linkedlist* L) {
    if (!L || !L->head) {
        return;
    }

    node* curr = L->head;
    while (curr != NULL && curr->link != NULL) {
        if (curr->exp == curr->link->exp) {
            curr->cof += curr->link->cof;
            node* temp = curr->link;
            curr->link = curr->link->link;
            free(temp);
        } else {
            curr = curr->link;
        }
    }
}

node* promptnode(){
    node* n = (node*)malloc(sizeof(node));

    int given_exp, given_cof;
    printf("\nEnter exponent: ");
    scanf("%d", &given_exp);
    printf("\nEnter coefficient: ");
    scanf("%d", &given_cof);

    if(n == NULL){printf("createnode failed");exit(1);}

    n->exp = given_exp;
    n->cof = given_cof;
    n->link = NULL;
    return n;
};

char printnode(node* n){
    if(n == NULL){
        printf("[Node is NULL]\n");
        return '\0';
    }
    printf("[%dx^%d]", n->cof, n->exp);
    return '\0';
}

void appendnode(linkedlist* L, node* new_node){
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

void insertnode(linkedlist* L, node* new_node, int pos){
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
    printf("Inserted %c at position %d\n", printnode(new_node), pos);
    
}

void popnode(linkedlist* L){
    if (L->head == NULL) {
        printf("No elements to pop\n");
        return;
    }

    if (L->head->link == NULL) {
        printf("Popped %c", printnode(L->head));
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
        printf("element %c of index 0 deleted", printnode(temp));
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
    printf("element %c of index %d deleted", printnode(curr), pos);
}

void display(linkedlist* L){

    if (L->head == NULL) {
        printf("\nEmpty linked list\n");
        return;
    }

    node* curr = L->head;
    printf("\nll node : ");
    while (curr != NULL) { 
        printf("%c+ ", printnode(curr));
        curr = curr->link;
    }

    printf("|<\n");
}


linkedlist* copylist(linkedlist* L) {
    linkedlist* new_list = createlist();
    node* curr = L->head;

    while (curr != NULL) {
        node* new_node = createnode(curr->exp, curr->cof);
        appendnode(new_list, new_node);
        curr = curr->link;
    }

    return new_list;
}


int main(){

    linkedlist* A = createlist();
    linkedlist* B = createlist();

    int opcode = 0;
    int operand = 0;
    int operand2 = 0;
    node* opnode = NULL;

    while(1){
    display(A);
    printf("\nSelect action : \
        \n1 append to A\
        \n2 insert to A\
        \n3 pop from A\
        \n4 delete from A\
        \n5 sort A\
        \n6 reduce A\
        \n9 exit\
        \n\t\t:");
    scanf("%d",&opcode);

    switch (opcode)
    {
    case 1:
        opnode = promptnode();

        clear_terminal();

        appendnode(A,opnode);

        break;
    
    case 2:
        opnode = promptnode();

        printf("\nnewnode position:");
        scanf("%d",&operand2);

        clear_terminal();

        insertnode(A,opnode,operand2);

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
        clear_terminal();
        insertionSortList(A);
        printf("\nList A sorted\n");
        break;
    
    case 6:
        clear_terminal();
        reduce(A);
        printf("\nList A reduced\n");
        break;
    
    case 9:
        clear_terminal();

        printf("\nprogram exiting\n");

        exit(0);
        break;

    default:
        clear_terminal();
        printf("\nInvalid option");
        break;
    }

    printf("\n");
    return 0;
}
