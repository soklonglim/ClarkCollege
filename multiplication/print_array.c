//
//Soklong Lim
//CSE224
//Homework #4
//October 24, 2014
//
//---Description---
//this code will accept an array and its length then print out the result of 
//the product of each element in the array.
//
//
//

#include <stdio.h>

void print_array( int *array, int str_len)
{
 
  int m; //loop counter
  int answer; 

  answer = mul_array( array, str_len); //get the result from mul_array

  if(answer == -1 && str_len == 0); //check if anwer = -1 but array lenth is '0' 
                                    //then do nothing 
  else { 
    for(m=0; m<str_len; m++){ //loop to print out the output

      printf("%i", array[m]); //print each element of an array
   
      if( m<(str_len-1)){ //condition to keep # of '*' one less than # of array element
        printf("*"); //print each '*' after each element of an array
      } //end of if
      
      if((m+1)==str_len){ //print the last part of required format
        printf("=%i\n\n", answer); //print out the '=' and answer to get the format
      } //end of if                // a*b*c*d=answer
 
    } //end of for

  } //end of else
} //end of main
