#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <time.h>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

#define max_threads 4

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
// Driver program to test above functions
int main()
{
    pthread_t threads[max_threads];
    int i;
    int *arr;
    unsigned long size = 10000L;

    arr = (int *)malloc(size * sizeof(int *));
  
    //start time 
    auto start = high_resolution_clock::now();
   
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10000;
    }

    //spliting the program to each thread to achieve parallelism
    int n = sizeof(arr)/sizeof(arr[0]);
    int p = pthread_create(&threads[i], NULL, quickSort(arr, 0, n-1), NULL);

    //joining all the completed task in each threads
    for (int i = 0; i < max_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    //printing array
    printf("Sorted array:\n");
    for (int i=0; i < size; i++)
    {  
        printf("%d ", arr[i]);
    }

    //stop time
    auto stop = high_resolution_clock::now();
    //gets the start and stop time and subtracts it to get the amount of time spent processing.
    auto duration = duration_cast<microseconds>(stop - start);
    auto duration_s = duration_cast<milliseconds>(stop - start);
    //convert milliseconds to seconds 
    double secs = double(duration_s.count())/1000;

    cout << "\nTime taken to run: " << duration.count() << " microseconds (" << secs << " seconds)"<< endl;

}
