#include <stdio.h>

void bubble_sort(int arr[], int len);
void selection_sort(int arr[], int len);
void insertion_sort(int arr[], int len);
void shell_sort(int arr[], int len);

/* 冒泡排序 */
void bubble_sort(int arr[], int len) 
{
    int i, j, temp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

/* 选择排序 */
void selection_sort(int arr[], int len)
{
    int i, j, temp;
    for(i=0; i<len; i++)
    {
        for(j=i+1; j<len; j++)
        {
            if(arr[j]<arr[i])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/* 插入排序 */
void insertion_sort(int arr[], int len)
{
    int i, j, temp;
    for(i=1; i<len; i++)
    {
        temp = arr[i];
        for(j=i; j>0&&arr[j-1]>temp; j--)
            arr[j] = arr[j-1];
        arr[j] = temp;
    }
}

/* 希尔排序 */
void shell_sort(int arr[], int len)
{
    int gap, i, j;
    int temp;
    for(gap=len>>1; gap>0; gap=gap>>1)
    {
        for(i=gap; i<len; i++)
        {
            temp = arr[i];
            for(j=i-gap; j>=0&&arr[j]>temp; j-=gap)
                arr[j+gap] = arr[j];
            arr[j+gap] = temp;
        }
    }
}

int main() {
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    shell_sort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}