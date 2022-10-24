// 2021MCB1181
// Jignesh Agrawal

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void BinaryIndextreemake(int *arr,int n, int *ans){
    *ans=*arr;
    // Makes Binary Tree
    for (int i = 1; i < n; i++)
    {
        *(ans+i)=0;
        for (int j = 0; j < (i&-i); j++)
        {
            *(ans+i)+=*(arr+i-j);
        }  
    }
    
}

void func1(int *arr,int n,int * ans){
    // Creates Cumulative Sum Array
    *ans=*arr;
    for (int i = 1; i < n; i++)
    {
        /* code */
        *(ans+i) = *(ans+i-1) + *(arr+i);
    }    
}

void func2(int *BIarr,int n,int query){
    // if query =1 then update the binary index tree
    // if query =2 then print the sum of first n - 5 elements

    clock_t start,end;
    
    if(query==1){
        start = clock();
        for (int i = 1; i < n; i=i+0)
        {
            /* code */
            *(BIarr+i)+=5;
            i=i+(i&-i);
        }
        end=clock();
        
        printf("The time taken for query 1 by function 2 is %f\n",(double)(end-start)/CLOCKS_PER_SEC);
        printf("The incremented value of the first index element is %d\n",*(BIarr+1));
    }

    else if(query==2){
        start = clock();
        int sum=0;
        for (int i = n-6; i > 0; i=i+0)
        {
            /* code */
            sum+=*(BIarr+i);
            i=i-(i&-i);

        }
        end=clock();
        printf("The time taken for query 2 by function 2 is %f\n",(double)(end-start)/CLOCKS_PER_SEC);
        printf("The sum of the first n-5 elements is %d\n",sum);
    }
    
}

int main(){
    char inptype;
    printf("Please enter a choice: ");
    scanf("%c",&inptype);
    char temp;
    scanf("%c",&temp);
    int *Arr = (int*)malloc(sizeof(int));
    int filesize=0;
    // input type 'a' for file input and b for random input
    if (inptype=='a')
    {
        FILE * fp;
        fp=fopen("ExampleFile.txt","r");
        *Arr = 0;
        int i=1;
        
        while(1){
            int c = getc(fp);
            if (c==EOF)
            {
                break;
            }
            else{
                Arr=(int*)realloc(Arr,(i+1)*sizeof(int));
                fscanf(fp,"%d",(&Arr[i]));
            }
            i++;
        }
        
        filesize=i;
        fclose(fp);
    }
    else if (inptype=='b'){
        char *carr = (char*)malloc(sizeof(char));
        int i=0;
        printf("Please input an integer array with space-separator and press Enter when done: ");
        while (1)
        {
            // input array as caharacter array
            char c;
            scanf("%c",&c);
            carr=(char*)realloc(carr,(i+1)*sizeof(char));
            carr[i]=c;
            if (c=='\n')
            {
                break;
            }
            i++;
        }
        i=0;
        int k=0;
        int num=0;
        int Flag=0;
        // converting character array to integer array
        while (1)
        {
            
            if ((carr[i]==' ') || (carr[i]=='\n'))
            {
                Arr=(int*)realloc(Arr,(k+1)*sizeof(int));
                if (Flag==1)
                {
                    num=-num;
                }
                *(Arr+k)=num;
                k++;
                num=0;
                Flag=0;
                if (carr[i]=='\n')
                {
                    break;
                }
            }
            else{
                
                if (carr[i]=='-')
                {
                    Flag=1;
                }
                else 
                num=num*10+(carr[i]-'0');
            }
            
            i++;
        }
        filesize=k;
        
    }
    else
    {
        printf("Invalid input");
    }
    

    printf("The array size is %d\n",filesize);

    // intial condition for func1
    int *CIarr = (int*)malloc(filesize*sizeof(int));
    clock_t start,end;
    func1(Arr,filesize,CIarr);
    printf("By function_1:\n");

    // query 1 func1
    start=clock();
    Arr[1]+=5;
    func1(Arr,filesize,CIarr);
    end=clock();
    printf("The time taken for query 1 by function 1 is %f seconds\n",(double)(end-start)/(double)CLOCKS_PER_SEC);
    printf("The incremented value of the first index element is %d\n",Arr[1]);


    // query 2 func1
    start=clock();
    int a = CIarr[filesize-6];
    end=clock();
    printf("The time taken for query 2 by function 1 is %f seconds\n",(double)(end-start)/(double)CLOCKS_PER_SEC);
    printf("The sum of first n-5 elements is %d\n",a);

    printf("By function_2:\n");

    // making binary index tree
    int *BItree = (int*)malloc(filesize*sizeof(int));
    BinaryIndextreemake(Arr,filesize,BItree);
   
    // query 1 func2
    func2(BItree,filesize,1);

    // query 2 func2
    func2(BItree,filesize,2);


    return 0;
}