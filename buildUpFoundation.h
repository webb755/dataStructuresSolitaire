/*#ifndef buildUpFoundation_H
#define buildUpFoundation_H
#include "stackADT.h"
#include "finalHeader.h"
#include <stdexcept>
#include <string>


struct nodeType
{
    card *info;
    nodeType *link;
    ~nodeType();
};



class buildUpFoundation : public stackADT<card>{
    public:
        //constructor
        buildUpFoundation(int=DEFAULT_STACK_SIZE);
        ~buildUpFoundation();
        buildUpFoundation(const buildUpFoundation& otherStack);

        void initializeStack();
        bool isEmptyStack() const;
        bool isFullStack() const;
        void push(const card &newItem);
        card top() const;
        void pop();
        void purge();
        const static int DEFAULT_STACK_SIZE = 104;

        bool operator ==(const buildUpFoundation&);
        bool operator !=(const buildUpFoundation&);

    private:
        nodeType *stackTop;
        void copyStack(const buildUpFoundation& otherStack);
        int count = 0;
        int maxStackSize;
};



buildUpFoundation::buildUpFoundation(int stackSize){
    if (stackSize <= 0){
        maxStackSize = DEFAULT_STACK_SIZE;
    } else {
        maxStackSize = stackSize;
    }
    stackTop = nullptr;
    count = 0;
}


buildUpFoundation::~buildUpFoundation(){
    initializeStack();
}


buildUpFoundation::buildUpFoundation(const buildUpFoundation& otherStack){
	stackTop = nullptr;
    this->maxStackSize = otherStack.maxStackSize;
    copyStack(otherStack);
}


void buildUpFoundation::initializeStack(){
    nodeType *temp;
    while (stackTop != nullptr){
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
}


bool buildUpFoundation::isEmptyStack() const{
    return (stackTop == nullptr);
}


bool buildUpFoundation::isFullStack() const{
    if (count == maxStackSize){
        return true;
    } else {
        return false;
    }
}


void buildUpFoundation::push(const card& newItem){
    if (isFullStack()){
        throw std::overflow_error("Stack Overflow. Cannot add to full stack.");
    } else {
        nodeType *newNode;
        newNode = new nodeType;
        newNode->info = new card(newItem);
        newNode->link = stackTop;
        stackTop = newNode;
        this->count++;
    }
    
}


card buildUpFoundation::top() const{
    if (stackTop != nullptr)
        return *(stackTop->info);
    else
        throw std::out_of_range("stack is empty.");
}


void buildUpFoundation::pop(){
    nodeType *temp;
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


void buildUpFoundation::purge(){
    this->initializeStack();
}


inline bool buildUpFoundation::operator==(const buildUpFoundation &otherStack)
{
    if (this->top() == otherStack.top())
        return true;
    return false;
}


inline bool buildUpFoundation::operator!=(const buildUpFoundation &otherStack)
{
    if (this->top() == otherStack.top())
        return false;
    return true;
}




void buildUpFoundation::copyStack(const buildUpFoundation& otherStack){
    nodeType *newNode, *current, *previous;
    
    if (stackTop != nullptr){
        initializeStack();
    }

    if (otherStack.stackTop == nullptr){
        stackTop = nullptr;
    }else{
        current = otherStack.stackTop;
        //copy info and link into stackTop
        this->stackTop = new nodeType;
        this->stackTop->info = new card(*(current->info));
        this->stackTop->link = nullptr;
        previous = stackTop;
        current = current->link;

        //copy remaining list items
        while (current != nullptr){
            newNode = new nodeType;

            newNode->info = new card(*(current->info));
            newNode->link = nullptr;
            previous->link = newNode;
            
            previous = newNode;
            current = current->link;
        }

        this->count = otherStack.count;
    }
}


inline nodeType::~nodeType()
{
    delete info;
}


#endif
 */


