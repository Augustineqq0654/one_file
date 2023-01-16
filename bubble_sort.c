#include <stdio.h>

void bubble_sort(int *a, int length);   //冒泡排序法

int main()
{
    printf("Hello, World!\n");
    int a[10]={1, 4, 2, 56, 34, 23, 90, 20, 66, 88};
    int length = sizeof(a)/sizeof(int);
    // printf("%d\n",sizeof(int));
    // printf("length:%d\n",length);
    if(length>10)
        return 0;
    bubble_sort(a, length);
    // int temp = 0;
    // for(int i=0; i<length; i++)
    // {
    //     for(int j=i; j<length; j++)
    //     {
    //         if(a[j]>a[j+1])
    //         {
    //             temp = a[j];
    //             a[j] = a[j+1];
    //             a[j+1] = temp;
    //         }
    //     }
    // }
    for(int i=0; i<length; i++)
        printf("%d\t",a[i]);
    return 0;
}

void bubble_sort(int *a, int length)
{
    int temp = 0;
    for(int i=0; i<length; i++)
    {
        for(int j=i; j<length; j++)
        {
            if(a[j]>a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}