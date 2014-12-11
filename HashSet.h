/**
 * A hash set.
 * Stub written by James Daly, 8 Oct 2014
 * Completed by [YOUR NAME]
 */
#pragma once

#ifndef HASH_SET_H
#define HASH_SET_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

template<class T>
class HashSet
{
public:
	HashSet(std::function<unsigned int(const T&)> hash, double loadFactor);
	HashSet(HashSet<T> &other);
	virtual ~HashSet();
	
	// Supplied Methods
	bool IsEmpty() const { return Size() == 0; }
	unsigned int Size() const { return size; }
	double GetLoadFactor() const { return loadFactor; }
	void DisplayItems() const { ForEach([](const T& item) { std::cout << item << std::endl; }); }
	double GetLoad() const { return ((double)Size()) / (double)NumBuckets(); }
	
	// Methods that you must complete
	unsigned int NumBuckets() const { return table.size(); }
	bool Contains(const T& item) const;
	bool Insert(const T &item);
	bool Remove(const T &item);
	void Clear();
	void ForEach(std::function<void (const T&)> func) const;
	unsigned int MaxBucketSize() const;
	double PercentEmptyBuckets() const;

private:
	unsigned int size;
	double loadFactor;
	std::function<unsigned int (const T&)> hash;
	// You need some data source to store items
	
	vector<vector<T>> table;
	
	// You can put any helper methods here
	void Rehash(){
		vector<vector<T>> temp = table;
		Clear();
		table.resize(NumBuckets()*2);
		for(unsigned int i = 0; i < temp.size(); i++){
			for(unsigned int j = 0; j < temp[i].size(); j++){
				Insert(temp[i][j]);
			}
		}
		
	}
};

/**
 * Default constructor
 */
template<class T>
HashSet<T>::HashSet(std::function<unsigned int(const T&)> hash, double loadFactor):
	size(0),
	loadFactor(loadFactor),
	hash(hash)
{
	// Empty: You can put other initialization information here
	table.resize(10);
}

/**
 * Copy Constructor
 * Uses uniform instantiation to initialize itself
 * and then copies all of the items from the other set
 */
template<class T>
HashSet<T>::HashSet(HashSet<T> &other) :
	HashSet(other.hash, other.loadFactor)
{
	auto insertItem = [=](const T& x){ this->Insert(x); };
	other.ForEach(insertItem);
}

/**
 * Destructor
 * Any cleanup you need to do can be done here
 */
template<class T>
HashSet<T>::~HashSet()
{
	// Empty: You can put any steps necessary for cleanup here
}

/**
 * Returns true iff the item is in the set
 */
template<class T>
bool HashSet<T>::Contains(const T &item) const
{
	unsigned int index = ((hash(item)) % (NumBuckets()));
	if(find(table[index].begin(), table[index].end(), item) != table[index].end()){
		return true;
	}
	return false;
}

/**
 * Inserts the item into the set.
 * Only one copy can exist in the set at a time.
 * Returns true iff the item was successfully added.
 */
template<class T>
bool HashSet<T>::Insert(const T &item)
{
	if(Contains(item)){
		return false;
	} else {
		unsigned int index = ((hash(item)) % (NumBuckets()));
		table[index].push_back(item);
		size++;
		if(size > (NumBuckets() * loadFactor))
			Rehash();
		return true;
	}
}

/**
 * Removes the item from the set.
 * Returns true iff the item was successfully removed.
 */
template<class T>
bool HashSet<T>::Remove(const T &item)
{
	unsigned int index = ((hash(item)) % (NumBuckets()));
	if( find(table[index].begin(), table[index].end(), item) != table[index].end()){
		table[index].erase(find(table[index].begin(), table[index].end(), item));
		size--;
		return true;
	}
	return false;
}

/**
 * Removes all elements from the set.
 */
template<class T>
void HashSet<T>::Clear()
{
	for(unsigned int i = 0; i < table.size(); i++){
		while(table[i].size()> 0){
			table[i].pop_back();
		}
	}
	size = 0;
}

/**
 * Invokes the function once on each item in the set.
 * The exact order is undefined.
 */
template<class T>
void HashSet<T>::ForEach(std::function<void (const T&)> func) const
{
	for(unsigned int i = 0; i < table.size(); i++){
		for(unsigned int j = 0; j < table[i].size(); j++){
			func(table[i][j]);
		}
	}
}

/**
 * Finds the maximum number of items in a bucket.
 */
template<class T>
unsigned int HashSet<T>::MaxBucketSize() const
{
	unsigned int maxSize = 0;
	for(unsigned int i = 0; i < table.size(); i++){
		if(table[i].size() > maxSize)
			maxSize = table[i].size();
	}
	return maxSize;
}

/**
 * Finds which fraction of the buckets are empty
 * The result is returned as a percent
 */
template<class T>
double HashSet<T>::PercentEmptyBuckets() const
{
	double perEmpty = 0;
	for(unsigned int i = 0; i < table.size(); i++){
		if(table[i].size() == 0)
			perEmpty++;
	}
	return (perEmpty/NumBuckets())*100;
	
}

#endif