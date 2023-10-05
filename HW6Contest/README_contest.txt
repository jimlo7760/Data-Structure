HOMEWORK 6 CONTEST: INVERSE WORD SEARCH


NAME:  Yanzhen Lu


OPTIMIZATIONS:
What did you do?
1. Eliminate all the warnings by converting the data type to same when operating
2. Add a break to the loop where to eliminate the zero-contain matrix since the first "full matrix"
    is found, because all the "full matrix" are added after the "zero-contain" matrix.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

Time for puzzle 1: 0.00s
Time for puzzle 2: 0.00s
Time for puzzle 3: 0.35s
Time for puzzle 4: 0.06s
Time for puzzle 5: 0.13s
Time for puzzle 6: 0.01s
Time for puzzle 7: 41.78s
Time for puzzle 8: 69.46s

According to the outcome above, my program will increase the running time exponentially as
there are more "free-fill" space in the matrix.
The test case that I created is:
2 2
+ ca
There is a total of 7502 solutions of my algorithm, which take 15.88s to solve. As the dimension or
empty space in the matrix increase, there will be a exponential increase in my timing. By contrast,
the less forbidden words will also contribute to the timing exponentially, as more matrices will be
potentially created.