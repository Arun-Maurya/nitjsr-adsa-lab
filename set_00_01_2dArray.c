#include<stdio.h>
#include<stdlib.h>

int main()
{
    int row, col;
   
    printf("Enter the number of rows");
    scanf("%d",& row);
    printf("Enter the number of cols");
    scanf("%d",& col);
    int array[row][col];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j]=0;
        }
        
    }
    
    printf("\n enter element of the array \n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0;j< col;j++)
        {
            printf("enter the element at position [%d][%d]:",i,j);
            scanf("%d",&array[i][j]);

        }
        
    }

     for (int i = 0; i<row; i++)
    {
        for (int j = 0; j< col; j++)
        {
            printf("%d\t",array[i][j]);
        }
        printf("\n");
    }
    

return 0;

}