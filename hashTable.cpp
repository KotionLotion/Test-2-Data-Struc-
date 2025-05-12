#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class HashTable
{
private:
    vector<int> table;
    int size;
    const int EMPTY = -1;
    const int DELETED = -2;

    // Division method hash function
    int hashFunction(int key)
    {
        return key % size;
    }

    // Quadratic probing function
    int quadraticProbe(int key, int i)
    {
        return (hashFunction(key) + i + i * i) % size;
    }

public:
    HashTable(int s) : size(s)
    {
        table.resize(size, EMPTY);
    }

    // Insert using quadratic probing
    void insert(int key)
    {
        if (search(key))
        {
            cout << "Error: Value " << key << " already exists\n";
            return;
        }

        for (int i = 0; i < size; i++)
        {
            int index = quadraticProbe(key, i);
            if (table[index] == EMPTY || table[index] == DELETED)
            {
                table[index] = key;
                cout << "Inserted " << key << " at position " << index << "\n";
                return;
            }
        }
        cout << "Error: Table is full\n";
    }

    // Search using quadratic probing
    bool search(int key)
    {
        for (int i = 0; i < size; i++)
        {
            int index = quadraticProbe(key, i);
            if (table[index] == key)
                return true;
            if (table[index] == EMPTY)
                return false;
        }
        return false;
    }

    // Delete using quadratic probing
    void remove(int key)
    {
        for (int i = 0; i < size; i++)
        {
            int index = quadraticProbe(key, i);
            if (table[index] == key)
            {
                table[index] = DELETED;
                cout << "Removed " << key << " from position " << index << "\n";
                return;
            }
            if (table[index] == EMPTY)
            {
                cout << "Error: Value " << key << " not found\n";
                return;
            }
        }
        cout << "Error: Value " << key << " not found\n";
    }

    void display()
    {
        cout << "\nCurrent Hash Table:\n";
        for (int i = 0; i < size; i++)
        {
            cout << "Index " << i << ": ";
            if (table[i] == EMPTY)
                cout << "Empty";
            else if (table[i] == DELETED)
                cout << "Removed";
            else
                cout << table[i];
            cout << endl;
        }
    }
};

void displayMenu()
{
    cout << "\nHash Table Operations:\n";
    cout << "1. Insert value\n";
    cout << "2. Search value\n";
    cout << "3. Delete value\n";
    cout << "4. Display table\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

int main()
{
    int tableSize;
    cout << "Enter hash table size: ";
    cin >> tableSize;

    while (cin.fail() || tableSize <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid size. Enter positive integer: ";
        cin >> tableSize;
    }

    HashTable ht(tableSize);
    int choice, value;

    do
    {
        displayMenu();
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Enter 1-5: ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid value. Enter integer: ";
                cin >> value;
            }
            ht.insert(value);
            break;

        case 2:
            cout << "Enter value to search: ";
            cin >> value;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid value. Enter integer: ";
                cin >> value;
            }
            cout << (ht.search(value) ? "Found" : "Not found") << endl;
            break;

        case 3:
            cout << "Enter value to delete: ";
            cin >> value;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid value. Enter integer: ";
                cin >> value;
            }
            ht.remove(value);
            break;

        case 4:
            ht.display();
            break;

        case 5:
            cout << "Exiting program\n";
            break;
        }
    } while (choice != 5);

    return 0;
}