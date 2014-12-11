#include "HashSet.h"
#include "HashFunc.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

/**
 * Inserts all of the items from the vector into the set and then outputs statistics.
 */
template<class T>
void Test(vector<T> &items, HashSet<T> &set)
{
	for (T& x :items)
	{
		set.Insert(x);
	}
	cout << "Number of items: " << set.Size() << endl;
	cout << "Number of buckets: " << set.NumBuckets() << endl;
	cout << "Actual load factor: " << set.GetLoad() << endl;
	cout << "Max number of items in a bucket: " << set.MaxBucketSize() << endl;
	cout << "Percent of empty buckets: " << set.PercentEmptyBuckets() << endl << endl;

}

int main(int argc, char* argv[])
{
	if(argc != 3) {
		cerr << "Incorrect number of command line arguments." << endl;
		cerr << "Usage: " << argv[0] << " <filename> <loadfactor>" << endl;
		exit(EXIT_FAILURE);
	}
	
	ifstream infile(argv[1]);
	// check to see if file opening succeeded
	if (!infile.is_open()) {
		cout<<"Could not open file\n";
		exit(EXIT_FAILURE);
	}
	
	double loadFactor = stod(argv[2]);
	
	// Read words
	vector<string> words;
	string word;
	while (infile >> word) {
		words.push_back(word);
	}
	
	HashSet<string> setA(HashA, loadFactor);
	cout << "Testing Hash Algorithm A" << endl;
	Test(words, setA);
	
	cout << endl;
	
	HashSet<string> setB(HashB, loadFactor);
	cout << "Testing Hash Algorithm B" << endl;
	Test(words, setB);
	
	cout << endl;
	
	HashSet<string> setC(HashC, loadFactor);
	cout << "Testing Hash Algorithm C" << endl;
	Test(words, setC);
	
	return 0;
}