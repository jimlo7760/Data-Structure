HOMEWORK 5: LINKED TRAIN CARS


NAME:  Yanzhen Lu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com
lecture recording
office hour

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25 h



DESCRIPTION OF IMPROVED SHIPFREIGHT ALGORITHM FOR EXTRA CREDIT 
Aiming for optimal (fastest train speed, most freight, fewest number
of engines used, and fewest resulting trains) for any input.  Note:
Student choice on how to prioritze between these goals.  Describe your
priorization and your implementation.

I m prioritizing the most freight, fewest resulting train, fewest number of engine, and the fastest train speed.
By calculating the weight of the freight that is going to add, if adding the freight will not let the train goes down below the
min speed, that means this freight car can be added. If this freight will let the train goes below the min speed, add a engine to it.
These conditions are all under the requirement of "<= the max number of cars" in each train. As the current train has excel this max
number, and there are more freight and more engines can be used, add a brand new train to the vector.



DESCRIPTION OF IMPROVED SEPARATE ALGORITHM FOR EXTRA CREDIT 
Aiming for optimally comfortable trains (smaller values for average
distance to dining and/or larger values for closest engine to sleeper)
and/or optimally handling cases with > 2 engines.  Student choice on how 
to prioritze between these goals.  Describe your priorization and your
implementation.


MISC. COMMENTS TO GRADER:
Be kind plz, appreciate it :)
Optional, please be concise!


