#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct student {
      char name[20] ;
      char matricule[20] ;
     struct  student * next ;

}student;//student
  student * tete ;
  typedef student* postudent ;
	 void addstudent (student s,postudent  tete ){
              student * ajout ;
               ajout = malloc (sizeof(student));
	       ajout ->name[20] =s.name[20];
	       ajout ->next =* tete;
	       tete=ajout; 

	 } 
  void deletestudent (student s , student * s ){
      student * qet,dele ;

  
  
  }
