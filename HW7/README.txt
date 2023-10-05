HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  Yanzhen Lu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
cplusplus.com
lecture video
lecture note

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  5h



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move

reading the database/populating your initial data structure:

-q (specific move): O(log(f) + log(m))

-q (all): O(log(f) + m)

-f: O(log(m) + t)

-s: O(log(m) + t)

-d: O(log(m) + log(t))


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
Plz be kind :)





