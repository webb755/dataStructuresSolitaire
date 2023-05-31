#include <string>
#include <cstdlib>

/////////////////hashTable class definitions//////////////////
template <class type>
class hashTable{
	public:
		hashTable(int = 104);
		~hashTable();
		void insertLinearProbe(type);
		int getNumberOfCollisions();
		void insertRandomProbe(type);
		type at(int);
		int getSize();

	private:
		type* ht;
		int sizeOfHT;
		int numberOfCollisions = 0;
		int itemCount;
};

template <class type>
inline hashTable<type>::hashTable(int size){
	this->sizeOfHT = size;
	ht = new type[size];
	itemCount = 0;
}

template <class type>
inline hashTable<type>::~hashTable()
{
	delete [] ht;
}

template <class type>
inline void hashTable<type>::insertLinearProbe(type object){
	bool found = false;
	int current = object.hash() % this->sizeOfHT;
	if (ht[current] == *(new type)/*nullptr*/){
		ht[current] = object;
		itemCount++;
	}
	else if (ht[current] != *(new type)/*nullptr*/){
		//use linear probe
		bool found = false;
		while (!found){
			numberOfCollisions++;
			current = (current + 1) % 50;
			if (ht[current] == *(new type)/*nullptr*/){
				ht[current] = object;
				found = true;
				itemCount++;
			}
		}
	}
}

template <class type>
inline int hashTable<type>::getNumberOfCollisions(){
    return numberOfCollisions;
}

template <class type>
inline void hashTable<type>::insertRandomProbe(type object){
	bool found = false;
	int current = object.hash() % this->sizeOfHT;
	if (ht[current] == *(new type)){////////////////////////////////////
		ht[current] = object;
		itemCount++;
	}
	else{/////////////////////////
		//use random probe
		bool found = false;
		while (!found){
			numberOfCollisions++;
			current = (current + (std::rand() % 52)) % 52;
			if (ht[current] == *(new type)){
				ht[current] = object;
				found = true;
				itemCount++;
			}
		}
	}
}

template <class type>
inline type hashTable<type>::at(int index)
{
    return (ht[index]);
}

template <class type>
inline int hashTable<type>::getSize()
{
    return itemCount;
}
