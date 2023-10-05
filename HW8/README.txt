HOMEWORK 8: B+ TREES


NAME:  YANZHEN LU


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
cplusplus.com
discussion forum
meeting record

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15h


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I use clion debugger & Dr.memory debugger on submitty on my program.
The example program test the program by a sequence of order.
I also tried to test my program by non-sequence insertion, which may
insert into the middle part of the leaf node, but the splitting / changing pointers
stay the same. Therefore, my program pass my own test. (test order: 1, 6, 2, 5, 3, 4)

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

Extra credit:
I made a three-dimension, which used to store keys in the tree.
Here is the structure:
first-dimension: store the levels in the tree
second-dimension: store the nodes in the current level
third-dimension: store the keys in the current node
For more info. see comments in the print_BFS_pretty function.

Be kind plz :)