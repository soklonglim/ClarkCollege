/*
Soklong Lim
CSE 215
Programming Assignment #1
Feb 20, 2015

***Description***
- this program is about Goldbach's Conjecture which means that all 
even number greater than 4 can be written as the sum of two prime numbers.
- the program will prompt use for even number and print the result int each line
with 1 second delay until user hit 'ctrl D'.
*/


#include <stdio.h>
#include <stdlib.h>

#define debug 0
#define time 1						//delay 
	
int isPrime(int number);
		
main(){

	int even, sum;					
	int top;						//hold the prime < user input #
	int bottom = 2;					//hold the smallest prime
	int c, d, w;	
	char buff[10];
	
	c = d = w = 0; 					//set flag
	
	system("clear");

	printf("> ");
	fgets(buff, 10, stdin);
	sscanf(buff, "%d", &even);

	if(even%2!=0){					//check if even
		printf("Not An Even Number.\n");
		exit(0);
	} else if(even<4){				//input must >= 4
		printf("Input Must >= 4\n");
		exit(0);
	}
			
	top = even;	
	
	while(1==1){

		while(c==0){	

			while(1==1){
				if(isPrime(top) == -1){			//not prime
					top = top - 1;				//decrement & recheck
					if(top<1){					//sum not found
						printf("Cannot Find The Sum.\n");
						c = 1; d = 1;			//set flag to 1 (break while)
						break;
					}
				} else {
					break;						//prime found
				}
			}
if(debug==1) printf("found top: %d.\n", top);
	
			while(d==0){
	
				while(1==1){
					if(isPrime(bottom) == - 1){		//not prime
						bottom = bottom + 1;		//increment & recheck
					} else { 
						break;						//prime found
					}
				}
if(debug==1) printf("found bottom: %d.\n", bottom);
	
				sum = top + bottom;					//sum the found primes
if(debug==1) printf("sum: %d.\n", sum);

				if(sum == even){					//done => found the sum of 2 primes
					c = 1;							//set flag to 1 (break while)
					d = 1;							//set flag to 1 (break while)
				} else if(sum>even+5){				//try with different top & bottom primes
					d = 1;
					bottom = 2;
				} else {							//try with different bottom prime
					bottom = bottom + 1;
				}
			}
			
			if(d==1 && c!=1){
				d = 0;								//reset flag
				top = top - 1;						//try smaller prime
				bottom = 2;							//reset to smallest prime
			}
		}//end of c-while

		w = w + 1;									//order
	
		printf("(%2d) %7d + %3d = %7d\n", w, top, bottom, even);
		sleep(time);								//1 sec delay 
		even = even + 2;							//next even #		
		top = even;
		bottom = 2;									//reset to smallest prime
		c = 0;										//reset flag
		d = 0;										//reset flag

	}//end of loopwhile
}//end of main	
	
	
//isPrime function-------------------------
int isPrime(int number){
	int test;

	for(test=2; test<=number-1; test++){
		if(number%test == 0){
			return -1;		//not prime
		}
	}
	
	if(test==number)
		return 1;			//Yes, prime
}

//----------------------------------------end of code----------------------------------------
