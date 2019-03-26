#include <stdio.h>
#include <stdlib.h>

struct Job
{
    char id;
    int dead;
    int profit;
};

struct Job arr[5]={{ 'a', 2, 100 }, { 'b', 1, 19 },
                   { 'c', 2, 27 },  { 'd', 1, 25 },
                   { 'e', 3, 15 }};

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b =temp;
}

void swapID(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Job arr[], int low, int high)
{
    int pivot = arr[high].profit;
    int pIndex = low;
    int i;
    for(i = low; i < high; i++)
    {
        if(arr[i].profit > pivot)
        {
            swapID(&arr[i].id, &arr[pIndex].id);
            swap(&arr[i].profit, &arr[pIndex].profit);
            swap(&arr[i].dead, &arr[pIndex].dead);
            pIndex++;
        }
    }
            swapID(&arr[high].id, &arr[pIndex].id);
            swap(&arr[high].profit, &arr[pIndex].profit);
            swap(&arr[high].dead, &arr[pIndex].dead);
    return pIndex;
}

void qSort(struct Job arr[], int low, int high)
{
    if(low < high)
    {
        int pIndex = partition(arr, low, high);
        qSort(arr, low, pIndex-1);
        qSort(arr, pIndex+1, high);
    }
}

int maxDeadline(struct Job arr[], int n)
{
    int i;
    int max = arr[0].dead;
    for(i = 0; i < n; i++)
    {
        if(max < arr[i].dead)
        {
            max = arr[i].dead;
        }
    }
    return max;
}
int printJob(struct Job arr[], int n)
{
    qSort(arr, 0, n-1);

    int max = maxDeadline(arr, n);

    char result[max];
    char slot[max];

    int cost = 0, jobsDone = 0;
    int i, min;
    for(i = 0; i < n; i++)
        slot[i] = 'F';

    for(i = 0; i < n; i++)
    {
       for(min = arr[i].dead -1; min>=0; min--)
       {
            if(slot[min] == 'F')
            {
                result[min] = arr[i].id;
                slot[min] = 'T';
                cost += arr[i].profit;
                jobsDone++;
                break;
            }
       }

     if(jobsDone == max)
        break;
    }

    printf("\nThe jobs selected with its id are:- \n");
    for(i=0; i< max; i++)
        printf("%c\t", result[i]);

    return cost;
}
int main()
{
    printf("\nThe maximum profit made from the jobs is %d\n", printJob(arr, 5));
    return 0;
}
