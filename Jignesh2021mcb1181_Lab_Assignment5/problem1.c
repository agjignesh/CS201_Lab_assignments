#include<stdio.h>
#include<stdlib.h>

// AVL Tree Node
struct node
{
    int value;
    int bf;
    struct node* left;
    struct node* right;
};

typedef struct node node;

node* Head_Node = NULL;

node* new_node(int value){
    node* leaf = malloc(sizeof(node));
    leaf->bf=0;
    leaf->value=value;
    leaf->left=NULL;
    leaf->right=NULL;
    return leaf;
}
// LL imbalance
node* LL_Balance(node* root){
    node* temp = root->left;
    root->left = root->left->right;
    temp->right = root;
    return temp;
}
// RR imbalance
node* RR_Balance(node* root){
    node* temp = root->right;
    root->right = root->right->left;
    temp->left = root;
    return temp;
}
// RL imbalance
node* RL_Balance(node* root){
    node* temp = root->right->left;
    root->right->left = temp->right;
    temp->right = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}
// LR imbalance
node* LR_Balance(node* root){
    node* temp = root->left->right;
    root->left->right = temp->left;
    temp->left = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}

// find the height of the tree
int height(node* root){
    if(root==NULL){
        return 0;
    }
    int left = height(root->left);
    int right = height(root->right);
    if(left>right){
        return left+1;
    }
    else{
        return right+1;
    }
}

// update the balance factor of the tree 
void updateBF(node* root){
    //node* root  = Head_Node;
    if (root==NULL)
    {
        return;
    }
    
    int left_height = height(root->left);
    int right_height = height(root->right);
    root->bf = left_height - right_height;
    updateBF(root->left);
    updateBF(root->right);
}

node* insertAVLtree(node* root,int n){
    if (root==NULL)
    {
        // printf("Hi ");
        return new_node(n);
    }
    else
    {
        if (root->value<n)
        {
            root->right = insertAVLtree(root->right,n);
            //printf("%d",root->bf);
        }
        else
        {
            root->left = insertAVLtree(root->left,n);
        }
        updateBF(root);
        if (root->bf==-2)
        {
            /* code */
            if (root->right->bf==-1)
            {
                root = RR_Balance(root);
            }
            else
            {
                root = RL_Balance(root);
            }
            updateBF(root);
        }
        else if (root->bf == 2){
            if (root->left->bf==1)
            {
                /* code */
                root = LL_Balance(root);
            }
            else{
                root = LR_Balance(root);
            }
            updateBF(root);
        }
        return root;
    }
}

// preorder traversal
void preorder(node* root){
    if (root!=NULL)
    {
        printf("%d ",root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

// inorder traversal
void inorder(node* root){
    if (root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->value);
        inorder(root->right);
    }
}

void search(node* root,int n){
    if (root==NULL)
    {
        printf("Not Present\n");}
    else{
        if (root->value==n)
        {
            printf("Present\n");
            printf("Balance Factor of %d is %d\n",root->value,root->bf);
            printf("Height of %d in th AVL tree is %d\n",root->value,height(root)-1);
        }
        else if (root->value<n)
        {
            search(root->right,n);
        }
        else
        {
            search(root->left,n);
        }
    }
}

int main(){
    int n = 25;
    //creating Intial tree
    for (int i = 0; i < n; i++)
    {
        /* code */
        Head_Node = insertAVLtree(Head_Node,i);
    }
    printf("Input\n");
    printf("AVL tree Constructed by insering elements from 0 to 24\n");
    
    // Choice Loop
    char choice;
    do
    {
        /* code */
        printf("\n");
        printf("i) Insert :\n");
        printf("s) search :\n");
        printf("p) Print Preorder and Inorder in Separate lines :\n");
        printf("q) Quit :\n");
        printf("\n");
        printf("Enter your choice : ");
        scanf(" %c",&choice);
        if (choice=='i')
        {
            printf("Enter a data to insert: ");
            int data;
            scanf("%d",&data);
            Head_Node = insertAVLtree(Head_Node,data);
        }
        else if (choice=='s')
        {
            /* code */
            printf("Enter a data you want to search: ");
            int data;
            scanf("%d",&data);
            search(Head_Node,data);
        }
        else if (choice=='p')
        {
            /* code */
            printf("Preorder sequence: \n");
            preorder(Head_Node);
            printf("\n");
            printf("Inorder sequence: \n");
            inorder(Head_Node);
            printf("\n");
        }
        else if (choice=='q')
        {
            /* code */
            printf("Thank you for using the program\n");
        }
        else
        {
            printf("Invalid choice\n");
        }
        
    }while (choice!='q');
    return 0;
}
