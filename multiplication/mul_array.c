//
//Soklong Lim
//CSE224
//Homework #4
//October 24, 2014
//
//
//---Description---
//this code will take the inputs that have been stored in an array and its length
//then mulitply each integer together. Finally, it returns the result 
//
//
//
#include <stdio.h>

int mul_array( int *array, int str_len)
{
  int k, tmp;

  if(-1 != str_len){ //check array length
    tmp = 1; //to make sure when 'tmp * array[0] = array[0]' (inside the for loop)

    for(k=0; k<str_len; k++){ //loop for multiply each element of an array

      tmp = tmp * array[k]; //mulitiplication operation

    } //end of for

    return tmp; //return the total result

  } else { 
    return -1; //'-1' will be returned if array length is '0'
  } //end of else

} //end of main


      
