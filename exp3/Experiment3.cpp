//Name: Aditya Garg
//Roll Number: 25/DA/005
//3. Write a program to implement Heap Sort.
#include <iostream>
using namespace std;

//TC(Every Case): O(N*logN)
// Function to maintain the max heap
void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1; //left child  index
    int right = 2 * i + 2; //right child index

    // Check if left child is larger
    if (left < n && arr[left] > arr[largest]) largest = left;

    // Check if right child is larger
    if (right < n && arr[right] > arr[largest]) largest = right;

    // If largest is not the root
    if (largest != i){
        swap(arr[i], arr[largest]);
        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heapSort(int arr[], int n){
    // Build a max heap
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(arr,n,i);
    }

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--){
        // Move the largest element to the end
        swap(arr[0], arr[i]);

        // Heapify the remaining heap
        heapify(arr, i, 0);
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
    heapSort(arr, n);
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}