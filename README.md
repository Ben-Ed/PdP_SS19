![Alt text](https://github.com/Ben-Ed/AuD_SS19/blob/master/ll2.gif?raw=true "Title")

# Programming in Practise - Linked List

Project assignment in the course "Programming in Practice" from summer semester 2019 during my Bachelors in Business Informatics. The task was to implement a singly linked list with several features in C. A linked list is a dynamic data structure, which can have elements added and removed without the need to create a fixed lenght beforehand. The single elements are connected one-way via a pointer, which references the following node. Final Mark: 20/20 Points.
<br> <br> The following is a small showcase of the different functions we had to implement. While this assignment and the concept of linked list are rather basic, it still may help some folks out there. 

## Tasks

 1. Implement a linked list with the following basic functions:
	-	void insert(int v, list * l)
	- 	int delete_head(list * l)
	-	void print list(list l)
	*	void delete all(list l)
	*	int lenght(list l)

2. Add the following advanced functions:
	*	int delete_pos(list ** l, int pos) - Deleting the list element on the position *pos* within the given *list*. If pos is not used, it shall return -1.
	*	int delete_elem(list * l, int e) - Deleting the first occurence of the element e within the given *list*. 
	*	void sort(list * l, int m) - Sorting the given list with bubble sort. Ascending if m >= 0. Ascending, but using the  absolute positive values else.
		
3. Within the main function, implement a list with 3 elements and test the prior functions. <br> <br />


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
Additionally, we rename our structure to *listelement* and the **pointer** to our listelement *list*. It is important to note that list is a pointer, as it is a references the first node of a list. <br> <br />

--- 
#### Exercise 1

> **void insert (int v, list * l)**

With our first function, *void insert*, we create an element carrying the value **v** within our list **l**. 
```c
void insert(int v, list * l) {

  listelement * new;                            //declaring a new list element
  new = malloc(sizeof(listelement));            //we allocate new memory for our new list element

  new->value = v;                               //the value of new is now = v
  new->next = *l;                               //*l is the pointer of our original first element. New now points to that list element, which is now the second element. 

  *l = new;                                     //*l is now a pointer to our new list element, hence showing again on the first element of our list.
}
```
With insert, we can add new list elements to the beginning within the given list. The original first element will move to the second position, which means it is not the beginning of the list anymore. Our new beginning of the list, the element we just added, is referenced by the name of the list. <br> <br />

---
<br />

> **int delete_head(list * l)**

The next function deletes the first element of a given *list* **l**. 
```c
int delete_head(list * l) {

  if (*l == NULL) return -1;           //returning -1 if the list is empty
  
  list old = *l;                                 
  *l = old->next;                      //*l is now a pointer on the second element (our new first element)

  free(old);                           //we free the *old* pointer

  return 0;    
}
```
After we delete the first element (the head), the list now points to the new first element, our prior second element. <br> <br />

---
<br />

> **int print_list(list l)**

The following shows how we can iterate through the *list* **l**. 
```c
void print_list(list  l){	//alle ELemente der Liste ausgeben
	
	if (l == NULL) printf("leer");
	
	else
		while (l != NULL){  
			printf("%d ", l->value);	
			l = l->next;	
		}	
}
```
As long as the pointer does not point to null (meaning it would be the end of the list), we iterate through every item via our pointers. <br />
The rest of the first exercise can be found in the full solution. <br> <br />

---
<br>
#### Exercise 2

> **int delete_pos(list * l, int pos)**

Deleting a specific element is, compared to the first functions, a little bit more complex. Since the elements are connected to the following nodes, deleting an element not being at the beginning nor the end would tear a "rift". In order to fix this, we need to connect the element prior and the one following our deleted element.
```c
int delete_pos(list * l, int position) {

  if (position == 0){delete_head(l);}
  if (position < 0 | position > (lenght(*l)-1)) return -1;  //if the position is not used within the list

  else {
    if (*l == NULL) return -1;
    
    int count = 1;                    
    list tmp = *l;
    
    while(count < position) {                //we iterate through until come to position
        tmp = tmp->next;                
        count++;}
    
    list dlt = tmp->next;
    tmp->next = dlt->next;                  // we have to connect the element prior to the deleted one with the element following
    free(dlt);                                      
  } return 0;}
```
We iterate through the list until we reach our designated goal - the element which is going to be deleted. However, we do not stop right on the position, but one position before. We do this to close the beforementioned rift we would create. 

<br>

---

<br />

> **int delete_elem(list * l, int e)**

This function is similiar to the prior. However, instead of stopping at a given parameter in form of an index, we iterate until we reached the first occurence of the *element **e***.
```c
int delete_elem(list * l, int e) {

if((*l)->value == e) delete_head(l);

list backup = *l;                           //Using a backup to reference the beginning of the list
list tmp = *l;                              //Always one ahead of our normal pointer *l

while((*l)->next != NULL) {
  tmp = (*l)->next;                   

  if(tmp->value == e) {
    (*l)->next = tmp->next;                 //preventing a rift
    free(tmp);
    tmp = NULL;                              

    break;}

  *l = tmp;                                 //*l and tmp iterate through the list until one list if clause is fulfilled
  if((*l)->next == NULL) {    
    *l = backup;
    return -1;}
    }

*l = backup;   
return 0;
}
```
If we iterate with l and tmp being one ahead, we are able to both delete e and connect the two neighbouring elements. 

<br> <br />

---


<br />

> **void sort(list * l, int m)**

The following function implements a bubble sort algorithm. Our m decides whether we use the original elements within the list (if m>=0), or else, the absolute positive values of the elements. We use a swap function to swap (surprising, isn't it) neighbouring nodes. It can be found in the full solution as well.
```c
  void sort(list * l, int m) {            
     
  list tmp = *l;            
  
   if(m < 0) {

     tmp = *l;
     while(tmp != NULL) {                     
  
      if(tmp->value < 0) tmp->value = tmp->value / (-1);   //turning the values into the absolute positive values
      tmp = tmp->next;                       
      tmp = *l;       
   }

   while(* l != NULL && (*l)->next != NULL){ 
    
      if((*l)->next->value >= (*l)->value) *l=(*l)->next;
      else {
      	swap(&(*l)->value, &(*l)->next->value);    //the following value is < than the current one, hence we need to swap them
	*l = tmp;              
		}
	}
	*l = tmp;       
}
```
Our result is a sorted linked list in ascending order. 
<br> <br />
Exercise 3 - the implementation and testing - can be found in the full solution. 

## C ya around
