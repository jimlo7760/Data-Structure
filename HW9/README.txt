HOMEWORK 9: MINIBLAST


NAME:  Yanzhen Lu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

ALAC
lab11.cpp
http://www.partow.net/programming/hashfunctions/
cplusplus.com


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  13h


HASH FUNCTION DESCRIPTION

The hash function takes an input string, iterates over each character in the string using a for loop. For each
character, it performs bitwise XOR (^), bitwise left shift (<<), and bitwise right shift (>>)
operations on an initially chosen hash value (1315423911), and adds the ASCII value of the
character to update the hash value. The resulting hash value is then returned as the final
output of the hash function.





HASH TABLE IMPLEMENTATION

The Key Value I store in each slot of the hash table is the a pair. Pair.first refers
to the current k-mer string, Pair.second stores a vectors of integers, containing the index
appears in the genome sequence. When there is a collision, I used linear probing,
which is find the first empty slot after the current index, to store the new Pair.





ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
Created a string to store the whole sequence, which will be L.
Created a string to store the query, which will be q.
Created a hash table to store every kmers in the genome sequence, which will be (L-k).
Created a vector in each slot (each k-mer) to store the indexes found in the genome sequence, p.
overall: L + q + (L-k) * p


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?
insert:
It will hash the k-mer first to get the hash value, which traverse the k-mer. O(k)
Find the first empty slot in the hash table to store the pair. Since the chance of
collision is so low, so we can ignore it. O(1)
Or, if the k-mer has previously existed, push_back the index to its index vector. O(1)
Overall: O(k)

find:
hash the k-mer: O(k)
get the index vector: O(1)
Overall: O(k)

resize:
create a vector with new size, with empty in each slot: O(1)
traverse the old table to get the valid k-mer: O(n), n = size of the hash table
insert into the new table: O(k)
overall: O(n * k)

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
be kind plz ;)