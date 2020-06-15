![Alt text](https://github.com/Ben-Ed/AuD_SS19/blob/master/ll2.gif?raw=true "Title")

# Programming in Practise - Linked List

Project assignment in the course "Programming in Practice" from summer semester 2019 during my Bachelors in Business Informatics. The task was to implement a singly linked list with several features in C. A linked list is a dynamic data structure, which can have elements added and removed without the need to create a fixed lenght beforehand. The single elements are connected one-way via a pointer, which references the following node. Final Mark: 20/20 Points.
<br> <br> The following is a small showcase of the different functions we had to implement. While this assignemt and the concept of linked list are rather basic, it still may help some folks out there. 

## Tasks

 1. Implement a linked list with the following basic functions:
	-	void insert(int v, list * l)
	-	void delete all(list l)
	-	void print list(list l)
	*	int delete_head(list * l)
	*	int lenght(list l)

2. Add the following advanced functions:
	*	int delete_pos(list ** l, int pos) - Deleting the list element on the position *pos* within the given *list*. If pos is not used, it shall return -1.
	*	int delete_elem(list * l, int e) - Deleting the first occurence of the element e within the given *list*. 
	*	void sort(list * l, int m) - Sorting the given list with bubble sort. Ascending if m >= 0. Ascending, but using the  absolute positive values else.
		
3. Within the main function, implement a list with 3 elements and test the prior functions.


## Solution
The full solution is uploaded, too. However, I will only discuss the crucial parts. Also, bear in mind that the full solution is in german. 

#### Starting with the fundamentals

We start with creating the single element of a list itself, called structure or compound datatype. 
```c
struct le {
    int value;              //the elements within the nodes are integers
    struct le * next;       //pointer to another list element
};

typedef struct le listelement;           
typedef listelement * list; 
```
*Value* is, surprisingly, the value of each node, while *next* is a pointer to another list element / node. Since we want the pointer to reference another structure, it needs to be declared with *struct le*.
Additionally, we rename our structure to *listelement* and the **pointer** to our listelement *list*.

### Exercise 1

> **a)** void insert.
