#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <time.h>
#include <omp.h>

using namespace std;
using namespace std::chrono;

//defining the threads being used
#define max_threads 4

const long SIZE = 10000L;

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

void* Q_sort(int q)
{
    int *arr;
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 10000;
    }

    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    //printing array
    printf("Sorted array:\n");
    for (int i=0; i < SIZE; i++)
    {  
        printf("%d ", arr[i]);
    }
    return 0;
}
 
// Driver program to test above functions
int main()
{
    int *arr;
    unsigned long size = SIZE;
    
    omp_set_num_threads(max_threads);

    arr = (int *)malloc(size * sizeof(int *));
  
    //start time 
    auto start = high_resolution_clock::now();
   
    #pragma omp parallel
    {
        int i = omp_get_thread_num();
        Q_sort(i);
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
