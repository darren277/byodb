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

