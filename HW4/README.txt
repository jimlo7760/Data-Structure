HOMEWORK 4: TOOL RENTAL LISTS


NAME:  Yanzhen Lu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
cplusplus.com
ALAC office hour
lecture recording

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25h



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file: O(i)
each inventory record contribute to 1 complexity

Rental event: O(e*i+i*i*r*c*i) or O(e*i+i*i*r*c*i)
e: loading record
i: check if the item exist in the inventory
i: check the stock of the item in the inventory
i: decrease the item stock in the inventory
q: add the customer into the rent list of the current item
c: check if the customer has existed in rent list
case 1: exist:
r: increase the corresponding item in corresponding item list in customer class
case 2: not exist:
c: sort customer list

Return event - no pending customer(s): O(r*i)
r: check if the current customer rent this item
i: update the customer info of the item in inventory list

Return event - with pending customer(s): O(r*i*p*i*e*i+i*i*r*c*i)
r: check if the current customer rent this item
i: update the customer info of the item in inventory list
p: check the pending list
i: check item stock in inventory list
+(rent event)

Entire program: O(i + e*i+i*i*r*c*i + r*i + r*i+p*i*e*i*i*i*r*c*i)
load inventory + rent event + return event


MISC. COMMENTS TO GRADER:
(optional, please be concise!)
