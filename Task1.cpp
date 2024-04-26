#include <iostream>
#include <set>
using namespace std;

int main()
{
    // Input array (contains duplicates).
    char arr[] = {'e', 'b', 'c', 'd', 'e', 'e', 'f', 'g', 'a', 'a', 'c', 'e', 'j', 'i', 'e'};
    // Size of 'arr'.
    int n = sizeof(arr) / sizeof(arr[0]);
    // Set 's' is initialised. It is provided 'begin(arr)' and 'end(arr)' as iterator arguments.
    set<char> s{begin(arr), end(arr)};

    // Printing the array and set to the console.
    cout << "Initial array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    cout << "After removing duplicates: ";
    for (char i : s)
        cout << i << " ";
}