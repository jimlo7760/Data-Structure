HOMEWORK 6: INVERSE WORD SEARCH


NAME:  Yanzhen Lu


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com
lecture video
discussion forum

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15h


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?
O((r+f) + ((w*h)*(l) + (r*l)*(w*h) + (f*l)*(w*h))*s + (f*l)*s + (w*h)^26+(f*l)* + (f*l)*(w*h)*s) + s*(w*h))
(r+f): store the require words to a list, forbidden words to a matrix

(w*h)*(l) check if the current required word has existed in the matrix
(r*l)*(w*h) create a matrix with the given required words
(f*l)*(w*h) check if the current grid contain forbidden words
((w*h)*(l) + (r*l)*(w*h) + (f*l)*(w*h))*s (summerize above): add-word process

(f*l)*s check if the solutions contain forbidden words
(w*h)^26 filled every gap with 26 letters

(f*l)*(w*h)*s check if contain forbidden words after filling zeros

s*(w*h) output


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
Plz be kind! Appreciate!

