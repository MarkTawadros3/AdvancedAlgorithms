#include <iostream>
using namespace std;

// function to print the array
void printArray(int arr[], int s)
{
    cout << "[" << arr[0];
    for (int i = 1; i < s; i++)
    {
        cout << ", " << arr[i];
    }
    cout << "]" << endl;
}

// function to rearrange array (find the partition point)
int partition(int arr[], int l, int h)
{
    // select the rightmost element as pivot
    int pivot = arr[h];
    // pointer for greater element
    int i = (l - 1);
    // traverse each element of the array
    // compare them with the pivot
    for (int j = l; j < h; j++)
    {
        if (arr[j] <= pivot)
        {
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;
            // swap element at i with element at j
            swap(arr[i], arr[j]);
        }
    }
    // swap pivot with the greater element at i
    swap(arr[i + 1], arr[h]);
    // return the partition point
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int target)
{
    // Check if the key is in the current array (i.e. within the range low to high) or not.
    int target_in_arr = -1;
    for (int i = low; i < high + 1; i++)
    {
        if (arr[i] == target)
        {
            target_in_arr = i;
            break;
        }
    }
    if (target_in_arr != -1)
    {
        swap(arr[high], arr[target_in_arr]);
        if (low < high)
        {
            // find the pivot element such that
            // elements smaller than pivot are on left of pivot
            // elements greater than pivot are on righ of pivot
            int pi = partition(arr, low, high);
            // recursive call on the left of pivot
            quickSort(arr, low, pi - 1, target);
            // recursive call on the right of pivot
            quickSort(arr, pi + 1, high, target);
        }
    }
}

// Driver code
int main()
{
    int unsorted_arr[] = {3, 1, 12, 9, 4, 10, 54, 34, 12, 89};
    int n = sizeof(unsorted_arr) / sizeof(unsorted_arr[0]);
    int key = 12;
    // Check if the key is in the array or not.
    int found = -1;
    for (int i = 0; i < n; i++)
    {
        if (unsorted_arr[i] == key)
        {
            found = i;
            break;
        }
    }
    // Print an error message and exit/terminate the program if the key does not exist.
    if (found == -1)
    {
        cout << 'Enter a valid element key';
        return 0;
    }
    cout << "UnsortedArray: ";
    printArray(unsorted_arr, n);
    // perform quicksort on data
    quickSort(unsorted_arr, 0, n - 1, key);
    cout << "Output: ";
    printArray(unsorted_arr, n);
    return 0;
}



// ------------------------------------------------------------



/* Iterative quicksort
#include <iostream>
#include <stack>
#include <utility>

using namespace std;

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to perform iterative quicksort
void iterativeQuickSort(int arr[], int low, int high) {
    stack<pair<int, int>> st;
    st.push({low, high});

    while (!st.empty()) {
        low = st.top().first;
        high = st.top().second;
        st.pop();

        if (low < high) {
            int pivot = partition(arr, low, high);

            // Push subarray indices of elements less than pivot
            st.push({low, pivot - 1});
            // Push subarray indices of elements greater than pivot
            st.push({pivot + 1, high});
        }
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, n);

    iterativeQuickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}*/



// ------------------------------------------------------------



