#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;

ofstream dataFile("sort_results_iter_and_rec.csv");

int heap_sort_count(int arr[], int n)
{
    int num_of_comp = 0;
    return num_of_comp;
}


// ---------------------------------------------------------------------


// Iterative Bubble Sort
int bubble_sort_count(int arr[], int n)
{
    int num_of_comp = 0;
    bool swap_occurs;
    for (int i = 0; i < n - 1; i++)
    {
        swap_occurs = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                swap_occurs = true;
            }
            num_of_comp++;
        }
        if (!swap_occurs)
        {
            break;
        }
    }
    return num_of_comp;
}

// Recursive Bubble Sort
int bubble_sort_count_rec(int arr[], int n)
{
    if (n == 1)
    {
        return 0;
    }
    int num_of_comp = 0;
    int swap_occurs = false;
    for (int x = 0; x < n - 1; x++)
    {
        if (arr[x] > arr[x+1])
        {
            swap(arr[x], arr[x+1]);
            swap_occurs = true;
        }
        num_of_comp++;
    }
    if (!swap_occurs)
    {
        return num_of_comp;
    }
    return num_of_comp + bubble_sort_count(arr, n - 1);
}


// ---------------------------------------------------------------------


// Iterative Selection Sort
int selection_sort_count(int arr[], int n)
{
    int num_of_comp = 0;
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
            num_of_comp++;
        }
        swap(arr[i], arr[min]);
    }
    return num_of_comp;
}

// Recursive Selection Sort
int selection_sort_count_rec(int arr[], int n, int i = 0)
{
    if (i == n - 1)
    {
        return 0;
    }
    int num_of_comp = 0;
    int min = i;
    for (int x = i + 1; x < n; x++)
    {
        if (arr[x] < arr[min])
        {
            min = x;
        }
        num_of_comp++;
    }
    swap(arr[i], arr[min]);
    return num_of_comp + selection_sort_count_rec(arr, n, i + 1);
}

// Another Recursive Selection Sort
int selection_sort_count_rec2(int arr[], int n)
{
    if (n == 1)
    {
        return 0;
    }
    int num_of_comp = 0;
    int s = sizeof(arr) / sizeof(arr[0]);
    int min = arr[-n];
    for (int x = s - n + 1; x < s; x++)
    {
        if (arr[x] < arr[min])
        {
            min = x;
        }
        num_of_comp++;
    }
    swap(arr[-n], arr[min]);
    return num_of_comp + selection_sort_count_rec2(arr, n - 1);
}


// ---------------------------------------------------------------------


// Iterative Insertion Sort
int insertion_sort_count(int arr[], int n)
{
    int num_of_comp = 0;
    int key;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j])
        {
            swap(arr[j], arr[j+1]);
            j--;
            num_of_comp++;
        }
        if (j >= 0)
        {
            num_of_comp++;
        }
    }
    return num_of_comp;
}

// Another Iterative Insertion Sort
int insertion_sort_count_iter2(int arr[], int n)
{
    int num_of_comp = 0;
    int key = 0;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        for (int j = i - 1; j > -1; j--)
        {
            num_of_comp++;
            if (key < arr[j])
            {
                swap(arr[j], arr[j+1]);
            }
            else
            {
                break;
            }
        }
    }
    return num_of_comp;
}

// Recursive Insertion Sort
int insertion_sort_count_rec(int arr[], int n = 1)
{
    int size_of_arr = sizeof(arr) / sizeof(arr[0]);
    if (n > size_of_arr - 1)
    {
        return 0;
    }
    int num_of_comp = 0;
    int key = arr[n];
    for (int x = n - 1; x > -1; x--)
    {
        num_of_comp++;
        if (key < arr[x])
        {
            swap(arr[x], arr[x+1]);
        }
        else
        {
            break;
        }
    }
    return num_of_comp + insertion_sort_count_rec(arr, n + 1);
}

