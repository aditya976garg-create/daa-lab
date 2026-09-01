//Name: Aditya Garg
//Roll Number: 25/DA/005
//6. Write a program to solve the Fractional Knapsack problem using the Greedy approach.
#include <iostream>
#include <algorithm>
using namespace std;

struct Item
{
    int weight;
    int value;
};

// Function to compare items according to value/weight ratio
bool compare(Item a, Item b)
{
    double ratio1 = (double)a.value / a.weight;
    double ratio2 = (double)b.value / b.weight;

    return ratio1 > ratio2;
}

int main()
{
    int n;
    double capacity;

    cout << "Enter number of items: ";
    cin >> n;

    Item items[100];

    cout << "Enter weight and value of each item:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    // Sort items according to value/weight ratio
    sort(items, items + n, compare);

    double totalValue = 0.0;

    // Select items greedily
    for (int i = 0; i < n; i++)
    {
        // If the complete item can fit
        if (items[i].weight <= capacity)
        {
            capacity = capacity - items[i].weight;
            totalValue = totalValue + items[i].value;
        }
        else
        {
            // Take only the required fraction
            double fraction = capacity / items[i].weight;

            totalValue = totalValue + items[i].value * fraction;

            capacity = 0;

            break;
        }
    }

    cout << "\nMaximum value in knapsack = " << totalValue;

    return 0;
}