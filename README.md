# 🇩🇿 History of Algeria Database

> A dynamic data structures project for managing a database of Algerian historical personalities, events, and dates — built in C.

---

##  Overview

This project implements a full-featured database system around Algerian historical data stored in a text file. It covers fundamental data structures — **linked lists**, **stacks**, **queues**, and **binary search trees (BST)** — using both iterative and recursive approaches.

Data in the file follows a specific format:
- Personalities and definitions separated by `=`
- Events separated by `:`
- Important dates enclosed in `{}`

---

##  Project Structure

```
├── src/
│   ├── linked_list.c       # Linked list & queue modules
│   ├── stack.c             # Stack modules
│   ├── bst.c               # Binary Search Tree modules
│   ├── recursion.c         # Recursive modules
│   ├── gui.c               # Graphical interface
│   └── main.c              # Entry point & menu
├── include/
│   ├── linked_list.h
│   ├── stack.h
│   ├── bst.h
│   └── recursion.h
├── data/
│   └── algeria_history.txt # Source data file
├── report/
│   └── report.pdf
└── README.md
```

---

##  Features

###  Linked Lists & Queues
- Load personalities with definitions and dates into linked lists
- Search by date of birth or death
- Sort alphabetically, by name length, or by age
- Add, update, and delete personalities
- Find palindrome names, similar personalities, merge into bidirectional/circular lists
- Convert lists to queues

### Stacks
- Convert merged lists to stacks
- Search, sort, add, update, and delete from stacks
- Convert stacks to queues or sorted linked lists
- Reverse a stack recursively

###  Binary Search Tree (BST)
- Build BST from file or stack
- In-order, pre-order, and post-order traversals
- Insert, delete, update nodes
- Find lowest common ancestor, in-order successor
- Mirror a tree, check balance, merge two BSTs

### Recursion
- Count/remove/replace name occurrences in file
- Generate permutations and subsequences of names/events
- Check palindromes and overlapping date ranges

###  GUI
Built using one of: **GTK+**, **ncurses**, **Raylib**, or **SDL**

---

##  Build & Run

```bash
gcc -o algeria_db src/*.c -Iinclude $(pkg-config --cflags --libs gtk+-3.0)
./algeria_db
```

> Adjust the compile flags based on the GUI library you choose.

---

##  Submission Deadline

**May 14, 2026** — Complete C source code, test suite, and PDF report.

---

## 🏫 Institution

**National School of Cybersecurity (NSCS)**  
Pôle scientifique et technologique Chahid « Abdelhafid Ihaddadène », Sidi Abdallah  
1st Year — Algorithms and Dynamic Data Structures | Academic Year 2025/2026
