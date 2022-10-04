# What is this?

As a venture into the C programming language, I decided to try out the following tutorial:

https://github.com/cstack/db_tutorial

This is going to be a database built from the ground up.


# Notes:

The creator of the tutorial breaks the abstract architecture (using `sqlite` as an example) of a database down into:
1. A front end which:
* Tokenizes input.
* Parses tokenized input.
* Generates bytecode from the parsed input for the backend VM.
2. A back end which:
* Receives bytecode instructions that operate on a self balancing [B-tree](https://en.wikipedia.org/wiki/B-tree) data structure.
* A pager for I/O and caching operations.

The first step in the tutorial is to create a function that accepts user input so that we can provide it with both database queries as well as "meta-commands".

_"Non-SQL statements like .exit are called “meta-commands”. They all start with a dot, so we check for them and handle them in a separate function."_

# Feature Branches (From Tutorial)

## First Feature Branch: Adding INSERT and SELECT statements

### Accepting and Interpreting Input

First we add our `do_meta_command()` and `prepare_statement()` functions.

We also create our meta command and statement enums.

### Basic Hardcoded Table

Requirements:
1. Support `insert` and `select` operations.
2. Adhere to a simple schema.

_"SQLite uses a B-tree for fast lookups, inserts and deletes."_


## Second Feature Branch: Hard Disk Persistence

Converted in memory table data structure to a hard disk memory pager that writes to and reads from a file.

**DEV NOTE**: I started trying to separate functionality from the main c file. I ended up going down a long rabbit hole about the history and use of header files for compiling from multiple file sources. I also encountered some duplicate imports while trying to compile. For now, rather then be bogged down with these constraints I just wrote a simple Python script for merging separate c files into one right before compilation. See `make main` and the `utils.py` file.


## Third Feature Branch: Cursor and B-Tree

We will now need a cursor in order to traverse the rows in our tables.

The basic insertion functionality for our B-Tree has been implemented.

The next step will be to add search functionality.


## Fourth Feature Branch: Implementing Binary Search for Our B-Tree

Added `table_find()` function which calls another new function called `leaf_node_find()` to perform a binary search on our B-Tree.

Added leaf node splitting functionality to create internal nodes. Also added root creation and tracking functions.

Search functionality was extended by incorporating recursive search of our B-Tree.


**NOTE TO SELF**:
Regarding how we jump from leaf node to leaf node during longer scans:
_"To scan the entire table, we need to jump to the second leaf node after we reach the end of the first. To do that, we’re going to save a new field in the leaf node header called “next_leaf”, which will hold the page number of the leaf’s sibling node on the right. The rightmost leaf node will have a next_leaf value of 0 to denote no sibling (page 0 is reserved for the root node of the table anyway)."_


# Next Steps

There are definitely some ways in which I want to expand on this project:
1. One is that I need more tests. Maybe I'll implement some coverage checks to make quantify progress along that dimension.
2. Create some kind of network accessible server for it so that I can build it and run it on remote servers and access it with a URI string.
3. Add a user system along with password authentication.
4. Elaborate significantly on the querying languge.


# Feature Branches (My Own)

