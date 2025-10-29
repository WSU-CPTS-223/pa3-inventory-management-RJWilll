#ifndef HASH
#define HASH

#include <iostream>
#include <cmath>

using namespace std;

template <typename Key, typename Value>
class hashTable
{
public:
hashTable();
void insert(Key& newKey, Value& newValue);
Value search(Key& searchKey);
bool deleteKey(Key& searchKey); //returns 1 if deleted, 0 if not


struct hashEntry
{
    bool isEmpty;
    int insertionAttempts = 0;
    Key key;
    Value data; 

    hashEntry()
    {
        isEmpty = 1;
        insertionAttempts = 0;
        key = Key();
        data = Value();
    } 
};

vector<hashEntry> arr;

};


/*
* Function: hashTable<Key, Value>::hashTable()
* Description: Default constructor for template class hashTable, initalizes array. 
* Input parameters: void
* Returns: N/A
* Preconditions: avl_map<Key,Value> object must be created 
* Postconditions: Initalizes array.
*/
template <typename Key, typename Value>
hashTable<Key, Value>::hashTable()
{
    arr = vector<hashEntry>(30000);
}

/*
* Function: void hashTable<Key, Value>::insert(Key& newKey, Value& newData)
* Description: Inserts data into hashtable.
* Input parameters: Key& newKey, Value& newData
* Returns: void
* Preconditions: N/A. 
* Postconditions: Places data into array.
*/
template <typename Key, typename Value>
void hashTable<Key, Value>::insert(Key& newKey, Value& newData)
{
    int index = 0, tempIndex = 0;
    index = hash<string>{}(newKey) % 30000;

    if(arr[index].isEmpty == 1)
    {
        arr[index].isEmpty = 0;
        arr[index].data = newData;
        arr[index].key = newKey;
        arr[index].insertionAttempts++;
    }
    else
    {
        tempIndex = (int)(index + pow(arr[index].insertionAttempts, 2)) % 30000;

        while(arr[tempIndex].isEmpty == 0)//using quadradic probing
        {
            arr[index].insertionAttempts++;
            tempIndex = (int)(index + pow(arr[index].insertionAttempts, 2)) % 30000;
        }

        arr[tempIndex].isEmpty = 0;
        arr[tempIndex].data = newData;
        arr[tempIndex].key = newKey;
        arr[tempIndex].insertionAttempts++;
    }
}

/*
* Function: Value hashTable<Key, Value>::search(Key& searchKey)
* Description: Returns data from hashtable using key.
* Input parameters: Key& searchKey
* Returns: Value
* Preconditions: searchKey value must be in array. 
* Postconditions: Returns value from key, default Value if not.
*/
template <typename Key, typename Value>
Value hashTable<Key, Value>::search(Key& searchKey)
{
    int index = 0, tempIndex = 0;
    index = hash<string>{}(searchKey) % 30000;

    if(arr[index].key == searchKey)//if works without 
    {
        cout << "Find Successful" << endl;
        return arr[index].data;
    }
    else
    {
        if(arr[index].insertionAttempts > 1)//need to check probing
        {
            for(int i = arr[index].insertionAttempts; i > 1; i--)
            {
                tempIndex = (int)(index + pow(arr[index].insertionAttempts, 2)) % 30000;
                if(arr[tempIndex].key == searchKey)
                {
                    cout << "Find Successful" << endl;
                    return arr[tempIndex].data;
                }
            }
        }

        cout << "Find Unsuccessful" << endl;
        return Value();
    }
}

/*
* Function: bool hashTable<Key, Value>::deleteKey(Key& searchKey)
* Description: Deletes data from hashtable.
* Input parameters: Key& searchKey
* Returns: bool
* Preconditions: searchKey value must be in array. 
* Postconditions: Deletes key if found, returns 1 if deleted, 0 otherwise.
*/
template <typename Key, typename Value>
bool hashTable<Key, Value>::deleteKey(Key& searchKey)
{
    int index = 0, tempIndex = 0;
    index = hash<string>{}(searchKey) % 30000;
    bool success = false;

    if(arr[index].key == searchKey)//if works without 
    {
        arr[index].key = Key();
        arr[index].isEmpty = 1;
        arr[index].data = Value();
        success = true;
    }
    else
    {
        if(arr[index].insertionAttempts > 1)//need to check probing
        {
            for(int i = arr[index].insertionAttempts; i > 1; i--)
            {
                tempIndex = (int)(index + pow(arr[index].insertionAttempts, 2)) % 30000;
                if(arr[tempIndex].key == searchKey)
                {
                    arr[index].key = Key();
                    arr[index].isEmpty = 1;
                    arr[index].data = Value();
                    success = true;
                }
            }
        }
    }

    return success;
}




#endif //HASH