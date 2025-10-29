/*****************************************************************
* Programmer: Reed Williams
* Class: CptS 223, Fall 2025;
* Programming Assignment: PA3
* Date: Oct 10, 2025
* Description: Header file for template class Avl_map, which will be used to
                to store nodes of values.
*****************************************************************/

#ifndef AVL
#define AVL

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include "avl_node.h"
#include "operations.h"

using namespace std;

void Pause();

template <typename Key, typename Value>
class avl_map
{
public:
avl_map();
~avl_map();

void insert(const Key& key, const Value& value); // Inserts key-value pair
void erase(const Key& key); // Removes key-value pair

void printInOrder(void);
void printPreOrder(void);
void updateBalanceFactor(void);
void balance(avl_node<Key,Value>* thisNode);
void rightRotation(avl_node<Key, Value>* thisNode);
void leftRotation(avl_node<Key, Value>* thisNode);

bool isEmpty(void);
void destroyList(void);

avl_node<Key,Value>* root;

class Iterator
{
	private:


	public:
        avl_node<Key,Value>* current;

		Iterator(avl_node<Key, Value>* node) : current(node) {}
        Iterator() : current(nullptr) {}


		Value& operator*()
		{
			return current->value;
		}

		Iterator& operator++()
		{
			if (current != nullptr)
			{
                if(current->rNode != nullptr)
                {
                    current = current->rNode;
                    while(current->lNode != nullptr)
                    {
                        current = current->lNode;
                    } 
                    
                }
                else if(current->pNode != nullptr && current->pNode->value > current->value)
                {
                    current = current->pNode;
                }
                else 
                {
                    current = nullptr;
                }
			}

			return *this;
		}

        Iterator& operator--()//I was having an insane amount of issues with this function giving me memory and linker issues, rewrote it like 20 times.
        {
            avl_node<Key, Value>* node = this->current;

            if (node == nullptr)
            {
                return *this; 
            }

            if (node->lNode != nullptr)
            {
                node = node->lNode;
                while (node->rNode != nullptr)
                {
                    node = node->rNode;
                }
                this->current = node;  
            }
            else
            {
                avl_node<Key, Value>* parentNode = node->pNode;
                while (parentNode != nullptr && node == parentNode->lNode)
                {
                    node = parentNode;
                    parentNode = parentNode->pNode;
                }

                this->current = parentNode;
            }

            return *this;
        }

        Iterator operator--(int)//postincrement
        {
            avl_node<Key, Value>* node = this->current;

            if (node == nullptr)
            {
                return *this; 
            }

            if (node->lNode != nullptr)
            {
                node = node->lNode;
                while (node->rNode != nullptr)
                {
                    node = node->rNode;
                }
                this->current = node;  
            }
            else
            {
                avl_node<Key, Value>* parentNode = node->pNode;
                while (parentNode != nullptr && node == parentNode->lNode)
                {
                    node = parentNode;
                    parentNode = parentNode->pNode;
                }

                this->current = parentNode;
            }

            return *this;
        }




		bool operator==(const Iterator& other) const
		{
			return current == other.current;
		}

        bool operator!=(const Iterator& other) const
		{
			return current != other.current;
		}

        Iterator begin()
        {
            current = this->root;
            if(this->root != nullptr)
            {
                while(current->lNode != nullptr)
                {
                    current = current->lNode;
                }
            }
            return Iterator(this->current);
        }

        Iterator end()
        {
            return nullptr;
        }
	};


Iterator find(const Key& key); // Returns an iterator 


private:
void erase(const Key& key, avl_node<Key,Value>* thisNode);

void printInOrder(avl_node<Key,Value>* thisNode);
void printPreOrder(avl_node<Key,Value>* thisNode);

int updateBalanceFactor(avl_node<Key,Value>* thisNode);

void destroyList(avl_node<Key,Value>* thisNode);

};



/*
* Function: avl_map<Key,Value>::avl_map()
* Description: Default constructor for template class avl_map, initalizes data members to null. 
* Input parameters: void
* Returns: N/A
* Preconditions: avl_map<Key,Value> object must be created 
* Postconditions: Initalizes data members to null.
*/
template <typename Key, typename Value>
avl_map<Key,Value>::avl_map()
{
    this->root = nullptr;
}

/*
* Function: avl_map<Key,Value>::~avl_map()
* Description: Destructor for template class avl_map, destroys list, releases memory from heap. 
* Input parameters: void
* Returns: N/A
* Preconditions: avl_map<Key,Value> object must be destroyed or out of scope. 
* Postconditions: Releases memory from heap, destroys list.
*/
template <typename Key, typename Value>
avl_map<Key,Value>::~avl_map()
{
    this->destroyList();
}

