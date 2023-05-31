#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"
//had to change nodeType to node
template <class Type>
class foundationList: public linkedList<Type>
{
	public:
		bool search(const Type& searchItem) const;
		void insert(const Type& newItem);
		void deleteNode(const Type& deleteItem);
		Type at(int);
		int getSize();
		//void print() const;
		
		void divideList(node<Type>* first1, node<Type>* &first2);
		node<Type>* mergeList(node<Type>* first1, node<Type>* first2, int (*func)(Type,Type));
		void recMergeSort(node<Type>* &first, int (*func)(Type,Type));
		void mergeSort(int (*func)(Type,Type));
		//Type foundationList<Type>::operator[](int i);
	
		//void insertFirst(const Type& newItem);
		//void insertLast(const Type& newItem);
	protected:
		int count;
		node<Type> *first;
		node<Type> *last;

};

template <class Type>
bool foundationList<Type>::search(const Type& searchItem) const
{
    node<Type> * current;
    bool found = false;
    current = this->first;
    while(current != nullptr && !found)
    {
        if(*(current->info) == searchItem)
        {
            found = true;
        }
        else 
        {
            current = current->link;
        }
    }
    return found;
}

template <class Type>
void foundationList<Type>::insert(const Type& newItem)
{
    node<Type> * newNode;
    newNode = new node<Type>;
    newNode->info = new Type(newItem);
    newNode->link = nullptr;
    if(this->isEmptyList())
    {
        this->first = newNode;
        this->last = newNode;
        this->count++;
    }
    else
    {
        this->last->link = newNode;
        this->last = newNode;
        this->count++;
    }
}

template <class Type>
void foundationList<Type>::deleteNode(const Type& deleteItem)
{
	node<Type> * current;
	node<Type> * trailCurrent;
	bool found;
	
	if(this->first == nullptr)
		throw std::out_of_range("Cannot delete from empty list.");
	else
	{
		if(*(this->first->info) == deleteItem)
		{
			current = this->first;
			this->first = this->first->link;
			this->count--;
			if(this->first == nullptr)
				this->last = nullptr;
			delete current;
		}
		else 
		{
			found = false;
			trailCurrent = this->first;
			current = this->first->link;
			while(current != nullptr && !found)
			{
				if(*(current->info) != deleteItem)
				{
					trailCurrent = current;
					current = current->link;
				}
				else
					found = true;
			}
			if(found)
			{
				trailCurrent->link = current->link;
				this->count--;
				if(this->last == current)
					this->last = trailCurrent;
				delete current;
			}
			else 
				throw std::out_of_range("Item not found in list. Cannot delete.");
		}
	}
}

template <class Type>
inline Type foundationList<Type>::at(int i)	//
{
	if(i > this->count - 1 || i < 0)
		throw std::out_of_range("Position is outside the foundation list");
	linkedListIterator<Type> it = this->begin();
	for (int j = 0; j < i; j++)
	{
		++it;
	}
	return *it;
}
template <class Type>
inline int foundationList<Type>::getSize()
{
    return count;
}
/*
template<class Type>
Type foundationList<Type>::operator[](int i)
{
    if(i > this->count -1 || i < 0)
        throw std::out_of_range("Position is outside the foundation list");
    linkedListIterator<Type> it = this->begin();
    for (int j = 0; j < i; j++)
    {
        ++it;
    }
    return *it;
}
 */
/*
template <class Type>
void foundationList<Type>::print() const{
    node<Type> * current;
    current = first;
    while(current != nullptr)
    {
        std::cout << *(current->info) << std::endl;
        current = current->link;
    }
}
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
void foundationList<Type>::divideList(node<Type>* first1, node<Type>* &first2){
	node<Type>* middle;
	node<Type>* current;

	if(first1 == nullptr)	//if list is empty make both null
		first2 = nullptr;
	else if(first1->link == nullptr)	//if only one element
		first2 = nullptr;	
	else{
		//set middle to start and current two node afirst
		middle = first1;
		current = first1->link;
		if (current != nullptr)
			current = current->link;

		while(current != nullptr){
			//advance middle once
			middle = middle->link;
			//advance current twice
			current = current->link;
			if (current != nullptr)
				current = current->link;
		}

		first2 = middle->link;	//starts with first node of second sublist
		middle->link = nullptr;			//reset middle
	}
}

template<class Type>
node<Type>* foundationList<Type>::mergeList(node<Type>* first1, node<Type>* first2, int (*func)(Type,Type)){
	node<Type> *lastSmall;	//points to last node of new merged list
	node<Type> *newfirst;	//points to start of new merged list

	if(first1 == nullptr)	//if first sublist is empty
		return first2;
	else if(first2 == nullptr)	//second sublist is empty
		return first1;
	else{	//comparing first nodes
		if (func (*(first1->info), *(first2->info)) == -1){
			newfirst = first1;
			first1 = first1->link;
			lastSmall = newfirst;
		}else{
			newfirst = first2;
			first2 = first2->link;
			lastSmall = newfirst;
		}

		while (first1 != nullptr && first2 != nullptr){	//loop iterates through rest of sublists
			if (func (*(first1->info), *(first2->info)) == -1){	// for <
				lastSmall->link = first1;
				lastSmall = lastSmall->link;
				first1 = first1->link;
			}else{
				lastSmall->link = first2;
				lastSmall = lastSmall->link;
				first2 = first2->link;
			}
		}

		if (first1 == nullptr)
			lastSmall->link = first2;
		else
			lastSmall->link = first1;

		return newfirst;
		}
	}

template <class Type>
void foundationList<Type>::recMergeSort(node<Type>* &first, int (*func)(Type,Type)){
	node<Type> *otherfirst;
	if (first->link != nullptr && first->link != nullptr){
		divideList(first, otherfirst);
		recMergeSort(first, func);
		recMergeSort(otherfirst, func);
		first = mergeList(first, otherfirst, func);
	}
}

template<class Type>
void  foundationList<Type>::mergeSort(int (*func)(Type,Type)){
	recMergeSort(this->first, func);
	if(this->first == nullptr)
		this->last = nullptr;
	else{
		this->last = this->first;
		while(this->last->link != nullptr)
			this->last = this->last->link;
	}
}

/* template<class Type>
void insertFirst(const Type& newItem){
	insert(newItem);
}

template<class Type>
void insertLast(const Type& newItem){
	insert(newItem);
}
	 */
	
#endif