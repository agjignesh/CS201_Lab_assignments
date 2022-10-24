#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int m=11;

// doubly linked list
struct linkedlist
{
    int data;
    struct linkedlist* next;
    struct linkedlist* prev;
};

typedef struct linkedlist linkedlist;

linkedlist* insert_linkedlist(linkedlist* head,int x){
    // just inserts in a doubly linked list
    // inserts at the start
    linkedlist* newnode = malloc(sizeof(linkedlist));
    newnode->data = x;
    newnode->prev=NULL;
    newnode->next=head;

    if (head!=NULL){
        head->prev = newnode;
    }
    return newnode;
}

linkedlist* delete_linkedlist(linkedlist* head,int x){
    // x is the element that neeeds to be deleted from the linked list
    linkedlist* temp = head;
    while (temp!=NULL)
    {
        if (temp->data==x)
        {
            /* code */
            if (temp->prev!=NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            if (temp->next!=NULL)
                temp->next->prev = temp->prev;
            free(temp);
            return head;
        }
        temp = temp->next;
    }
}

int search_linkedlist(linkedlist* head, int x){
    // return 1 if element is found else return 0
    linkedlist* temp = head;
    while (temp!=NULL)
    {
        if (temp->data==x)
            return 1;
        temp = temp->next;
    }
    return 0;
}

struct hashtable{
    linkedlist** linkedlist_head;
};

typedef struct hashtable hashtable;

int hash_fxn(int k){
    // This is the hash Function used it can be modified to any hash fxn of your choice
    if (k<0)
    {
        return((m-(-k)%m));
    }
    return (k%m);
    
}

hashtable* make_table(){
    // creates an empty hash table
    hashtable* table;
    table = malloc(sizeof(hashtable));
    table->linkedlist_head = malloc(m*sizeof(linkedlist*));
    // printf("hi");
    for (int i = 0; i < m; i++)
    {
        table->linkedlist_head[i] = NULL;
    }
    return table;
}

void insert_hashtable(hashtable* table,int k){
    table->linkedlist_head[hash_fxn(k)] = insert_linkedlist(table->linkedlist_head[hash_fxn(k)],k);
}

void delete_hashtable(hashtable* table, int k){
    table->linkedlist_head[hash_fxn(k)] = delete_linkedlist(table->linkedlist_head[hash_fxn(k)],k);
}

void search_hashtable(hashtable* table, int k){
    int found = search_linkedlist(table->linkedlist_head[hash_fxn(k)],k);
    if (found)
        printf("\nsearched element %d is found in slot number %d\n",k,hash_fxn(k));
    else
        printf("\nnot present\n");
}

void display_hashtable(hashtable* table){
    for (int i = 0; i < m; i++)
    {
        linkedlist* temp = table->linkedlist_head[i];
        printf("index %d: ",i);
        while (temp!=NULL){
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main(){
    hashtable* table = NULL;
    table = make_table();
    printf("Enter hash table size m: ");
    scanf("%d",&m);
    int choice = 5;
    do
    {
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Search");
        printf("\n4. Display");
        printf("\n5. Quit");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        int k;
        switch (choice)
        {
        case 1: 
            printf("\nEnter value to insert: ");
            scanf("%d",&k);
            insert_hashtable(table,k);
            break;
        case 2:
            printf("\nEnter value to delete: ");
            scanf("%d",&k);
            delete_hashtable(table,k);
            break;
        case 3:
            printf("\nenter the element to be searched: ");
            scanf("%d",&k);
            search_hashtable(table,k);
            break;
        case 4:
            display_hashtable(table);
            break;
        default:
            break;
        }
    }while (choice!=5);
    
    return 0;
}