// Another Recursive Insertion Sort
int insertion_sort_count_rec2(int arr[], int n = 1)
{
    int size_of_arr = sizeof(arr) / sizeof(arr[0]);
    if (n > size_of_arr - 1)
    {
        return 0;
    }
    int num_of_comp = 0;
    int key = arr[n];
    int j = n - 1;
    while (j >= 0 && key < arr[j])
    {
        swap(arr[j], arr[j+1]);
        j--;
        num_of_comp++;
    }
    if (j >= 0)
    {
        num_of_comp++;
    }
    return num_of_comp + insertion_sort_count_rec2(arr, n + 1);
}


// ---------------------------------------------------------------------


void printArray(int arr[], int n)
{
    for (int x = 0; x < n; x++)
    {
        cout << arr[x] << " ";
    }
    cout << endl;
}

void reshuffle(int temp[], int arr[], int n)
{
    for (int x = 0; x < n; x++)
    {
        temp[x] = arr[x];
    }
}

void printTable(int n, string arr_type, string sort_type, int sort, double exec_time)
{
    cout << left << setw(20) << n << left << setw(20) << arr_type << left << setw(20) << sort_type << left << setw(25) << sort << left << setw(20) << exec_time << "\n";
}

void run_sorts(int arr[], string arr_type, int n)
{
    int* temp = new int[n]; // Can be shortened to 'int temp[n];'
    reshuffle(temp, arr, n);
    //cout << "Starting Array: ";
    //printArray(temp, n);

    auto start = chrono::high_resolution_clock::now(); // Can be called here or in the sorting algorithm itself. Both the same.
    int sort = heap_sort_count(temp, n);  // Can call the iterative one as well.
    auto end = chrono::high_resolution_clock::now();
    double exec_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
    dataFile << n << "," << arr_type << ",Heap," << sort << "," << exec_time << "\n";
    printTable(n, arr_type, "Heap", sort, exec_time);

    reshuffle(temp, arr, n);
    
    start = chrono::high_resolution_clock::now();
    sort = bubble_sort_count(temp, n);
    end = chrono::high_resolution_clock::now();
    exec_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
    dataFile << n << "," << arr_type << ",Bubble," << sort << "," << exec_time << "\n";
    printTable(n, arr_type, "Bubble", sort, exec_time);

    reshuffle(temp, arr, n);

    start = chrono::high_resolution_clock::now();
    sort = selection_sort_count(temp, n);
    end = chrono::high_resolution_clock::now();
    exec_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
    dataFile << n << "," << arr_type << ",Selection," << sort << "," << exec_time << "\n";
    printTable(n, arr_type, "Selection", sort, exec_time);

    reshuffle(temp, arr, n);

    start = chrono::high_resolution_clock::now();
    sort = insertion_sort_count(temp, n);
    end = chrono::high_resolution_clock::now();
    exec_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
    dataFile << n << "," << arr_type << ",Insertion," << sort << "," << exec_time << "\n";
    printTable(n, arr_type, "Insertion", sort, exec_time);

    //cout << "Final Array: ";
    //printArray(temp, n);
}

void test_comparisons()
{
    srand(time(0));

    dataFile << "Size of Array,Type of Array,Sorting Algorithm,Number of Comparisons,Execution Time\n";
    cout << left << setw(20) << "Size of Array" << left << setw(20) << "Type of Array"
    << left << setw(20) << "Sorting Algorithm" << left << setw(25) << "Number of Comparisons"
    << left << setw(20) << "Execution Time" << "\n";

    for (int s = 1; s < 31; s++)
    {
        int* rand_arr = new int[s]; // Can all be shortened to 'int rand_arr[n], sorted_arr[n], inv_arr[n];'
        int* sorted_arr = new int[s];
        int* inv_arr = new int[s];
        int num1 = 0;
        int num2 = 0;
        for (int i = 0; i < s; i++)
        {
            rand_arr[i] = rand() % (s * 20);
            num1 += rand() % (s * 20);
            sorted_arr[i] = num1;
            num2 += rand() % (s * 20);
            inv_arr[s-i-1] = num2;
        }
        run_sorts(rand_arr, "Random", s);
        run_sorts(sorted_arr, "Sorted", s);
        run_sorts(inv_arr, "Inversely-sorted", s);
        delete[] rand_arr;
        delete[] sorted_arr;
        delete[] inv_arr;
    }
}

int main()
{
    test_comparisons();
    dataFile.close();
}