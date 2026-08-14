#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct student {
      char name[20] ;
      char matricule[20] ;
     struct  student * next ;

}student;//student
  typedef student* postudent ;
	 void addstudent (student s,postudent* potete ){
              student * ajout ;
               ajout = malloc (sizeof(student));
	       ajout ->name[20] =s.name[20];
	       ajout ->next =(*potete) ;
	      * potete=ajout; 

	 } 
  void deletestudent (student ds , postudent* potete ){
      student* pnow ;
      student* previous;
      pnow = *potete;
      previous = pnow ;
      pnow =pnow->next;
      if (pnow->name[20] == ds.name[20]){
      *potete=pnow->next;
      free (pnow);
      }else{
      while (pnow->name[20] != ds.name[20]&& pnow != NULL ){
	      previous=pnow;
              pnow=pnow->next;
      }
          if (pnow == NULL ){
	  printf ("le nom inconnu");
	  }else{
	  previous->next = pnow->next;
	  free(pnow);
	  printf ("operation reussite ");
	  }//if2
      }//if
      
  
  
  }
