// 2021MCB1181
// Jignesh Agrawal

#include<stdio.h>
#include<stdlib.h>

// linked list
struct node
{
    int data;
    struct node *next;
};

typedef struct node node;

// function to create a new node
node *newNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// create linked list of desired length
/*
Example:
         1->2->3->4->5->6->7->8->9
                     ^           |
                     |           |
                     -------------
*/
node* Createlinkedlist(int distance,int edge){
    // distance is the length of the linked list before the loop starts
    node *head = newNode(1);
    node *temp = head;
    for (int i = 2; i < distance+2; i++)
    {
        /* code */ 
        temp->next = newNode(i);
        temp = temp->next;
    }
    node* temp2= temp;
    for (int i = distance+2; i < distance+edge+1; i++)
    {
        /* code */
        temp2->next = newNode(i);
        temp2 = temp2->next;
    }
    // creating a loop in the linked list if edge is not 0
    if (edge != 0)
        temp2->next = temp;   
    return head;
}

// print the linked list
void printList(node *head)
{
    node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

// Checks if there are cycles in the code or not
void DetectCycle (node* head){
    // creating 2 pointers 1 fast and 1 slow
    node* slow = head;
    node* fast = head;
    do {
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast && fast != NULL && fast->next != NULL); 
    // if pointer is NULL then no loops
    if (fast == NULL || fast->next == NULL)
    {
        printf("The linked list contains no cycle");
        return;
    }
    else
    {
        printf("Cycle detected");
    }
}

int DetectCyclelength(node* start){
    // Takes cycles start and returns the loop length
    node* temp = start;
    int c=0; // counts the no.of elements in the loop
    do
    {
        temp = temp->next;
        c++;
        printf("%d",c);
        if (temp == NULL){
            return 0;
        }
    }while (temp!=start);
    return c;
}

// Tells the no.of elements before the loop starts and tells the no.of elements in the loop as well
void DetectCycleStart (node* head){
    node* slow = head;
    node* fast = head;
    do {
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast && fast != NULL && fast->next != NULL); 

    if (fast == NULL || fast->next == NULL)
    {
        printf("No Cycle");
    }
    else
    {
        int c=0; // counting the no.of elements before the loop start
        slow = head;
        while (slow != fast){
            slow = slow->next;
            fast = fast->next;
            c++;
        }
        printf("The linked list has a cycle of length %d and the distance of the start node of the cycle from the head of the linked list is %d",DetectCyclelength(slow),c);

    }
}



int main(){
    printf("Press Y for linked list with a cycle and N for without cycles: ");
    char ch;
    scanf("%c",&ch);
    if (ch =='N'){
        printf("Enter the size (number of edges) of linked list without cycle: ");
        int d;
        scanf("%d",&d);
        node * head = Createlinkedlist(d,0);
        DetectCycle(head);
        // printList(head);
    }
    else if (ch == 'Y'){
        printf("Enter the length of cycle in the linked list: ");
        int d,e;
        scanf("%d",&d);
        printf("Enter the distance (number of edges) of the start node of the cycle from the head of the linked list: ");
        scanf("%d",&e);
        node * head = Createlinkedlist(d,e);
        DetectCycleStart(head);
    }
    else{
        printf("Invalid input");
    }
    
    // node* head = Createlinkedlist(2,2);
    
    return 0;
}