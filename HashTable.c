//
//Soklong Lim
//CSE 222
//Programming Assighment #5 (Hash Table)
//Feb 06, 2015
//
//*****Description*****
//
//This program is about Hash Table. Input can be anything. Data can be inserted and removed using
//the commands in the help section. The Hash consists an array with length of "LENGTH" and 
//that each slot stores each memory address of a node contain data and delete flag. Hash function is
//h(key,i)=(sum of the ascii value of each elememt of input + 7i)%LENGTH. Following are the instruction:
// #h		Display help message
// #d word	Delete word from hash table
// #s word 	Search word on hash table
// #p		Display entire hash table
// #Q		Quit the program
// anything	Insert data to hash table
//
//


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LENGTH 23

//funtion declaration--------------------------------------
int hash(char str[], int i);					//hash function
void help();					
int str_cp(char str1[], char str2[]);			//input
int str_cp_key(char str1[], char str2[]);		//keyword
//---------------------------------------------------------

struct hashEntry{
	char *word;
	int delete;
};

main(){

	struct hashEntry myHash[LENGTH];
	char *hashPtr;			//pointer to free memory
	char buff[1027];		//limit entry 1024, command 3 => total 1027
	char keyWord[1024];		//temp holder
 	int keyLen;				//length of each entry
	int key;				//location where to store on myHash
	int i; 					//probing counter
	int num;


	system("clear");											//clear screen
	help();														//help mseg

	for(num=0; num<LENGTH; num++){								//store in myHash 
		myHash[num].word = NULL;
	}

	while(1){													//infinit loop
        printf("\n> ");
        fgets(buff, 1027, stdin);

		if(buff[0] == '#' && buff[1] == 'h'){					//'#h' block --- help
			help();

		} else if( buff[0] == '#' && buff[1] == 'd'){			//'#d word' block --- delete
	      	keyLen = str_cp_key(buff, keyWord);					//copy input and get its length
			key = search(&myHash,keyWord);						//search before deleting, if found, it return the location on the array 
			if(key == -1){										//'-1' means not found
				printf("!!!ERROR!!! <%s>\tNot Found.\n", keyWord);
			} else {
				myHash[key].delete = 1;							//'1' == deleted	
//				free(myHash[key].word);							//free memory
				hashPtr = myHash[key].word;
				free(hashPtr);
				printf("<%s>\tDELETED.\n", keyWord);			//confirm mseg for user
			}
	
		} else if(buff[0] == '#' && buff[1] == 's'){			//'#s word' block --- search
			keyLen = str_cp_key(buff,keyWord);					//copy input and get its length
			if(search(&myHash,keyWord)!= -1){					//!= '-1' = found
				printf("<%s>\tFound\n", keyWord);				//confirm mseg for user
			} else {
				printf("<%s>\tNot Found\n", keyWord);			//confirm mesg for user
			}

		} else if(buff[0] == '#' && buff[1] == 'p'){			//'#p' block --- print
			for(num=0; num<LENGTH; num++){
				printf("%d\t", num);							//print index
				if(myHash[num].word == NULL){					//'NULL' == empty
					printf("<NULL>\n");
				} else { 
					if(myHash[num].delete == 0){				//'0' == data exists
						printf("<%s>\n", myHash[num].word);
					} else if(myHash[num].delete == 1){			//'1' == data was deleted
						printf("<DELETED>\n");
					}
				}
			}

		} else if(buff[0] == '#' && buff[1] == 'Q'){			//'#Q' block --- quit
			for(num=0; num<LENGTH; num++){
				if(myHash[num].word != NULL){					//free all memory before exiting program
//					free(myHash[num].word);
					hashPtr = myHash[num].word;
					free(hashPtr);
				}
			}
			exit(0);

		} else { 												//insert block
			keyLen = str_cp(buff, keyWord);						//copy input and get its length
			if(search(myHash,keyWord) != -1){					//check if exits
				printf("!!!ERROR!!! <%s>\tAlready Exist\n", keyWord);
			} else {
				i = 0;											//initialize probing numer to try from Zero
				while(i<23){
					key = hash(keyWord,i); 						//find spot on the array
					if(myHash[key].word == NULL || myHash[key].delete == 1){
						myHash[key].word = malloc(keyLen+1);	//create a memory block to store input
						if(myHash[key].word == NULL){			
							printf("Out Of Memory.\n");			//fail to allocate memory
						}
						strcpy(myHash[key].word,keyWord);		//store data
						myHash[key].delete = 0;					//set delete to Zero == data exits
						i = 25;									//make i>23 to break 'while loop'
					} else {
						i++;									//increment to find new spot on array
						if(i==23){								//if fail after 23 attemp, hash table is full.
							printf("Hash Is Full.\n");
						}			
					}
				}
			}//end of else
		}//end of else
	}//end of while
}//end of main

//---------------------------------------------------------
	
//hash function--------------------------------------------
int hash(char str[], int i){
	int n, ascii;
	ascii = 0;

	for(n=0; str[n] != '\n' && str[n] != '\0' ; n++){
		ascii = ascii + (int)str[n];						//calculate ascii value of the whole string
	}		
	ascii = (ascii+7*i)%23;									//key calculation
	return ascii;											//return result
}

//search function------------------------------------------
int search(struct hashEntry *array, char str[]){
	int num;
	
	for(num=0; num<LENGTH; num++){
		if(array[num].word == NULL){						//'NULL' no data stored
			//do nothing
		} else if(array[num].delete == 1){					//'0' data was deleted
			//do nothing
		} else {
			if(strcmp(array[num].word,str) == 0){			//compare the input and exiting data
				return num;									//return location on array if found
			}
		}
	}
	return -1;												//not found return '-1'
}

//help function--------------------------------------------
void help(){												//help+instruction information
	printf("\t--->>>!<<<Help>>>!<<<---\n");
	printf("#h\t\tDisplay this help message.\n");
	printf("#p\t\tDisplay entire hash table.\n");
	printf("#Q\t\tQuit the program.\n");
	printf("#s Word\t\tSearch word on hash.\n");
	printf("#d Word\t\tDelete word from hash.\n");
	printf("(anything)\tInsert word into hash.\n\n");
}

//string copy-insert---------------------------------------
int str_cp(char str1[], char str2[]){						//copy input from buffer for Insert section
	int i; 

    for(i=0; str1[i] != '\n' && str1[i] != '\0' && i<1024; i++){
        str2[i] = str1[i];
    }
    str2[i] = '\0';											//nulterminate the end of the string
    return i;												//return the length
}

//string copy-keyword--------------------------------------
int str_cp_key(char str1[], char str2[]){					//copy keyword from buffer for Search or Delete
	int i, len;

	len = 0;
	for(i=3; str1[i] != '\n' && str1[i] != '\0'; i++){		//start with 3 becasue of skipping command '#s ' or '#d '
		str2[i-3] = str1[i];
	}
	str2[i-3] = '\0';										//nulterminate the end of the string
	len = i-3;
	return len;												//return the length
}
//---------------------------end of code----------------------------------------
