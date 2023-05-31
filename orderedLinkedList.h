/* Program name: vendingMachine.cpp
* Author: Ben Webb
* Date last updated: 2/8/23
* Purpose: use linked list to simulate vending machine
*/

#ifndef ORDERED_H
#define ORDERED_H
#include "linkedList.h"
#include <stdexcept>

//make sure when you are adding nodes to the ordered linked list you are properly setting up the data the node contains.  
//That data is being kept in a pointer in the node class you will need to dynamically allocate memory when setting the data.

template<class type>
class orderedLinkedList : public linkedList<type>{
    public:
        //define virtual functions provided by linkedList
        bool search(const type& searchItem) const;
        void insertFirst(const type& newItem);
        void insertLast(const type& newItem);
        void deleteNode(const type& deleteItem);

        //adding insert function to add to middle of list
        void insert(const type& newItem);
};


//inherited functions from linkedList

template<class type>
bool orderedLinkedList<type>::search(const type& searchItem) const{
    bool found = false;
    node<type> *current;

    current = this-> first;
    while (current != nullptr && !found){
        if (*(current->info) >= searchItem) 
                { found = (*(current->info) == searchItem);
                  return found; 
                }
        else    { current = current->link; }       
    }

    return found;
}

//only defining these two because we must define abstract functions
//we use insert(newItem) to insert into sorted list so we call it here
template<class type>
void orderedLinkedList<type>::insertFirst(const type& newItem)  { insert(newItem);    }

template<class type>
void orderedLinkedList<type>::insertLast(const type& newItem)   {  insert(newItem);    }


template<class type>
void orderedLinkedList<type>::deleteNode(const type& deleteItem){
    node<type> *current;
    node<type> *trailCurrent;
    bool found;

    if (this->first == nullptr){
        std::cout << "cannot delete from empty list" << std::endl;
    } else {
        current = this->first;
        found = false;

        //traverse list to find spot where item is/should be
        while (current != nullptr && !found){
            if (*(current->info) >= deleteItem){
                found = true;
            } else {
                trailCurrent = current;
                current = current->link;
            }
        }

        if (current == nullptr)     {   throw std::out_of_range("item not in list");  }
        else{
            if (*(current->info) == deleteItem){    //if item matches
                if (this->first == current){        
                    //if first item is to be deleted
                    this->first == this->first->link;
                    if (this->first = nullptr)  {   this->last = nullptr;   }
                    delete current;
                } else {
                    trailCurrent->link = current->link;
                    if (current == this->last)  {   this->last = trailCurrent;  }
                    delete current;
                }
            this->count--;
            }
        }
    }
}


template<class type>
void orderedLinkedList<type>::insert(const type& newItem){
    node<type> *current = nullptr;
    node<type> *trailCurrent = nullptr;
    node<type> *newNode = nullptr;
    bool found = false;

    //load newItem into memory with newNode ptr pointing to it
    newNode = new node<type>;
    newNode->info = new type(newItem);
    newNode->link = nullptr;

    //if new list, add newItem to first space
    if (this->first == nullptr){
        this->first = newNode;
        this->last = newNode;
        this->count++;
    } else {
    //if list had items, search through them to find right place for newNode
        current = this->first;
        found = false;

        while (!found && current != nullptr){
            if (*(current->info) >= newItem){
                found = true;
            } else {
                trailCurrent = current;
                current = current->link;
            }
        }

        if (current == this->first){
        //newItem is smallest, it becomes new first
            newNode->link = this->first;
            this->first = newNode;
            this->count++;
        } else {
        //newItem is somewhere in middle (or end)
            trailCurrent->link = newNode;
            newNode->link = current;
            this->count ++;
        //if item is last
            if (current == nullptr){
                this->last = newNode;
            }
        }
    }
}



#endif