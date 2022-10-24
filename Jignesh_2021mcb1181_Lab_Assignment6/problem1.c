// Jignesh Agrawal
//2021MCB1181

#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int t=2;

struct node
{
    bool leaf; // if it is a leaf or not
    int n; // no.of keys
    int* key;
    struct node** pointer;
};

typedef struct node node;

int L_search(int* arr,int n,int k){ 
    for (int i = 0; i < n-1; i++)
    {
        if ((*(arr+i)<k) && (*(arr+i+1)>k))
        {
            return (i+1);
        }
    }
    if (arr[0]>k)
    {
        return 0;
    }
    else
    {
        return n;
    } 
}

node* new_node(int* arr,int n){
    node* newnode = malloc(sizeof(node));
    newnode->key = malloc((2*t-1)*sizeof(int));
    newnode->pointer = malloc((2*t)*sizeof(node*));
    for (int i = 0; i < n; i++)
    {
        *(newnode->key+i) = arr[i];
    }
    newnode->n = n;
    for (int i = 0; i < 2*t; i++)
    {
        /* code */
        *(newnode->pointer+i) = NULL;
    }
    newnode->leaf = true;
}

node* insert_key(node* root,int value,node* left,node* right){
    // insert only if the list empty
    int i =0;
    for (i; i<root->n; i++){
        if (*(root->key+i)>value)
        {
            break;
        }
    }
    for(int j = root->n; j>i; j--){
        *(root->key+j)=(root->key)[j-1];
        *(root->pointer+j+1)=(root->pointer)[j];
    }
    *(root->key+i) = value;
    *(root->pointer+i) = left;
    *(root->pointer+i+1) = right;
    root->n+=1;
    return root;
}

node* split(node* parent, node* child){
    // assume parent is empty
    node* right_newchild = new_node((child->key)+t,t-1);
    right_newchild->leaf = child->leaf;
    for (int i = 0; i < t; i++)
    {
        /* code */
        *(right_newchild->pointer+i) = (child->pointer)[i+t];
    }
    node* left_newchild = child;
    left_newchild->n = t-1;
    //printf("HI");
    if (parent == NULL)
    {
        parent = new_node((child->key)+t-1,1);
        parent->leaf = false;
        *(parent->pointer) = left_newchild;
        *(parent->pointer+1) = right_newchild;
    }
    else{
        parent = insert_key(parent,(child->key)[t-1],left_newchild,right_newchild);
    }
    return parent;
}

node* insert(node* parent,int value){
    if (parent==NULL)
    {
        int arr[1];
        *arr = value;
        parent = new_node(arr,1);
        return parent;
    }

    if (parent->n == 2*t-1)
    {
        //printf("Hi");
        parent = split(NULL,parent);
        //printf("%d",(parent->leaf));
        //printf("%d",(parent->pointer)[1]->key[0]);
        //printf("Hi");
    }
    if (parent->leaf)
    {
        //printf("hi");
        parent = insert_key(parent,value,NULL,NULL);
        return parent;
    }
    else
    {
        int index = L_search((parent->key),parent->n,value);
        //printf("%d",index);
        if ((parent->pointer)[index]->n == 2*t-1)
        {
            parent = split(parent,(parent->pointer)[index]);
            index = L_search((parent->key),parent->n,value);
        }
        *(parent->pointer+index) = insert(*(parent->pointer+index),value);
        return parent;
    }
}

int B_tree_height(node* root){
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int max = 0;
        for (int i = 0; i < root->n+1; i++)
        {
            int temp = B_tree_height((root->pointer)[i]);
            if (temp>max)
            {
                max = temp;
            }
        }
        return max+1;
    }
}

void B_tree_search(node* root,int value){
    if (root == NULL)
    {
        printf("NOT FOUND");
        return;
    }
    int Flag=0;
    for (int i = 0; i < root->n; i++)
    {
        /* code */
        if (*(root->key+i) == value)
        {
            Flag=1;
            break;
        }
        
    }
    if (Flag==1)
    {
        printf("Present\n");
        printf("The Node Contains: ");
        for (int i = 0; i < root->n; i++)
        {
            /* code */
            printf("%d ",*(root->key+i));
        }
        printf("\n");
        printf("The height of this node is %d",B_tree_height(root)-1);
        printf("\n");
    }
    else
    {
        int index = L_search((root->key),root->n,value);
        B_tree_search((root->pointer)[index],value);
    }
}

void B_tree_search_min(node* root){
    if (root == NULL)
    {
        printf("NOT FOUND\n");
        return;
    }
    if (root->leaf)
    {
        printf("%d\n",*(root->key));
        return;
    }
    else
    {
        B_tree_search_min((root->pointer)[0]);
    }
}

void B_tree_Sorted(node* root){
    if(root->leaf){
        for (int i=0; i<root->n; i++){
            printf("%d ",*(root->key+i));
        }
        return;
    }
    else{
        for (int i=0; i<root->n; i++){
            B_tree_Sorted((root->pointer)[i]);
            printf("%d ",*(root->key+i));
        }
        B_tree_Sorted((root->pointer)[root->n]);
    }
}

int main(){
    node* head=NULL;
    printf("Enter the minimum degree of the B-tree t: ");
    scanf("%d",&t);
    for (int i = 10; i > 0; i--)
    {
        /* code */
        head = insert(head,i);
    }
    printf("Options: \n");
    printf("I for Insertion\n");
    printf("S for Search\n");
    printf("M for Finding minimum\n");
    printf("T for Traversing the B-tree\n");
    printf("E for Exit\n");
    char choice;
    // Choice loop
    do{
        printf("Enter your choice: ");
        scanf(" %c",&choice);
        if (choice=='I')
        {
            int no_of_values;
            printf("Enter number of elements you wanted to enter: ");
            scanf("%d",&no_of_values);
            printf("Enter %d numbers to insert: ",no_of_values);
            for (int i = 0; i < no_of_values; i++)
            {
                int value;
                scanf("%d",&value);
                head = insert(head,value);
            }
        }

        else if (choice=='S')
        {
            int value;
            printf("Enter element to search: ");
            scanf("%d",&value);
            B_tree_search(head,value);
        }

        else if (choice=='M')
        {
            printf("The minimum element is ");
            B_tree_search_min(head);
        }
        else if (choice=='T')
        {
            printf("Inorder Traversal: ");
            B_tree_Sorted(head);
            printf("\n");
        }
        else if (choice=='E')
        {
            printf("Thank You! ");
            break;
        }
        else
        {
            printf("Invalid choice");
        }
    }while(choice!='E');
    

    return 0;
}