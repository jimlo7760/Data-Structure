HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  Yanzhen Lu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

ALAC
cplusplus.com
lab TA/mentors
lecture videos

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10h



NAIVE ALGORITHM:

Order Notation: O(w * h * w * h)

Timing Experiment Data:
tiny_5x5.ppm: 0.00s user 0.00s system 63% cpu 0.004 total
small_10x10.ppm: 0.00s user 0.00s system 66% cpu 0.005 total
squiggle_30x30.ppm: 0.01s user 0.00s system 88% cpu 0.019 total
lines_100x100.ppm: 1.16s user 0.02s system 99% cpu 1.188 total
data_structures_300x300.ppm: 85.89s user 1.30s system 98% cpu 1:28.31 total


Discussion:
This algorithm has a relatively bad efficiency, because it have to visit each
pixel twice, which will have 4-nested loop. The num of black pixels will not
impact the efficiency because the only difference between a black and
non-black pixel is doing a mathematics operation, which has little impact on the
overall efficiency.

IMPROVED ALGORITHM:

Order Notation: O(w * h + w * h * p)

Timing Experiment Data:
tiny_5x5.ppm: 0.00s user 0.00s system 48% cpu 0.005 total
small_10x10.ppm: 0.00s user 0.00s system 61% cpu 0.005 total
squiggle_30x30.ppm: 0.00s user 0.00s system 70% cpu 0.006 total
lines_100x100.ppm: 0.03s user 0.00s system 92% cpu 0.038 total
data_structures_300x300.ppm: 5.95s user 0.07s system 99% cpu 6.055 total

Discussion:
This algorithm improved some efficiency from the naive method. Basically, it gain
the timing advantage by sacrificing the memory. Because it has to store the coordinates
of black points as a vector, then traverse the vector for each coordinate and get the
distance to the closest black point and record it as the distance to of the current coordinate.


FAST MARCHING METHOD (with a map):

Order Notation: O(w * h + (w * h - p) * (1 + log (w * h)))

Timing Experiment Data:
tiny_5x5.ppm: 0.00s user 0.00s system 67% cpu 0.005 total
small_10x10.ppm: 0.00s user 0.00s system 72% cpu 0.005 total
squiggle_30x30.ppm: 0.01s user 0.00s system 87% cpu 0.012 total
lines_100x100.ppm: 0.09s user 0.00s system 98% cpu 0.097 total
data_structures_300x300.ppm: 1.28s user 0.02s system 99% cpu 1.302 total

Discussion:
First, like the improved method, it has to traverse the whole image to get the black pixels'
coordinate, and record it into the vector. Then for each coordinate other than the black pixel,
we have to do a percolate up (with avg O(1) complexity) when insert into the priority queue
and percolate down (with average O(log (w * h)) complexity). However, as the size of the picture
is small, it cannot show the advantage of log function, which may spend more than compared to
improved method.


DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
Be kind plz :)