/*
* Function: void avl_map<Key,Value>::insert(const Key& key, const Value& value)
* Description: Insert function for avl_map, takes pair of key and value, allocates new node and initalizes new data,
*               and adds new node of AVL Tree, balancing if needed.
* Input parameters: const Key& key, const Value& value
* Returns: void
* Preconditions: N/A 
* Postconditions: Allocates space for new node, adds node to map, balances tree.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::insert(const Key& key, const Value& value)
{
    avl_node<Key,Value>* pNew = new avl_node<Key,Value>(key, value);
    avl_node<Key,Value>* thisNode = this->root;

    if(pNew != nullptr)
    {

        if(this->isEmpty())
        {
            this->root = pNew;
        }
        else
        {
            while(thisNode != nullptr && thisNode->lNode != pNew && thisNode->rNode != pNew)
            {
                if(pNew->key == thisNode->key)// if repeat
                {
                    cout << "Error, entered repeating key" << endl;
                    Pause();
                    break;
                }

                if(pNew->key < thisNode->key && thisNode->lNode == nullptr)
                {
                    thisNode->lNode = pNew;
                    pNew->pNode = thisNode;
                }
                else if(pNew->key > thisNode->key && thisNode->rNode == nullptr)
                {
                    thisNode->rNode = pNew;
                    pNew->pNode = thisNode;
                }
                else if(pNew->key > thisNode->key)
                {
                    thisNode = thisNode->rNode;
                }
                else if(pNew->key < thisNode->key)
                {
                    thisNode = thisNode->lNode;
                }
            }

            updateBalanceFactor(this->root);
            balance(pNew);
        }
    }
}


/*
* Function: void avl_map<Key,Value>::erase(const Key& key) 
* Description: Shell function for erasing operation in avl_map.
* Input parameters: const Key& key
* Returns: void
* Preconditions: Node of with Key of value key must be in tree.
* Postconditions: Deallocates node of Key key.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::erase(const Key& key) // Removes key-value pair
{
    erase(key, this->root);
}


/*
* Function: typename avl_map<Key,Value>::Iterator avl_map<Key,Value>::find(const Key& key) 
* Description: Find operation for Avl_map, returning iterator of node found.
* Input parameters: const Key& key
* Returns: typename avl_map<Key,Value>::Iterator
* Preconditions: Node of with Key of value key must be in tree.
* Postconditions: Returns iterator of type avl_map containing Key key.
*/
template <typename Key, typename Value>
typename avl_map<Key,Value>::Iterator avl_map<Key,Value>::find(const Key& key) 
{
    avl_node<Key,Value>* thisNode = this->root;

    while(thisNode != nullptr)
    {
        if(thisNode->key == key)//found yippee
        {
            return Iterator(thisNode);
        }
        else if(thisNode->key < key)
        {
            thisNode = thisNode->rNode;
        }
        else if(thisNode->key > key)
        {
            thisNode = thisNode->lNode;
        }
    }

    return Iterator();
}


