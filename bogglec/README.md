# Boggle Solver #
[Programming Assignment 10](http://coursera.cs.princeton.edu/algs4/assignments/boggle.html)

[Checklist](http://coursera.cs.princeton.edu/algs4/checklists/boggle.html)

## Things I've Learned ##
* `#define CHAR_TO_INDEX(c) ((int)c - (int)'A')` is used to convert char to int in C++.
* when going through a for loop, it should be `for (int c = 0 + 'A'; c < R_ + 'A'; c++) {` to make sure it iterates through the correct interval
* When returning a collection (list, queue, bag, vector, etc), usually a copy is made. Apparently sometimes the compiler will automatically make it a reference to save time/space, but I'm not sure if this actually happens. Will need to test.
* Changed so that `myTrieSET::Node` is no longer public, isPrefix and isCurrentString are able to do the job.
* Took advantage of C++ string mutability, so when looking at the next letter, `word.push_back(board_.getLetter())` and then at the end, `word.pop_back`. Very useful for keeping track of Q's as well.
* However, now the prefix query `isPrefix` starts at the root Node every time. Need to figure out how to optimize so that it keeps track of where it left off.
* Successfully implemented a recursive destructor for myTrieSET, by going through each node and deleting any non-NULL connections. 

## To-do list ##
* Figure out how to return the queue/bag iterator for a BoggleSolver iterator. (I think I've got it working.)
* Is there any way to not have to expose the Node structure of myTrieSET? Can prefixQuery return a true/false? - Done
* In addition to the new Node when making the trie, also need to be aware of the new char[M * N * 2] in BoggleSolver - Done
* Figure out the iterator issue.
* Exploit the fact that when a prefixQuery runs, it is the same as the last prefixQuery except for the last letter.