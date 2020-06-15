/* C-Projekt

#include <stdio.h>
#include <stdlib.h>



//Deklarierung des zusammengesetzten Datentyps "le". Struktur eines Listenelements einer einfach verketteten Liste

struct le {

    int value;                        //le hat einen int Wert

    struct le * next;                 //Pointer auf Typ le

};


typedef struct le listelement;               //Umbenennung des Typen le in listelement. => listelement ist zusammengesetzter Datentyp
typedef listelement * list;                  //Umbenennung von listelement * in list. => list ist ein Pointer auf ein listelement





//-----------------------------------------------


//Funktionen für die einfach verkettete Liste. Aufgabe 1)


//-----------------------------------------------


// A) void_insert. Fügt neue, erste Listenelement zur Liste hinzu.
void insert(int v, list * l) {

  listelement * new;                            //neues Listenelement. => new ist Pointer auf ein Listenelement
  new = malloc(sizeof(listelement));            //Speicherreservierung für new

  new->value = v;                               //der Wert (value) von new wird v zugewiesen
  new->next = *l;                               //next (Pointer) von new zeigt jetzt ans Ende der Liste => NULL, da *l dort vorher drauf gezeigt hat

  *l = new;                                     //*l zeigt jetzt auf new, da es das neue, erste Listenelement ist
}



// B) int delete_head. Löscht das erste Listenelement einer Liste.
int delete_head(list * l) {

  if (*l == NULL) return -1;                     //falls die Liste leer ist (== falls *l auf NULL zeigt), return -1
  
  list old = *l;                                 //Pointer old aufs erste Listenelement von list l
  *l = old->next;                                //*l ist nun ein Pointer aufs 2. Listenelement (old->next)

  free(old);                                     //der Pointer aufs 1. Listenelement wird gelöscht / freed

  return 0;                                      //Rückgabe von 0, falls es keine Komplikationen gab
}



// C) void delete_all. Löscht die gesamte Liste.
void delete_all(list l) {

  list next;                                     //Pointer next auf listenelement, um 2 Zeiger zu haben, mit denen man versetzt vorrücken kann

  while (l != NULL) {                            //solange die Liste nicht am Ende ist

    next = l->next;                             //der Pointer next zeigt nun aufs Folgeelement

    free(l);                                    //der Speicherplatz für l wird freigegeben

    l = next;                                   //der Pointer l rückt nun nach und zeigt aufs gleiche Listenelement wie next
  }
}



// D) int lenght. Gibt die Länge der Liste zurück.
int lenght(list l) {

  int counter;                                  //Deklarierung eines Zählers, der die Länge darstellt

  while (l != NULL) {                           //solange die Liste nicht am Ende ist

    counter++;                                  //der Zähler wird um 1 erhöht
    l = l->next;                                //der Pointer l zeigt nun aufs folgeelement
  } 

  return counter;                               //gibt die Länge der Liste zurück
}



// E) void print_list(list l). Gibt die einzelnen Werte der Listenelemente aus
void print_list(list  l){	//alle ELemente der Liste ausgeben
	
	if (l == NULL) printf("leer");
	
	else
	
		while (l != NULL){
		    
			printf("%d ", l->value);
			
			l = l->next;
			
		}
		
}




//-----------------------------------------------


//Funktionen für die einfach verkettete Liste. Aufgabe 2)


//-----------------------------------------------



//int delete_pos(list * l, int position). Löscht das Listenelement aus der Liste auf der Position "position".
int delete_pos(list * l, int position) {

  if (position == 0){                             //falls das 1. Listenelement gelöscht werden soll, wird die Funktion delete_head aufgerufen
      delete_head(l);
  }

  if (position < 0 | position > (lenght(*l)-1)) return -1;  //falls die Position nicht in der Liste ist. Liste beginnt bei 0 und letztes Element ist Länge - 1. Alles darunter, bzw. darüber ist außerhalb des Liste

  else {
    if (*l == NULL) return -1;                    //falls die Liste leer ist, gib -1 zurück

    int count = 1;                                //initialisierung einer count variable, um bis zur Position zu gelangen
    list tmp = *l;
    while(count < position) {                     //solange es nicht an der gewünschten Position ist, wird der Pointer weiter bewegt. Stoppt eine Stelle vor der gewünschten Position, an der das Listenelement entfernt werden soll

        tmp = tmp->next;                            //Pointer zeigt nun aufs Folgeelement
        count++;                                    //count wird erhöht

    }
    
    list dlt = tmp->next;                            //dlt wollen wir löschen und tmp hält auf dem counter, also eine Positon vorher demnach muss dlt einen weiter
    tmp->next = dlt->next;                           // tmp->next = dlt wollen wir löschen dementsprech muss tmp mit dem Element nach dlt verbunden werden damit die Liste bleibt
  
    free(dlt);                                       // dlt wird gelöscht
  }
  return 0; 
} 




//-----------------------------------------------

//Funktionen für die einfach verkettete Liste. Aufgabe 3)

//-----------------------------------------------

//int delete_elem(list * l, int e). Löscht das erste Vorkommen von e in der Liste.
int delete_elem(list * l, int e) {

if((*l)->value == e) {                          //falls das erste Listenelement das zu entfernende Listenelement e ist, wird die Funktion delete_head ausgeführt.

  delete_head(l);                               //löscht das erste Listenelement
  
}



list backup = *l;                               //Erstellung eines backups, damit der Pointer *l am Ende wieder aufs erste Listenelement zeigen kann

list tmp = *l;                                  //Pointer tmp, der versetzt um +1 mit dem Pointer *l benutzt wird

while((*l)->next != NULL) {                             //solange die Liste nicht leer ist

  tmp = (*l)->next;                             //der Pointer tmp zeigt nun auf das folgeelement von *l

  if(tmp->value == e) {                         //falls tmp (bzw. das folgeelement) den gesuchten Wert hat

    (*l)->next = tmp->next;                             //*l zeigt nun auf das übernächste Element (folgeelement von tmp), damit es keinen Bruch in der einfach verketteten Liste gibt

    free(tmp);                                  //Freigabe des reservierten Speicherplatzes von tmp (dem Listenelement)

    tmp = NULL;                                 //tmp zeigt nun auf NULL => Kein dangling Pointer

    break;                                      //While Schleife wird verlassen, da nur das 1. Vorkommen abgefragt wird

  }

  *l = tmp;                                     //*l zieht auf und zeigt jetzt auf das gleiche Listenelement wie tmp. So bewegen sich *l und tmp um 1 versetzt durch die Liste, bis eine der beiden IF Clauses zutrifft

  if((*l)->next == NULL) {                                //falls die Liste am Ende ist und das gesuchte Element e nicht vorkam, wird -1 zurückgegeben. Außerdem wird *l wird auf den Listenanfang gesetzt

    *l = backup;
    return -1;                                 
  }
}

*l = backup;                                    //*l zeigt nun wieder auf den Listenanfang

return 0;
}



//-----------------------------------------------

//Funktionen für die einfach verkettete Liste. Aufgabe 4)

//-----------------------------------------------

//void sort(list * l, int m). Sortiert die Liste nach dem Verfahren "Insertion Sort". Bei positivem Parameter m (oder 0) wird die Liste aufsteigend sortiert, ansonsten werden die Beträge der Liste sortiert.


void swap(int * x, int * y){                    //Hilfsfunktion um 2 Elemente der Liste zu vertauschen
	
  int swap;

	swap = * x;

	* x = * y;

	* y = swap;
  }
 


  void sort(list * l, int m) {            
     
  list tmp = *l;                               //Pointer tmp zeigt wie *l aufs erste Listenelement


   if(m < 0) {                                 //bei negativen Parametern wird die gesamte Liste durchgegangen, um die negativen Zahlen in ihre Beträge umzuwandeln

     tmp = *l;

     while(tmp != NULL) {                     //durchläuft die Liste, bis tmp auf Null zeigt => Listenende
    
      if(tmp->value < 0) {                    //falls der aktuelle Wert negativ ist

      tmp->value = tmp->value / (-1);         //wird er in den Betrag gewandelt. x = -x / (-1)

      }

      tmp = tmp->next;                        //tmp zieht ein Listenelement weiter

     }
      tmp = *l;                               //tmp zeigt letztendlich wieder an den Listenanfang
   }



while(* l != NULL && (*l)->next != NULL){      //solange die Liste nicht am Ende ist (wenn beide Pointer auf NUll zeigen)
    
		if((*l)->next->value >= (*l)->value){      //Ist der folgende Wert größer oder gleich des aktuellen Werts, müssen die jeweiligen 2 Werte nicht getauscht weerden
		
			*l=(*l)->next;                            //der Pointer *l rückt ein Listenelement weiter
		
		}
		
		else {                                     //ansonsten ist der folgende Wert kleiner als der aktuelle => die Werte müssen getauscht werden
		
		swap(&(*l)->value, &(*l)->next->value);    //aufruf der Hilfsfunktion swap um die beiden Werte zu vertauschen
		
		*l = tmp;                                  //*l zeigt nun wieder auf den Listenanfang, damit die Liste erneut von vorne beginnen kann, die Elemente zu untersuchen
		
		}
	}
	
	*l = tmp;                                    //*l zeigt nun wieder an den Listenanfang
}







//-----------------------------------------------

//Main Funktion

//-----------------------------------------------


int main(void) {
  

     printf("\n\n------------------\n\nFunktionen aus Aufgabe 1\n\n------------------\n\n");

 
    list testliste = NULL;                     //Initialisierung einer Testliste
    
    insert(-2, &testliste);                    //einfügen der Werte 
    insert(10, &testliste);
    insert(32, &testliste);
    insert(0, &testliste);
    insert(4, &testliste);
    insert(1, &testliste);
    insert(-9, &testliste);
    
    printf("###### Zu Beginn #####\n");
    printf("Aktuelle Liste: ");
    print_list(testliste);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste));

    printf("\n\n##### Nach Aufruf der Funktion delete_head #####\n");
    delete_head(&testliste);
    printf("Aktuelle Liste: ");
    print_list(testliste);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste));

    printf("\n\n##### Nach Aufruf der Funktion delete_all #####\n");
    delete_all(testliste);
    printf("Aktuelle Liste: ");
    print_list(testliste);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste));
    printf("Da es sich bei delete_all um die unsichere Variante handelt (von ha1.pdf vorgegeben), zeigen die Pointer auf zufällige Adresse und deren Werte\n");


    list testliste2 = NULL;                     //Initialisierung einer 2. Testliste
    
    insert(4, &testliste2);                    //einfügen der Werte 
    insert(-25, &testliste2);
    insert(0, &testliste2);
    insert(22, &testliste2);
    insert(25, &testliste2);
    insert(1, &testliste2);
    insert(-9, &testliste2);


   
    printf("\n\n------------------\n\nFunktionen der Aufgaben 2-4\n\n------------------\n\n");

    printf("###### Zu Beginn #####\n");
    printf("Aktuelle Liste: ");
    print_list(testliste2);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste2));

    printf("\n\n###### Nach Funktion delete_pos. Aufgabe 2) #####\n");
    delete_pos(&testliste2, 5);
    printf("Aktuelle Liste: ");
    print_list(testliste2);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste2));

    printf("\n\n###### Nach Funktion delete_elem. Aufgabe 3) #####\n");
    delete_elem(&testliste2, 25);
    printf("Aktuelle Liste: ");
    print_list(testliste2);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste2));

    printf("\n\n###### Nach Funktion sort mit Paramter 1. Aufgabe 4) #####\n");
    sort(&testliste2, 1);
    printf("Aktuelle Liste: ");
    print_list(testliste2);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste2));

    printf("\n\n###### Nach Funktion sort mit Paramter -1. Aufgabe 4) #####\n");
    sort(&testliste2, -1);
    printf("Aktuelle Liste: ");
    print_list(testliste2);
    printf("\nAktuelle Listenlänge: %d\n", lenght(testliste2));

    printf("\n-------\n");
    printf("\nEnde\n");
    printf("\n-------\n");
    

  
  return 0;
}
