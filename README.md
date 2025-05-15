# PassServer Password Management with Hash Tables

This project implements a **password management system** using a custom hash table. It provides a command-line menu that allows you to securely store and manage username-password pairs.

## 📄 Project Files

- `proj5.cpp` — Runs the interactive menu and connects user actions to the PassServer.
- `passserver.h / passserver.cpp` — Encapsulates password management logic, including user authentication and modification.
- `hashtable.h / hashtable.hpp` — Custom hash table implementation using separate chaining and STL containers.

##  Features

The menu allows you to:

- **Load users** from a file
- **Add** a new user
- **Remove** an existing user
- **Change** a user’s password
- **Find** a user in the hash table
- **Dump** the entire hash table content
- **Check** the size of the hash table
- **Write** all users to a file
- **Exit** the program

##  How to Run
1. Compile: g++ hashtable.hpp passserver.cpp proj5.cpp
2. a.out

