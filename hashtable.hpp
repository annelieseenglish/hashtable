#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "hashtable.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include<functional>
namespace cop4530 {

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) : currentSize(0) {
	table.resize(size);
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
	makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K &k)  const {
	auto & whichList = table[myhash(k)];
	for (const auto &pair : whichList) {
	   if (pair.first == k) {
		return true;
	   }
	}
   return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const pair<K,V> &kv) const {
	auto& whichList = table[myhash(kv.first)];	//current chain
	for (const auto& pair : whichList) {
	   if (pair == kv) {
		return true;
	   }
	}
   return false;	//if no match found
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const pair<K,V> &kv) {
	auto & whichList = table[myhash(kv.first)];

	if (find_if(begin(whichList), end(whichList),
		[&kv](const pair<K, V>& element) { return element.first == kv.first; })
	!= end(whichList)) {
	   return false;
	}

	whichList.push_back(kv);	//insert new kv pair
	++currentSize;

	//rehash
	if (currentSize > table.size()) {
	   rehash();
	}
	   return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(pair<K,V> &&kv) {
	auto &whichList = table[myhash(kv.first)];

	if (find_if(begin(whichList), end(whichList),	//does key alr exist
		[&kv](const pair<K, V>& element) {return element.first == kv.first; })
	   != end(whichList)) {
	   return false;	//key already exists
	}

	whichList.push_back(move(kv));	//put pair in table
	++currentSize;

	if (currentSize > table.size()) {	//rehash if load factor > 1
	   rehash();
	}
   return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K &k) {
	auto & whichList = table[myhash(k)];
	auto itr = find_if(whichList.begin(), whichList.end(), [&k](const pair<K, V> & pair) {
	   return pair.first == k;
	});

	if (itr == whichList.end()) {
	   return false;
	}

	whichList.erase(itr);
	--currentSize;
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::clear() {
	makeEmpty();	//clear table
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
	ifstream file(filename);
	if (!file.is_open()) {
	   return false;	//cant open file
	}

	K key;
	V value;
	while (file >> key >> value) {
	   insert(make_pair(key, value));	//insert pairs from files
	}
   return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const {
	for (size_t i = 0; i < table.size(); ++i) {
	   const auto& chain = table[i];
	   if (!chain.empty()) {
		cout << i << ": ";
		for (const auto& pair : chain) {
		   cout << pair.first << " -> " << pair.second << "; ";
		}
	cout << endl;
    }
  }
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {
	return currentSize;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const {
	ofstream file(filename);
	if (!file.is_open()) {
	   return false;
	}

	for (const auto& chain : table) {
	   for (const auto& pair : chain) {
		file << pair.first << " " << pair.second << endl;
	   }
	}
    return true;
}

////////PRIVATE//////////////////////////////////////////

template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
	for (auto& thisList : table) {
		thisList.clear();
	}
    currentSize = 0;
}

template <typename K, typename V>
void HashTable<K, V>::rehash() {
	auto oldTable = table;	//copy the current table
	table.resize(prime_below(2 * table.size()));	//resize
	for (auto &chain : table) {
	   chain.clear();
	}
	currentSize = 0;

	for (const auto &chain : oldTable) {
	   for (const auto &kv : chain) {
		insert(kv);
	   }
	}
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const {
	hash<K> hashfunction;
	return hashfunction(k) % table.size();
}

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n) {
	const unsigned long max_prime = 1000;

	if (n > max_prime || n == max_prime) {
	   cerr << "** input too large for prime_below()\n";
	   return max_prime;
	}
	if (n <= 1) {
	   cerr << "**input too small \n";
	   return 0;
	}

	//now: 2 <= n < max_prime
	vector<unsigned long> primes(n + 1, 1);;
	setPrimes(primes);
	while (n > 1) {
	   if (primes[n] == 1) {
		return n;
	   }
	   --n;
	}
   return 2;
}

template <typename K, typename V>	//sets all prime indexes to 1
void HashTable<K, V>::setPrimes(vector<unsigned long>& vprimes) {
	size_t n = vprimes.size();
	vprimes[0] = vprimes[1] = 0;
	for (size_t i = 2; i < n; ++i) {
	   if (vprimes[i] == 1) {
		for (size_t j = i * i; j < n; j+= i) {
		   vprimes[j] = 0;
		}
	   }
	}
}


}
#endif
