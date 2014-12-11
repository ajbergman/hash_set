#include "HashFunc.h"
#include <math.h>

using namespace std;

/**
 * 
   MurmurHash2, by Austin Appleby
   a non-cryptographic hash function suitable for general hash-based lookup.

 */
unsigned int HashA(const std::string& s)
{
	int len = s.length();
	unsigned int seed = 234;

	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	// Initialize the hash to a 'random' value

	unsigned int h = seed ^ len;

	// Mix 4 bytes at a time into the hash

	const char * data = s.c_str();

	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h *= m; 
		h ^= k;

		data += 4;
		len -= 4;
	}
	
	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

/**
 * Simple Hash
 * return the sum of the asci numbers for each character
 */
unsigned int HashB(const std::string& s)
{
	unsigned int hashval = 0;
	for(char ch : s){
		hashval += ch;
	}
	return hashval;
}

/**
 * Java String hashCode
 * The hash code for a String object is computed using int arithmetic, where s[i] is the ith character of the string, and it is raised to length-i power.
 * The hash value of the empty string is zero.
 * http://docs.oracle.com/javase/8/docs/api/java/lang/String.html#hashCode--
 */
unsigned int HashC(const std::string& s)
{
	// TODO
	unsigned int sum = 0;
	for(unsigned int i = 0; i < s.length(); i++){
		sum += s[i]*pow( 31, (s.length()-(i+1)) );
	}
	return sum;
}
