HOMEWORK 2: HOCKEY CLASSES


NAME:  Yanzhen Lu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20h



DESCRIPTION OF 3RD STATISTIC:
Please be concise! (< 200 words)
What question you are trying to answer with your statistic? 
What data did you need to organize? 
What was interesting or challenging about the implementation of this statistic? 

I count the number of committed of each penalty, and sorting them from the highest to the
lowest. In case of the same number committed in two penalties, I will sort it alphabetically.
The new data that I have organised is the new class Penalty, storing the name of the penalty,
as well as the number committed. The challenging thing about this statistics is that I have to
precisely located the keyword of penalty, and then traverse them in the penalty vector to see if
it has existed. If they are not existed, create a new penalty object, otherwise accumulate the
one that already in the vector.

NAME OF FILE WITH SAMPLE OUTPUT FROM 3RD STATISTIC:
Be sure to select (or create) a dataset with interesting results
2012_ecac.txt

< insert filename, file is included with submission >
2012_ecac_custom.txt


MISC. COMMENTS TO GRADER:  
Optional, please be concise!

