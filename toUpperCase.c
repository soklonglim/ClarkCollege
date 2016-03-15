//
//soklong lim
//CSE224
//Homework #3
//Oct 17, 2014
//
//-----*****Description*****----- 
//if user type './up' w/ no argument following, inputs will be read frm stdin to stdout and convert frm lower to uppercase  
//if user type './up' following by filenames, inputs will be read frm each file and display on stdout as well as convert frm lower to uppercase
// 


#include <stdio.h>
#include <ctype.h>
#include <string.h>

main( int argc, char **argv)
{ 
  int i; //loop counter 
  int j; //loop counter
  FILE *fp; //file pointer
  char frm_file[200]; //temperary storage of file content 
  char frm_keyboard[200]; //store data from stdin 

if( argc == 1){  //check if user do not put any argument

 while( NULL != fgets( frm_keyboard, 200, stdin)){ //check if users type ^D then end of operation
  for(j=0; j<strlen(frm_keyboard); j++) //loop for converting to uppercase 
    frm_keyboard[j] = toupper( frm_keyboard[j]); //convert to uppercase
  printf("%s", frm_keyboard); //display stdin to stdout
  
 } //end of while   

} else { //check if use put file name after command

  for( i=1; i<argc; i++) //count # of files or # of arguments excluding './up'
  { 
    printf("File #%d: %s\n", i, argv[i]); //note for file ordering and its name

    fp = fopen( argv[i], "r"); //read from the file

    if( fp == NULL){ //check if the file is readable or found
      printf("!!!!! \"%s\" Is NOT Found.\n\n", argv[i]); //mesg for not found file

    } else { //if the file is readable, the following will be printed

      printf("-----Beginning of \"%s\"-----\n", argv[i]); //note for the beginnig of opened file

      while( NULL != fgets( frm_file, 200, fp)){ //check if end of file
       for(j=0; j<strlen(frm_file); j++) //loop for converting to uppercase
        frm_file[j] = toupper( frm_file[j]); //convert to uppercase
        if( frm_file[strlen(frm_file)-1] = '\n') //remove all the '\n' put by fgets
           frm_file[strlen(frm_file)-1] = '\0'; //replace with '\0' (Nul terminator)

      printf("%s\n", frm_file); //display file contents to stdout
      }

    fclose(fp); //shutdown stream
      printf("-----End of \"%s\"-----\n\n", argv[i]); //note for the end of the opending file

    } //end of else

  } //end of for

 } //end of if

} //end of main
