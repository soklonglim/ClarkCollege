//
//Soklong Lim
//CSE224
//Homework #4
//October 24, 2014
//
//
//---Description---
//this code will capture the inputs, integer only, and store them in an array. 
//Finally, it returns the total number of integers and its length.
//
//

#include <stdio.h>
#include <string.h> 
#include "sum.h"

int read_array( int *array)
{

  char inPut[MAXSIZE+5]; //temperary storage
  int i; //loop counter
  int str_len; //length of input array

  printf("\nMaximum input is %d.\n", MAXSIZE); //mesg of maximum input
  
  for( i=0; i<(MAXSIZE); i++){
   
     if( i==(MAXSIZE-1)){ //check for one last input remaining
      printf("Last Entry: "); //warning mesg for max input reached

     } else { 
      printf("Entery #%i: ", (i+1)); //order of input
     } //end of else 

        if( NULL != fgets(inPut, (MAXSIZE+5), stdin)){ //check if user hit ^D

           if( 0 == strcmp(inPut,"\n")){ //compare if user just hit enter with no input
             if(i==0){
               printf("\n...GoodBye!...\n\n"); //mesg before the program quites
               return (-1); //'-1' will be returned after the program quites
             } else {
               break; //stop capturing input & continue the operation
             } //end of else 

           } else {
             if( 0 != sscanf(inPut, "%i", &array[i])){ //check if user not input integer
                str_len = i+1; //keep track of the length of the input array

             } else {
                printf("\nInputs Have To Be Integer\n...Processing Abort!...\n\n"); //mesg after putting non integer
                return (-1); //'-1' will be returned after the program quites
             } //end of else
           } //end of else

        } else {
           printf("\n\n...Goodbye!...\n\n"); //mesg after user hit ^D
           return (-1); //'-1' will be returned after the program quites
        } //end of else
  } //end of for

  return str_len; //return the value of array length

} //end of main
