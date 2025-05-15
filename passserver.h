#include "hashtable.h"
#include<string>
#include<utility>

class PassServer {
   public:
	PassServer(size_t size = 101);	//constructor
	~PassServer();	//destructor
	bool load(const char *filename);	//load password file into hashtable obj
	bool addUser(pair<string, string> &kv);	//add new user and password
	bool addUser(pair<string, string> &&kv);	//move version
	bool removeUser(const string & k);	//delete an exiting user with username k
	bool changePassword(const pair<string, string> &p, const string & newpassword);	//change users passowrd
	bool find(const string & user) const;	//check if a user exists
	void dump();	//displa structure and contents of HashTable
	size_t size() const;	//return HashTable size
	bool write_to_file(const char *filename) const;	//save user/pass combo into a file
   private:
	string encrypt(const string & str);	//encrypt parameter str
	cop4530::HashTable<string, string> table;	//hash table instance
};

