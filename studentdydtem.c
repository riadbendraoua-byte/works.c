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
      }//i
       
      void duplicate (postudent tete ) {
      postudent po,pre;
      po=tete;
      char* names ;
      int i = 0 ;
      po=po->next;
      pre = po->next;
      while (po != NULL ){
         while( pre != NULL){
	   if (pre->name == po->name ){
	 * ( names+i) =*( po->name) ;
	   i++;
	   break ; 
	   }else{
	      pre=pre->next;
	   
	   }
	 
	 } 
      po = po->next ;
      }
      for (int l=0;l<=999;l++){
      printf ("this name have a doble%s ",names+l);
      }
      }
      }
