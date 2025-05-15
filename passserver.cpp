#include "passserver.h"
#include "hashtable.hpp"
#include <iostream>
#include <fstream>
#include <functional> // For  hash
#include <utility>
#include <string>

// Constructor: initialize the hash table with the given size
PassServer::PassServer(size_t size) : table(size) {}

// Destructor
PassServer::~PassServer() {}

// Load usernames and passwords from a file
bool PassServer::load(const char *filename) {
    return table.load(filename);
}

// Add a user with an encrypted password
bool PassServer::addUser(pair<string, string> &kv) {
     string encryptedPassword = encrypt(kv.second);
    return table.insert({kv.first, encryptedPassword});
}

//move version
bool PassServer::addUser(pair<string, string> &&kv) {
        string encryptedPassword = encrypt(kv.second);
        return table.insert({move(kv.first), move(encryptedPassword)});
}

// Remove a user
bool PassServer::removeUser(const string & k) {
    return table.remove(k);
}

// Change a user's password
bool PassServer::changePassword(const pair<string, string> &p, const  string & newpassword) {
    if (!table.contains(p.first)) {
         return false; // User not found
        }

     string oldE = encrypt(p.second);
     string newE = encrypt(newpassword);

    if (oldE == newE) {
        return false; // New password must be different
        }

    if (table.match({p.first, oldE})) {
        return table.insert({p.first, newE}); // Update password
    }
    return false; // Passwords do not match}
}

// Find a user
bool PassServer::find(const string &user) const {
    return table.contains(user);
}

// Dump the contents of the hash table
void PassServer::dump() {
    table.dump();
}

// Get the size of the hash table
size_t PassServer::size() const {
    return table.size();
}

// Write usernames and encrypted passwords to a file
bool PassServer::write_to_file(const char *filename) const {
    return table.write_to_file(filename);
}

// Encrypt the password (simple example using  hash)
string PassServer::encrypt(const  string & str) {
    return  to_string(hash<string>{}(str));
}
