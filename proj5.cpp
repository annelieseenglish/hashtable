#include "passserver.h"
#include "hashtable.h"
#include <iostream>
#include <string>
using namespace std;

void menu() {
    cout << "\n\n";
    cout << "l - Load from File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "Enter choice: ";
}

int main() {
    PassServer ps(101); // Initialize PassServer with hash table size
    char choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
        case 'l': {
            string filename;
            cout << "Enter the file to be loaded from: ";
            cin >> filename;
            if (ps.load(filename.c_str())) {
                cout << "File loaded successfully!" << endl;
            } else {
                cout << "Could not load file." << endl;
            }
            break;
        }
        case 'a': {
            string user, pass;
            cout << "Enter username: ";
            cin >> user;
            cout << "Enter password: ";
            cin >> pass;
            if (ps.addUser(make_pair(user, pass))) {
                cout << "User successfully added!" << endl;
            } else {
                cout << "Could not add user. Does the username already exist?" << endl;
            }
            break;
        }
        case 'r': {
            string user;
            cout << "Enter the user to be removed: ";
            cin >> user;
            if (ps.removeUser(user)) {
                cout << "User removed successfully." << endl;
            } else {
                cout << "Could not remove user." << endl;
            }
            break;
        }
        case 'c': {
            string user, oldP, newP;
            cout << "Enter username: ";
            cin >> user;
            cout << "Enter old password: ";
            cin >> oldP;
            cout << "Enter new password: ";
            cin >> newP;
            if (ps.changePassword(make_pair(user, oldP), newP)) {
                cout << "Password successfully changed!" << endl;
            } else {
                cout << "Could not change password. Is it the same as the old one?" << endl;
            }
            break;
        }
        case 'f': {
            string user;
            cout << "Enter the user you'd like to find: ";
            cin >> user;
            if (ps.find(user)) {
                cout << "User found!" << endl;
            } else {
                cout << "Could not find user." << endl;
            }
            break;
        }
        case 'd': {
            cout << "Dumping HashTable..." << endl;
            ps.dump();
            break;
        }
        case 's': {
            cout << "The size of the Hash Table is " << ps.size() << endl;
            break;
        }
        case 'w': {
            string filename;
            cout << "Please enter the filename to write to: ";
            cin >> filename;
            if (ps.write_to_file(filename.c_str())) {
                cout << "Success!" << endl;
            } else {
                cout << "Could not write to file." << endl;
            }
            break;
        }
        case 'x': {
            cout << "Exiting program..." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'x');

    return 0;
}
