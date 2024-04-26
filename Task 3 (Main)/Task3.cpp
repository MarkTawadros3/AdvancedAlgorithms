#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;

ofstream dataFile("sort_results.csv");

int heapify(int arr[], int n, int i)
{
    int num_of_comp = 0;
    int minVal = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n)
    {
        num_of_comp++;
        if (arr[l] < arr[minVal])
        {
            minVal = l;
        }
    }
    if (r < n)
    {
        num_of_comp++;
        if (arr[r] < arr[minVal])
        {
            minVal = r;
        }
    }
    if (minVal != i)
    {
        swap(arr[i], arr[minVal]);
        num_of_comp += heapify(arr, n, minVal);
    }
    return num_of_comp;
}

int heap_sort_count(int arr[], int n)
{
    int num_of_comp = 0;
    for (int i = (n - 2) / 2; i >= 0; i--)
    {
        num_of_comp += heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        num_of_comp += heapify(arr, i, 0);
    }
    return num_of_comp;
}

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

int insertion_sort_count(int arr[], int n)
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

void exec_sorts(int temp[], int arr[], int n, string arr_type, string sort_alg)
{
    reshuffle(temp, arr, n);
    auto start = chrono::high_resolution_clock::now();
    int sort;
    if (sort_alg == "Heap")
    {
        sort = heap_sort_count(temp, n);
    }
    else if (sort_alg == "Bubble")
    {
        sort = bubble_sort_count(temp, n);
    }
    else if (sort_alg == "Selection")
    {
        sort = selection_sort_count(temp, n);
    }
    else
    {
        sort = insertion_sort_count(temp, n);
    }
    auto end = chrono::high_resolution_clock::now();
    double exec_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
    dataFile << n << "," << arr_type << "," << sort_alg << "," << sort << "," << exec_time << "\n";
    printTable(n, arr_type, sort_alg, sort, exec_time);
}

void run_sorts(int arr[], string arr_type, int n)
{
    int* temp = new int[n];
    exec_sorts(temp, arr, n, arr_type, "Heap");
    exec_sorts(temp, arr, n, arr_type, "Bubble");
    exec_sorts(temp, arr, n, arr_type, "Selection");
    exec_sorts(temp, arr, n, arr_type, "Insertion");
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
        int* rand_arr = new int[s];
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
    return 0;
}