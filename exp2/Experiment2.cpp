//Name: Aditya Garg
//Roll Number: 25/DA/005
//2. Write a program to implement Quick Sort.

//Quick Sort: place the pivot at it's correct place, then quick sort left and right part of it
//Divide & Conquer Algorithm

//TC: O(N*log(base:2)N) due to same reason as merge sort
//SC: O(1) as there is no temp arr used in quick sort
#include <iostream>
using namespace std;

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high){
    if (low < high){
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main()
{
    int arr[100], n;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++){
        cin>>arr[i];
    }
    quickSort(arr, 0, n - 1);
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}