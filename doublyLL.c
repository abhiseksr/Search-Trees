/*Doubly Linked list implementation in C
Author - Abhishek Kumar */

#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *prev;
    struct node *next;
};

typedef struct node node;

int size;

node * create(int value){
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = value;
    newnode->prev = 0;
    newnode->next = 0;
    size++;
    return newnode;
}

void traverse(node * head){
    while (head!=0){
        printf("%d ",head->data);
        head = head->next;
    }
    printf("\n");
}

node * insertbeg(node *head, int value){
    node * newnode = create(value);
    newnode->next = head;
    head->prev = newnode;
    return newnode;
}

void insertend(node *head,int value){
    node * newnode = create(value);
    while (head->next!=0){
        head = head->next;
    }
    head->next = newnode;
    newnode->prev = head;
}

void insertpos(node *head, int pos, int value){
    if (pos==1) printf("Use insertbeg instead!\n");
    else if (pos==size+1) printf("Use insertend instead!\n");
    else if (pos<1 || pos>size+1){
        printf("Invalid position!\n");
    }
    else{
        node * newnode = create(value);
        int idx = 1;
        while (idx<pos-1){
            head = head->next;
            idx++;
        }
        newnode->prev  = head;
        newnode->next = head->next;
        head->next = newnode;
        newnode->next->prev = newnode;
    }
}

node * delbeg(node * head){
    if (size==1){
        printf("Cannot be deleted!\n");
        return head;
    }
    node *ptr = head->next;
    free(head);
    size--;
    return ptr;
}

void delend(node * head){
    if (size==1){
        printf("Cannot be deleted!\n");
        return;
    }
    while (head->next->next!=0){
        head = head->next;
    }
    node * temp = head->next;
    head->next = 0;
    free(temp);
    size--;
}

void delpos(node *head,int pos){
    if (pos==1) printf("Cannot be deleted!\n");
    else if (pos==size) printf("Use deltend instead!\n");
    else if (pos<1 || pos>size){
        printf("Invalid position!\n");
    }
    else{
        int idx = 1;
        while (idx<pos){
            head = head->next;
            idx++;
        }
        node * temp = head;
        head->prev->next = head->next;
        head->next->prev = head->prev;
        free(temp);
        size--;
    }
}

void reversetraverse(node * head){
    if (head!=0){
        reversetraverse(head->next);
        printf("%d ",head->data);
    }
}

int main(){

    printf("Menu\n2. traverse\n4. reversetraverse\n5. insertbeg\n6. insertend\n"
    "7. insertpos\n8. delbeg\n9. delend\n10. delpos\n\n");
    int choice, pos ,value;
    node *head = create(1);
    while (1){
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 2:
            traverse(head);
            break;
        case 4:
            reversetraverse(head);
            printf("\n");
            break;
        case 5:
            printf("Enter value to be inserted: ");
            scanf("%d", &value);
            head  = insertbeg(head, value);
            break;
        case 6:
            printf("Enter value to be inserted: ");
            scanf("%d", &value);
            insertend(head, value);
            break;
        case 7:
            printf("Enter position and value to be inserted: ");
            scanf("%d%d",&pos, &value);
            insertpos(head, pos,value);
            break;
        case 8:
            head = delbeg(head);
            break;
        case 9:
            delend(head);
            break;
        case 10:
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            delpos(head,pos);
            break;
        default:
            break;
        }
    }
    return 0;
}