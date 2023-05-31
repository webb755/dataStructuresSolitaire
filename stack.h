/* Program name: stack.h
*  Author: Ben Webb
*  Date last updated: 2/14/23
* Purpose: stack data structure
*/

#ifndef STACK_H
#define STACK_H
#include "stackADT.h"
#include <stdexcept>
#include <string>

template <class type>
struct nodeType
{
    type *info;
    nodeType<type> *link;
    ~nodeType();
};


template <class type>
class stackType : public stackADT<type>{
    public:
        //constructor
        stackType(int=DEFAULT_STACK_SIZE);
        ~stackType();
        stackType(const stackType<type>& otherStack);

        void initializeStack();
        bool isEmptyStack() const;
        bool isFullStack() const;
        void push(const type& newItem);
        type top() const;
        void pop();
        void purge();
        const static int DEFAULT_STACK_SIZE = 104;
        int getCount();

        bool operator ==(const stackType&);
        bool operator !=(const stackType&);
        //friend std::ostream& operator<<(std::ostream&, const stackType&);

    private:
        nodeType<type> *stackTop;
        void copyStack(const stackType<type>& otherStack);
        int count = 0;
        int maxStackSize = 104;
};


template <class type>
stackType<type>::stackType(int stackSize){
    if (stackSize <= 0){
        maxStackSize = DEFAULT_STACK_SIZE;
    } else {
        maxStackSize = stackSize;
    }
    stackTop = nullptr;
    count = 0;
}

template <class type>
stackType<type>::~stackType(){
    initializeStack();
}

template <class type>
stackType<type>::stackType(const stackType<type>& otherStack){
	stackTop = nullptr;
    this->maxStackSize = otherStack.maxStackSize;
    copyStack(otherStack);
}

template <class type>
void stackType<type>:: initializeStack(){
    nodeType<type> *temp;
    while (stackTop != nullptr){
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
}

template <class type>
bool stackType<type>::isEmptyStack() const{
    return (stackTop == nullptr);
}

template <class type>
bool stackType<type>::isFullStack() const{
    if (count == maxStackSize){
        return true;
    } else {
        return false;
    }
}

template <class type>
void stackType<type>::push(const type& newItem){
    if (isFullStack()){
        throw std::overflow_error("Stack Overflow. Cannot add to full stack.");
    } else {
        nodeType<type> *newNode;
        newNode = new nodeType<type>;
        newNode->info = new type(newItem);
        newNode->link = stackTop;
        stackTop = newNode;
        this->count++;
    }
    
}

template <class type>
type stackType<type>::top() const{
    if (stackTop != nullptr)
        return *(stackTop->info);
    else
        throw std::out_of_range("stack is empty.");
}

template <class type>
void stackType<type>::pop(){
    nodeType<type> *temp;
    if (stackTop == nullptr){
        throw std::out_of_range("stack is empty.");
    } else {
        //type newt(*(stackTop->info));
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
        count--;
    }
}

template <class type>
void stackType<type>::purge(){
    this->initializeStack();
}

template <class type>
inline int stackType<type>::getCount()
{
    return count;
}

template <class type>
inline bool stackType<type>::operator==(const stackType &otherStack)
{
    if (this->top() == otherStack.top())
        return true;
    return false;
}

template <class type>
inline bool stackType<type>::operator!=(const stackType &otherStack)
{
    if (this->top() == otherStack.top())
        return false;
    return true;
}



template <class type>
void stackType<type>::copyStack(const stackType<type>& otherStack){
    nodeType<type> *newNode, *current, *previous;
    
    if (stackTop != nullptr){
        initializeStack();
    }

    if (otherStack.stackTop == nullptr){
        stackTop = nullptr;
    }else{
        current = otherStack.stackTop;
        //copy info and link into stackTop
        this->stackTop = new nodeType<type>;
        this->stackTop->info = new type(*(current->info));
        this->stackTop->link = nullptr;
        previous = stackTop;
        current = current->link;

        //copy remaining list items
        while (current != nullptr){
            newNode = new nodeType<type>;

            newNode->info = new type(*(current->info));
            newNode->link = nullptr;
            previous->link = newNode;
            
            previous = newNode;
            current = current->link;
        }

        this->count = otherStack.count;
    }
}





#endif

template <class type>
inline nodeType<type>::~nodeType()
{
    delete info;
}
