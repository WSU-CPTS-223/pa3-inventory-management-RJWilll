/*****************************************************************
* Programmer: Reed Williams
* Class: CptS 223, Fall 2025;
* Programming Assignment: PA3
* Date: Oct 10, 2025
* Description: Header file for template class avl_node, which will be
                used as the actual nodes for the self-balancing 
                AVL tree.
*****************************************************************/

#ifndef NODE
#define NODE

#include <iostream>

using namespace std;

template <typename Key, typename Value>
class avl_node
{
public:
avl_node();
avl_node(Key k, Value v);

Key key;
Value value;
int balanceFactor;
avl_node* rNode;
avl_node* lNode;
avl_node* pNode;

private:


};


/*
* Function: avl_node<Key,Value>::avl_node()
* Description: Default constructor for template class avl_node, initalizes data members to null. 
* Input parameters: void
* Returns: N/A
* Preconditions: avl_node<Key,Value> object must be created 
* Postconditions: Initalizes data members to null.
*/
template <typename Key, typename Value>
avl_node<Key,Value>::avl_node()
{
    this->key = NULL;
    this->value = NULL;

    this->balanceFactor = 0;
    this->rNode = nullptr;
    this->lNode = nullptr;
    this->pNode = nullptr;


}

/*
* Function: avl_node<Key,Value>::avl_node(Key k, Value v)
* Description: Parameritized constructor for template class avl_node, initalizes data members key and value by value, 
                with rest of values being default. 
* Input parameters: void
* Returns: N/A
* Preconditions: avl_node<Key,Value> object must be created 
* Postconditions: Initalizes data members.
*/
template <typename Key, typename Value>
avl_node<Key,Value>::avl_node(Key k, Value v)
{
    this->key = k;
    this->value = v;

    this->balanceFactor = 0;
    this->rNode = nullptr;
    this->lNode = nullptr;
    this->pNode = nullptr;
}


#endif //NODE