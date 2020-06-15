![Alt text](https://github.com/Ben-Ed/AuD_SS19/blob/master/ll2.gif?raw=true "Title")

# Programming in Practise - Linked List

Project assignment in the course "Programming in Practice" from summer semester 2019. The task was to implement a singly linked list with several features in C. A linked list is a dynamic data structure, which can have elements added and removed without the need to create a fixed lenght beforehand. The single elements are connected one-way via a pointer, which references the following element. 
Final Mark: 20/20 Points.

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
