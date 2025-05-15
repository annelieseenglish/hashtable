#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<vector>
#include<string>
#include<list>
#include<utility>
#include<iostream>
using namespace std;

namespace cop4530 {
   template <typename K, typename V>
   class HashTable {
      public:
	HashTable(size_t size = 101);	//constructor
	~HashTable();	//destuctor, deletes all elements
	bool contains(const K& k) const;	//check if key k in hashtable
	bool match(const pair<K,V> &kv) const;	//check if key-val pair in hashtable
	bool insert(const pair<K,V> &kv);	//add kv into hash table
	bool insert(pair<K,V> &&kv);	//move version of above
	bool remove(const K& k);	//delete key k
	void clear();	//delete all elements in hash table
	bool load(const char *filename);	//load content of file w name filename into hashtable
	void dump() const;	//display all entries in hash table
	size_t size() const;	//return num elements in hash table
	bool write_to_file(const char *filename) const;	//write all elements in hashtable into filename file

      private:
	vector<list<pair<K, V>>> table;
	size_t currentSize;
	void makeEmpty();	//delete all elements in hash table
	void rehash();	//rehash function
	size_t myhash(const K &k) const;	//return index of vector entry
	unsigned long prime_below(unsigned long);	//determine proper prime numbers used in setting vector size
	void setPrimes(vector<unsigned long>&);
   };
};

#endif