/*
* Function: void avl_map<Key,Value>::printInOrder(void)
* Description: Shell function to print in order function, prints all entries by key in ascending order.
* Input parameters: void
* Returns: void
* Preconditions: Avl_map cannot be empty.
* Postconditions: Prints node data to screen in ascending order.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::printInOrder(void)
{
    printInOrder(this->root);
    cout << endl << endl;
    Pause();
}

/*
* Function: void avl_map<Key,Value>::printPreOrder(void)
* Description: Shell function for print pre order function, prints all entries by key using pre-order traversal.
* Input parameters: void
* Returns: void
* Preconditions: Avl_map cannot be empty.
* Postconditions: Prints node data to screen using pre order traversal.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::printPreOrder(void)
{
    printPreOrder(this->root);
    cout << endl << endl;
    Pause();
}

/*
* Function: void avl_map<Key,Value>::updateBalanceFactor(void)
* Description: Shell function for update balance factor function, updates balance factor for all nodes in avl_map.
* Input parameters: void
* Returns: void
* Preconditions: Avl_map cannot be empty.
* Postconditions: Modifies balance factor data member. 
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::updateBalanceFactor(void)
{
    updateBalanceFactor(this->root);
}

/*
* Function: void avl_map<Key,Value>::balance(avl_node<Key,Value>* thisNode)
* Description: Avl's self balancing function, self balances tree from thisNode to the root, traversing upward.
* Input parameters: avl_node<Key,Value>* thisNode
* Returns: void
* Preconditions: Avl_map cannot be empty.
* Postconditions: Modifies pointers of nodes, self balances tree.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::balance(avl_node<Key,Value>* thisNode)
{

    if(thisNode != nullptr)//if not reached top of tree
    {
        while(thisNode->balanceFactor < -1 || thisNode->balanceFactor > 1)
        {
            updateBalanceFactor();

            if(thisNode->balanceFactor > 1)//left skewed 
            {
                if(thisNode->lNode->balanceFactor > 0)//LL case
                {
                    rightRotation(thisNode);
                    updateBalanceFactor();

                }
                else if(thisNode->lNode->balanceFactor < 0)//LR case
                {
                    leftRotation(thisNode->lNode);
                    rightRotation(thisNode);
                    updateBalanceFactor();
                }
            }
            else if(thisNode->balanceFactor < -1) //right skewed
            {
                if(thisNode->rNode->balanceFactor < 0)//RR case
                {
                    leftRotation(thisNode);
                    updateBalanceFactor();
                }
                else if(thisNode->rNode->balanceFactor > 0)//RL case
                {
                    rightRotation(thisNode->rNode);
                    leftRotation(thisNode);
                    updateBalanceFactor();
                }
            }
        }

        balance(thisNode->pNode);
    }
}

template <typename Key, typename Value>
void avl_map<Key,Value>::rightRotation(avl_node<Key, Value>* thisNode)
{
    avl_node<Key,Value>* lchild = thisNode->lNode;
    avl_node<Key,Value>* lrchild = lchild->rNode;

    if(thisNode->pNode != nullptr)//if not root
    {
        if(thisNode->pNode->value < thisNode->value)
        {
            thisNode->pNode->rNode = thisNode->lNode;
        }
        else 
        {
            thisNode->pNode->lNode = thisNode->lNode;
        }
    }

    lchild->pNode = thisNode->pNode;
    thisNode->lNode = lrchild;
    if(lrchild != nullptr){ lrchild->pNode = thisNode;}
    lchild->rNode = thisNode;
    thisNode->pNode = lchild;

    if(this->root == thisNode)
    {
        this->root = lchild;
    }
}

template <typename Key, typename Value>
void avl_map<Key,Value>::leftRotation(avl_node<Key, Value>* thisNode)
{
    avl_node<Key,Value>* rchild = thisNode->rNode;
    avl_node<Key,Value>* rlchild = rchild->lNode;

    if(thisNode->pNode != nullptr)//if not root
    {
        if(thisNode->pNode->value < thisNode->value)
        {
            thisNode->pNode->rNode = rchild;
        }
        else 
        {
            thisNode->pNode->lNode = rchild;
        }
    }

    rchild->pNode = thisNode->pNode;
    thisNode->rNode = rlchild;
    if(rlchild != nullptr){rlchild->pNode = thisNode;}
    rchild->lNode = thisNode;
    thisNode->pNode = rchild;

    if(this->root == thisNode)
    {
        this->root = rchild;
    } 
}

/*
* Function: bool avl_map<Key,Value>::isEmpty(void)
* Description: Returns boolean if the avl_map is empty or not
* Input parameters: void
* Returns: bool
* Preconditions: N/A 
* Postconditions: Returns boolean.
*/
template <typename Key, typename Value>
bool avl_map<Key,Value>::isEmpty(void)
{
    return this->root == nullptr;
}

