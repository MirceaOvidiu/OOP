#include <stdio.h>
#include <iostream>
using namespace std;

class Sorter
{
public:
    int low = 0;

    void swap(int a, int b)
    {
        int temp;

        temp = a;
        a = b;
        b = temp;
    }

    int separe(int v[], int low, int high)
    {
        int pivot;
        pivot = v[high];

        int i, j;
        i = low - 1;

        for (j = low; j <= high - 1; j++)
        {
            if (v[j] < pivot)
            {
                i++;
                swap(v[i], v[j]);
            }
        }

        swap(v[i + 1], v[high]);

        return (i + 1);
    }

    void quickSort(int v[], int low, int high)
    {
        int sepIndex;

        if (low < high)
        {
            sepIndex = separe(v, low, high);

            quickSort(v, low, sepIndex - 1);

            quickSort(v, sepIndex + 1, high);
        }
    }

    void printArray(int arr[], int n)
    {
        int i;
        for (i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main()
{
    int arr[5] = {40, 8, 11, 2, 99};
    int n = 5;

    Sorter sorting;

    sorting.quickSort(arr, 0, n);
    sorting.printArray(arr, n);

    return 0;
}