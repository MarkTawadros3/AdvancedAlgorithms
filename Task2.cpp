#include <iostream>
using namespace std;

class Item
{
    public:
        // Class attributes: val - stores the actual value/element (integer).
        // prev - pointer to the previous Item object.
        // next - pointer to the next Item object.
        int val;
        Item* prev;
        Item* next;
    
        // Constructor accepts three parameters.
        Item(int v, Item* p, Item* n)
        {
            // Initialisation of each member variable.
            val = v;
            prev = p;
            next = n;
        }
};

class LinkedList
{
    public:
        // Starting/first Item.
        Item* head;
        // Length/size of list.
        int len;
    
        LinkedList()
        {
            // Initialisation of attributes.
            // The 'head' Item is set to NULL (as there are no Items yet).
            // 'len' is set to 0 as there are no elements in the list; it is empty.
            head = NULL;
            len = 0;
        }

        /*void insertBeginning(int data)
        {
            Item* newItem = new Item(data, NULL, head);
            head = newItem;
        }

        void insertAt(int index, int data)
        {
            Item* temp = head;
            for (int i = 0; i < index-1; i++)
                temp = temp->next;
            Item* newItem = new Item(data, temp, temp->next);
            temp->next->prev = newItem;
            temp->next = newItem;
        }

        void insertLast(int data)
        {
            Item* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            Item* newItem = new Item(data, temp, NULL);
        }*/

        // Method to insert a value/element 'v' into the list at position 'index'.
        void insert(int index, int v)
        {
            // Check if the provided index is within the list's range.
            if (index < 0 or index > len)
            {
                cout << "Invalid index.\n";
                return;
            }
            Item* temp = head;
            // Input at the start.
            if (index == 0)
            {
                Item* n = new Item(v, NULL, temp);
                if (temp != NULL)
                {
                    temp->prev = n;
                }
                head = n;
            }
            // Input at the end.
            else if (index == len)
            {
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                Item* n = new Item(v, temp, NULL);
                temp->next = n;
            }
            // Input at the given index.
            else
            {
                for (int x = 0; x < index; x++)
                {
                    temp = temp->next;
                }
                Item* n = new Item(v, temp->prev, temp);
                temp->prev->next = n;
                temp->prev = n;
            }
            len++;
        }

        /*void deleteFirst()
        {
            Item* temp = head;
            head = temp->next;
            // May add 'delete temp;'
        }

        void deleteAt(int index)
        {
            Item* temp = head;
            for (int i = 0; i < index-1; i++)
                temp = temp->next;
            temp->next = temp->next->next;
        }

        void deleteLast()
        {
            Item* temp = head;
            while (temp->next->next != NULL)
                temp = temp->next;
            temp->next = NULL;
        }*/

        // Method to delete the Item at the given index.
        void deleteItem(int index)
        {
            // Check if the provided index is within the list's range.
            if (index < 0 or index > len - 1)
            {
                cout << "Invalid index.\n";
                return;
            }
            Item* temp = head;
            // Delete from the start.
            if (index == 0)
            {
                head = NULL;
                if (temp->next != NULL)
                {
                    head = temp->next;
                    head->prev = NULL;
                }
            }
            // Delete from the end.
            else if (index == len - 1)
            {
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->prev->next = NULL;
            }
            // Delete from the given index.
            else
            {
                for (int x = 0; x < index; x++)
                {
                    temp = temp->next;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            len--;
        }

        // Finds the index/position of the provided Item 'i' in the list.
        int findIndex(Item* i)
        {
            // If 'i' is a nullptr, return -1.
            if (i == NULL)
            {
                return -1;
            }
            // 'temp' starts at the 'head' Item; which technically has an "index" of 0. Thus, we set 'c' as 0.
            int c = 0;
            Item* temp = head;
            // While the current Item ('temp') is not equal to / same as 'i', go to next Item (using the -> operator).
            // Incrmeent the counter 'c'.
            while (temp != i)
            {
                temp = temp->next;
                c++;
            }
            // Return the index.
            return c;
        }

        // Output the entire list to the console.
        void print()
        {
            Item* temp = head;
            // While the current Item is not NULL (i.e. is a valid element of the list), print its 'val' and move to the next one.
            while (temp != NULL)
            {
                cout << temp->val << " ";
                temp = temp->next;
            }
            cout << endl;
        }
};

Item* partition(LinkedList* linkedlst, Item* low, Item* high)
{
    int pivot = high->val;
    Item* i = low;
    Item* j = low;
    while (j != high)
    {
        if (j->val <= pivot)
        {
            swap(i->val, j->val);
            i = i->next;
        }
        j = j->next;
    }
    swap(i->val, high->val);
    return i;
}

void quickSort(LinkedList* linkedlst, Item* low, Item* high)
{
    int l = linkedlst->findIndex(low);
    int h = linkedlst->findIndex(high);
    if (l != -1 && h != -1 && l < h)
    {
        Item* lstbreak = partition(linkedlst, low, high);
        quickSort(linkedlst, low, lstbreak->prev);
        quickSort(linkedlst, lstbreak->next, high);
    }
}

/*One-function Quicksort
void quickSort(LinkedList* linkedlst, Item* low, Item* high)
{
    if (low != NULL && high != NULL)
    {
        int l = 0, h = 0;
        Item* temp = linkedlst->head;
        while (temp != low)
        {
            temp = temp->next;
            l++;
        }
        temp = linkedlst->head;
        while (temp != high)
        {
            temp = temp->next;
            h++;
        }
        if (l < h)
        {
            Item* lstbreak = partition(linkedlst, low, high);
            quickSort(linkedlst, low, lstbreak->prev);
            quickSort(linkedlst, lstbreak->next, high);
        }
    }
}*/

int main()
{
    // Creating an object of LinkedList.
    LinkedList* lst1 = new LinkedList();
    // Populating the list.
    lst1->insert(0, 30);
    lst1->insert(1, 3);
    lst1->insert(2, 4);
    lst1->insert(3, 20);
    lst1->insert(4, 5);

    // lst1->insertBeginning(30)
    // lst1->insertAt(1, 3)
    // lst1->insertAt(2, 4)
    // lst1->insertAt(3, 20)
    // lst1->insertLast(5)

    // Printing the initial list.
    cout << "Linked List before sorting\n";
    lst1->print();

    // Get the pointer to the last Item in lst1.
    Item* temp = lst1->head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    // Perform quicksort if the list has two or more Items.
    if (lst1->len > 1)
    {
        quickSort(lst1, lst1->head, temp);
    }

    // Printing the sorted list.
    cout << "Linked List after sorting\n";
    lst1->print();

    // Delete the dynamically-created LinkedList object to preserve memory.
    delete lst1;
}