/* Alternative Solutions
#include <iostream>
using namespace std;

void printArray(int arr[], int length)
{
    cout << "Output: [" << arr[0];
    for (int i = 1; i < length; i++)
    {
        cout << ", " << arr[i];
    }
    cout << "]\n" << endl;
}

int findIndex(int arr[], int length, int target)
{
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}

void firstSortAlg(int arr[], int length, int key)
{
    int occ = 0;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == key)
        {
            occ++;
        }
    }
    int newArray[length];
    int index = 0;
    for (int x = 0; x < length; x++)
    {
        if (arr[x] < key)
        {
            newArray[index] = arr[x];
            index++;
        }
    }
    for (int y = 0; y < occ; y++)
    {
        newArray[index] = key;
        index++;
    }
    for (int z = 0; z < length; z++)
    {
        if (arr[z] > key)
        {
            newArray[index] = arr[z];
            index++;
        }
    }
    printArray(newArray, length);
}

void secondSortAlg(int arr[], int length, int key)
{
    for (int i = 0; i < length; i++)
    {
        int keyIndex = findIndex(arr, length, key);
        int temp = arr[i];
        if (arr[i] == key && i > keyIndex)
        {
            for (int a = i; a > keyIndex; a--)
            {
                arr[a] = arr[a-1];
            }
            arr[keyIndex] = temp;
        }
        else if (arr[i] < key && i > keyIndex)
        {
            arr[i] = key;
            arr[keyIndex] = temp;
            keyIndex = i;
        }
        else if (arr[i] > key && i < keyIndex)
        {
            for (int b = i; b < keyIndex; b++)
            {
                arr[b] = arr[b+1];
            }
            arr[keyIndex] = temp;
        }
    }
    printArray(arr, length);
}

// This algorithm seperates them into 'higher value [than key]' and 'lower' sections,
// however, it does not sort them in the required way.
// Score 7/10
void thirdSortAlg(int arr[], int length, int key)
{
    for (int i = 0; i < length; i++)
    {
        int keyIndex = findIndex(arr, length, key);
        int temp = arr[i];
        if (arr[i] <= key && i > keyIndex)
        {
            arr[i] = key;
            arr[keyIndex] = temp;
            keyIndex = i;
        }
        else if (arr[i] > key && i < keyIndex)
        {
            arr[i] = key;
            arr[keyIndex] = temp;
            keyIndex = i;
        }
    }
}

// Score: 7/10
void fourthSortAlg(int arr[], int length, int key)
{
    for (int i = 0; i < length; i++)
    {
        int keyIndex = findIndex(arr, length, key);
        int temp = arr[i];
        if (arr[i] <= key && i > keyIndex)
        {
            int step = i - 1;
            while (arr[step] >= key && step >= keyIndex)
            {
                arr[step + 1] = arr[step];
                --step;
            }
            arr[step + 1] = temp;
        }
        else if (arr[i] > key && i < keyIndex)
        {
            int step = i + 1;
            while (arr[step] <= key && step <= length)
            {
                arr[step - 1] = arr[step];
                ++step;
            }
            arr[step - 1] = temp;
        }
    }
    printArray(arr, length);
}

// Score 8-9/10
// Just need to make it more efficient + turn it into a recursive function
void sortAlgIter(int arr[], int length, int key)
{
    for (int i = 0; i < length; i++)
    {
        int keyIndex = findIndex(arr, length, key);
        int temp = arr[i];
        if (arr[i] <= key)
        {
            int step = i - 1;
            while (step >= keyIndex)
            {
                arr[step + 1] = arr[step];
                --step;
            }
            arr[step + 1] = temp;
        }
        else
        {
            int step = i + 1;
            while (step <= keyIndex)
            {
                arr[step - 1] = arr[step];
                ++step;
            }
            arr[step - 1] = temp;
        }
    }
    printArray(arr, length);
}

// Score: 9/10
// IMPROVEMENTS: we can decrease number of parameters by calculating the length of
// the array inside the function (i.e. ''sizeof(arr)/sizeof(int)'') instead of passing it.
void sortAlgRec(int arr[], int length, int i, int key)
{
    if (i < 0)
    {
        return;
    }
    sortAlgRec(arr, length, i - 1, key);
    int keyIndex = findIndex(arr, length, key);
    int temp = arr[i];
    if (temp <= key)
    {
        int step = i - 1;
        while (step >= keyIndex)
        {
            arr[step + 1] = arr[step];
            --step;
        }
        arr[step + 1] = temp;
    }
    else
    {
        int step = i + 1;
        while (step <= keyIndex)
        {
            arr[step - 1] = arr[step];
            ++step;
        }
        arr[step - 1] = temp;
    }
}

int main()
{
    int list[] = {3, 1, 12, 9, 4, 10, 54, 34, 12, 89};
    cout << "UnsortedArray: [3, 1, 12, 9, 4, 10, 54, 34, 12, 89]" << endl;
    
    int size = sizeof(list) / sizeof(int);
    
    int num;
    cout << "Key = ";
    cin >> num;
    
    //sortAlgIter(list, size, num);
    sortAlgRec(list, size, size - 1, num);
    printArray(list, size);

    cout << "UnsortedArray: [3, 1, 34, 12, 9, 4, 10, 54, 71, 12, 1, 89, 12, 12, 5, 30, 12]" << endl;
    int list2[] = {3, 1, 34, 12, 9, 4, 10, 54, 71, 12, 1, 89, 12, 12, 5, 30, 12};
    int size2 = sizeof(list2) / sizeof(int);
    //sortAlgIter(list2, size2, num);
    sortAlgRec(list2, size2, size2 - 1, num);
    printArray(list2, size2);

    cout << "UnsortedArray: [12, 3, 1, 34, 12, 9, 4, 10, 54, 71, 12, 1, 89, 12, 12, 5, 30]" << endl;
    int list3[] = {12, 3, 1, 34, 12, 9, 4, 10, 54, 71, 12, 1, 89, 12, 12, 5, 30};
    int size3 = sizeof(list3) / sizeof(int);
    //sortAlgIter(list3, size3, num);
    sortAlgRec(list3, size3, size3 - 1, num);
    printArray(list3, size3);

    cout << "UnsortedArray: [12, 3, 1, 34, 12, 9, 4, 10, 54, 71, 12, 1, 89, 12, 12, 5, 30, 12]" << endl;
    int list4[] = {12, 3, 1, 34, 12, 9, 4, 10, 54, 71, 12, 1, 89, 12, 12, 5, 30, 12};
    int size4 = sizeof(list4) / sizeof(int);
    //sortAlgIter(list4, size4, num);
    sortAlgRec(list4, size4, size4 - 1, num);
    printArray(list4, size4);

    return 0;
}*/