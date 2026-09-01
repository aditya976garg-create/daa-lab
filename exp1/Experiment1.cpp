//Name: Aditya Garg
//Roll Number: 25/DA/005
//1. Write a program to implement Merge Sort using both recursive and iterative methods.
#include<bits/stdc++.h>
using namespace std;

//ITERATIVE METHOD
//TC: O(N*log(base:2)N)
/*
void merge(int arr[], int low, int mid, int high){
    int temp[100];
    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high){
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid) temp[k++] = arr[i++];

    while (j <= high) temp[k++] = arr[j++];

    for (i = low, k = 0; i <= high; i++, k++){
        arr[i]=temp[k];
    }
}

void iterativeMergeSort(int arr[], int n){
    for (int size = 1; size < n; size *= 2){
        for (int low = 0; low < n - 1; low += 2 * size){
            int mid = low + size - 1;
            int high = low + 2 * size - 1;

            if (mid >= n)
                continue;

            if (high >= n)
                high = n - 1;

            merge(arr, low, mid, high);
        }
    }
}
*/


//RECURSIVE METHOD
//Merge Sort: Divide and Merge
//Use Recursion Backtracking

//TC: O(N*log(base:2)N)
//O(N): due to merge function & O(log(base:2)N): due to mS function

//SC(Worst Case): O(N)
//Cause of the temp array used in merge function  
void merge(int arr[], int low, int mid, int high){
    int i = low;
    int j = mid + 1;
    int k = 0;

    int temp[100];
    while (i <= mid && j <= high){
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid) temp[k++] = arr[i++];

    while (j <= high) temp[k++] = arr[j++];

    for (i = low, k = 0; i <= high; i++, k++){
        arr[i]=temp[k];
    }
}

void mergeSort(int arr[], int low, int high){
    if (low < high){
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

int main(){
    int arr[100], n;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter elements: ";

    for (int i = 0; i < n; i++){
        cin>>arr[i];
    }

    //iterativeMergeSort(arr, n);
    mergeSort(arr, 0, n - 1);
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout<<arr[i]<<" "; 
    }
    return 0;
}