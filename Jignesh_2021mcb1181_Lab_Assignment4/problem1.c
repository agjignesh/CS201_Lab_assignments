#include<stdio.h>
int heap_size=0;

void exchange(int* a, int* b){
    int temp = *a;
    *a= *b;
    *b = temp;
}

int left_child(int a){
    return (2*a);
}

int right_child(int a){
    return (2*a+1);
}

int parent(int a){
    return (a/2);
}

void max_heapify(int* a,int i){
    int l = left_child(i);
    int r = right_child(i);
    int largest = i;
    if (l<=heap_size && a[l]>a[largest])
    {
        largest = l;
    }
    if (r<=heap_size && a[r]>a[largest])
    {
        largest = r;
    }
    if (largest==i)
    {
        return;
    }
    exchange(&a[largest],&a[i]);
    max_heapify(a,largest);
}

void built_max_heap(int* a){
    int n = heap_size;
    while (n>=1)
    {
        max_heapify(a,n);
        n--;
    } 
}

int extract_max(int* a){
    int temp = a[1];
    exchange(&a[1],&a[heap_size]);
    heap_size--;
    max_heapify(a,1);
    return temp;
}

void min_heapify(int* a,int i){
    int l = left_child(i);
    int r = right_child(i);
    int smallest = i;
    if (l<=heap_size && a[l]<a[smallest])
    {
        smallest = l;
    }
    if (r<=heap_size && a[r]<a[smallest])
    {
        smallest = r;
    }
    if (smallest==i)
    {
        return;
    }
    exchange(&a[smallest],&a[i]);
    min_heapify(a,smallest);
}

void built_min_heap(int* a){
    int n = heap_size;
    while (n>=1)
    {
        min_heapify(a,n);
        n--;
    } 
}


int main(){
    // Taking n and k as input and defining a array of size n+1 with first index 1 and last index n
    printf("Enter number of elements n and k: ");
    int n,k;
    scanf("%d",&n);
    scanf("%d",&k);
    int choice;
    printf("Enter 1 for Algorithm 1a and Enter 2 for Algorithm 1b ");
    scanf("%d",&choice);
    printf("Enter %d numbers ",n);
    if (choice==1)
    {
        int arr[n+1];
        heap_size = n;
        for(int i=1;i<=n;i++){
            scanf("%d",&arr[i]);
        }
        built_max_heap(arr);
        int temp = 0;
        for (int i = 0; i < k; i++)
        {
            temp = extract_max(arr);
        }
        printf("%d th largest number is %d",k,temp);
    }
    else if (choice==2)
    {
        int arr[k+1];
        heap_size=k;
        int i;
        for (i = 1; i <= k; i++)
        {
            scanf("%d",&arr[i]);
        }
        built_min_heap(arr);
        for ( ; i <= n; i++)
        {
            int in;
            scanf("%d",&in);
            if (in>arr[1])
            {
                exchange(&in,&arr[1]);
                min_heapify(arr,1); 
            }
        }
        printf("%d th largest number is %d",k,arr[1]);  
    }
    // 100 120 20 30 10 110 90 65 40 50
    return 0;
}
