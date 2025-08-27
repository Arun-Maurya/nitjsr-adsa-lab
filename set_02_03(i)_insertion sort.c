#include<stdio.h>
int main(){
    int a,b,n;
    printf("enter the size of the array ");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
         scanf("%d",&arr[i]);
    }
    for(int i=1;i<n;i++){
        a=arr[i];
        b=i-1;
        while(b>=0 && arr[b]>a){
              arr[b+1]=arr[b];
              b--;
        }
        arr[b+1]=a;
    }
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
   return 0; 
}