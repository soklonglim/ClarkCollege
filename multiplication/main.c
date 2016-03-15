//
//Soklong Lim
//CSE224
//Homework #4
//October 24, 2014
//
//
//---Description---
//this is the main program that will call: 
//1: read_array, read inputs entered by user then multiply all the numbers,
//and 2: print_array, print out the result of multiplication
//
//

#include <stdio.h>
#include "sum.h"

main()
{

  int array[MAXSIZE+1]; //array of integer with the size of 'MAXSIZE+5'
  int length; //length of array

  length =  read_array(array); //length of the array stored inputs from user

  print_array(array, length); //print the result


} //end of main