/*
* Function: void avl_map<Key,Value>::destroyList(void)
* Description: Shell function to deallocate all nodes in avl_map.
* Input parameters: void
* Returns: void
* Preconditions: avl_map cannot be empty.
* Postconditions: Deallocates all nodes in list, sets root to nullptr.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::destroyList(void)
{
    destroyList(this->root);
}


/*
* Function: void avl_map<Key,Value>::erase(const Key& key, avl_node<Key,Value>* thisNode)
* Description: Helper function for erase function for avl_map, recursive function that iterates through
*               map, deallocating node that shares same value as key.
* Input parameters: const Key& key, avl_node<Key,Value>* thisNode
* Returns: void
* Preconditions: avl_map cannot be empty.
* Postconditions: Deallocates found node in list.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::erase(const Key& key, avl_node<Key,Value>* thisNode)
{
    avl_node<Key,Value>* tempNode = nullptr;
    avl_map<Key,Value>::Iterator i(thisNode);

    if(thisNode != nullptr)
    {
        if(thisNode->key == key)//delete this Node
        {
            if(thisNode->lNode != nullptr)//replace with a left node, either has both or only left child
            {
                i.operator--();//I was having an insane amount of issues with this function giving me memory and linker issues, had to lookup that i could directly call the overloaded function.
                tempNode = i.current;//get node to replace thisNode
                if(thisNode == this->root){this->root = tempNode;}
                tempNode->rNode = thisNode->rNode;

                if(tempNode != thisNode->lNode)
                {
                    if(tempNode->pNode->key < tempNode->key){tempNode->pNode->rNode = nullptr;}
                    else {tempNode->pNode->lNode = nullptr;}

                    tempNode->lNode = thisNode->lNode;
                    thisNode->lNode->pNode = tempNode;

                }

                if(thisNode->rNode != nullptr)
                {
                    thisNode->rNode->pNode = tempNode;
                }
                tempNode->pNode = thisNode->pNode;
            }
            else if(thisNode->rNode != nullptr)//replace with a right node, only has right child
            {
                tempNode = ++i.current;//get node to replace thisNode
                if(thisNode == this->root){this->root = tempNode;}

                if(tempNode != thisNode->rNode)
                {
                    if(tempNode->pNode->key < tempNode->key){tempNode->pNode->rNode = nullptr;}
                    else {tempNode->pNode->lNode = nullptr;}

                    tempNode->rNode = thisNode->rNode;
                    thisNode->rNode->pNode = tempNode;
                }
 
                tempNode->pNode = thisNode->pNode;
            }
            else//has no leaf nodes
            {
                if(thisNode == this->root)
                {
                    this->root = nullptr;
                }
                else 
                {
                    tempNode = thisNode->pNode;//for balancing
                    if(thisNode->pNode->key < thisNode->key)
                    {
                        thisNode->pNode->rNode = nullptr;
                    }
                    else 
                    {
                        thisNode->pNode->lNode = nullptr;
                    }
                }

            }

            delete thisNode;
            updateBalanceFactor();
            balance(tempNode);
        }
        else if(thisNode->key < key)
        {
            erase(key, thisNode->rNode);
        }   
        else if(thisNode->key > key)
        {
            erase(key, thisNode->lNode);
        }
    }
}

/*
* Function: void avl_map<Key,Value>::printInOrder(avl_node<Key,Value>* thisNode)
* Description: Helper function to print in order function, prints all entries by key in ascending order.
* Input parameters: void
* Returns: void
* Preconditions: Avl_map cannot be empty.
* Postconditions: Prints node data to screen in ascending order.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::printInOrder(avl_node<Key,Value>* thisNode)
{
    if(thisNode != nullptr)
    {
        printInOrder(thisNode->lNode);
        cout << "Key: " << thisNode->key << ", Balance Factor: " << thisNode->balanceFactor << endl;
        printInOrder(thisNode->rNode);
    }
}

/*
* Function: void avl_map<Key,Value>::printPreOrder(avl_node<Key,Value>* thisNode)
* Description: Helper function to print pre order function, prints all entries by key in ascending order.
* Input parameters: void
* Returns: void
* Preconditions: Avl_map cannot be empty.
* Postconditions: Prints node data to screen with pre order traversal.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::printPreOrder(avl_node<Key,Value>* thisNode)
{
    if(thisNode != nullptr)
    {
        cout << "Key: " << thisNode->key << ", Value: " << thisNode->value << ", Balance Factor: " << thisNode->balanceFactor << endl;
        printPreOrder(thisNode->lNode);
        printPreOrder(thisNode->rNode);
    }
}

/*
* Function: void avl_map<Key,Value>::updateBalanceFactor(avl_node<Key,Value>* thisNode)
* Description: Helper function for update balance factor operation, updates balance factor for all nodes.
* Input parameters: void
* Returns: void
* Preconditions: Avl_map cannot be empty.
* Postconditions: Updates balance factor on nodes.
*/
template <typename Key, typename Value>
int avl_map<Key,Value>::updateBalanceFactor(avl_node<Key,Value>* thisNode)
{
    if(thisNode != nullptr)
    {
        int lheight = updateBalanceFactor(thisNode->lNode);//why
        int rheight = updateBalanceFactor(thisNode->rNode);
        thisNode->balanceFactor = lheight - rheight;
        return max(lheight, rheight) + 1;
    }
    else
    {
        return -1;
    }
}

/*
* Function: void avl_map<Key,Value>::destroyList(avl_node<Key,Value>* thisNode)
* Description: Helper function for deallocating all nodes in list. 
* Input parameters: avl_node<Key,Value>* thisNode
* Returns: void
* Preconditions: avl_map cannot be empty.
* Postconditions: Deallocates all nodes in list.
*/
template <typename Key, typename Value>
void avl_map<Key,Value>::destroyList(avl_node<Key,Value>* thisNode)
{
    if(thisNode != nullptr)
    {
        destroyList(thisNode->lNode);
        destroyList(thisNode->rNode);
        delete thisNode;
    }
}



#endif //AVL