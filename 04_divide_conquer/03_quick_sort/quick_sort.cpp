#include <iostream>

using namespace std;

int partition(int arr[], int start, int stop) {
    int pivot = arr[start]; // anything except stop

    int left = start - 1; 
    int right = stop + 1; 
    
    while (left < right) {
        do {left += 1;} 
        while (arr[left] < pivot);

        do {right -= 1;} 
        while (arr[right] > pivot);
        
        if (left < right) {
            swap(arr[left], arr[right]);
        }
    }

    return right;
}

void quicksort(int arr[], int start, int stop) {
    if (start < stop) {
        int pi = partition(arr, start, stop);
        quicksort(arr, start, pi);
        quicksort(arr, pi + 1, stop);
    }
}

int main()
{
    int arr[] = {5, 2, 9, 1, 3};
    int n = 5;

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}