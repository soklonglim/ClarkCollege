//
//Soklong Lim
//CSE 224
//HW#7
//November 25, 2014
//
//***Description***
//This program will read the input from keyboard and count each word
//Print out each word and its frequency when user hit ^D(Ctrl-D)
//
//


#include <stdio.h>
#include <string.h>
#include <ctype.h>

main()
{

  char startofword[32]; //var to store one word
  char words[512][32];  //main array storage of all words
  int frm_keyboard;     //var to store one character frm fgetc
  int freq[512];        //freqency of each word
  int eofword=0;        //end of word flag
  int length=0;         //length of each word
  int order;            //loop counter 
  int upBound=0;        //upper boundary of number of words in array
  int returnValue=0;    //return value flag

///////////////////////////////////////////////////////////////////////


  while ( EOF != ( frm_keyboard = fgetc( stdin))){ //capture input frm keyboard
                                                   //until it hits EOF
     frm_keyboard=tolower(frm_keyboard); //convert all input to lowercase
   
     if( frm_keyboard >= 'a' && frm_keyboard <= 'z' && length<32){ //allow only alphabet to form a word
                                                                   //limit each word to 32 char. max.
          startofword[length]=frm_keyboard; //store one character at a time to form a word
          length++;  //increment array index for the next character/Documents/Season 1
          eofword=0; //keep zero value if not encounter any character not betwee a-z
     } else {
          eofword=1; //set value to one to continue to the next 'if' condition
          startofword[length]='\0'; //null terminate the array
          order=0;   //set value to zero to continue to the next 'while' loop
     } //end of else

     if( eofword==1 && length!=0 ){  
           while( order<upBound){ //loop thru each word existing in the array
              if( strcmp( words[order], startofword) == 0){ //compare new word to each of the existing words
                  freq[order]=freq[order]+1; //increment freqency of the word
                  returnValue=1;  //set the flag to one
              } //end of if     
              order++; //increment index
           } //end of while
               
		   if( returnValue!=1 && upBound<512){ //if the flag != 1 & # of word < 512 words
               strcpy( words[upBound], startofword); //copy new word into the main array
               words[upBound][length]='\0'; //null terminate the new string copy
               freq[upBound]=1; //increment the frequency of new word
               upBound++; //increment index of new word for the new coming new word
           } //end of if
           
        returnValue=0; //reset the flag
        startofword[0]='\0'; //clear the string
        length=0; //clear the lenght of the string
     } //end of if
  } //end of while

  for( order=0; order<upBound; order++) //'for' loop to print out the result 
       printf("%+32s : %i\n", words[order], freq[order]); //print each word and its requency

} //end of main
