#include<stdio.h>
#include<stdlib.h>
int fiborec (int num){
if (num == 0 ){
return 1 ;
}else{
	if (num == 1 ) {
	return 1;
	}else {
      return fiborec (num-1)+fiborec(num-2);
}

}
}
int main(){
	int num ;
printf ("give a number");
scanf ("%d",&num);
int x = fiborec(num);
printf ("fibbo of the num %d \n",x);
return 0 ;
}
