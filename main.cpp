#include <iostream>
#include <string>

#include "Headers/entry.h"
#include "Headers/operations.h"
#include "Headers/hash.h"
#include "Headers/avl_map.h"

using namespace std;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, hashTable<string, entry*>& hash, avl_map<string, vector<entry*>>& map)
{
    avl_map<string, vector<entry*>>::Iterator tempIterator;
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        while(line.find("find") != string::npos)//do some clean up to just get the key
        {
            line.erase(line.find("find"), 5);
        }
        cout << *hash.search(line) << endl;
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        while(line.find("listInventory") != string::npos)//do some clean up to just get the key
        {
            line.erase(line.find("listInventory"), 14);
        }
        while(line.find(" ") != string::npos)
        {
            line.erase(line.find(" "),1);
        }
        tempIterator = map.find(line);
        if(tempIterator.current != nullptr)
        {
            for(int i = 0; i < (int)tempIterator.current->value.size(); i++)
            {
                cout << *(tempIterator.current->value[i]) << endl;
            }
        }
        else
        {
            cout << "No Category Found." << endl;
        }
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices
}

int main(int argc, char const *argv[])
{
    string line;
    hashTable<string, entry*> h;
    avl_map<string, vector<entry*>> map;

    parseFile(h, map);
    map.printInOrder();

    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, h, map);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    relieveHeap(h);
    return 0;
}
