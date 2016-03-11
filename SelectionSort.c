//
//Soklong Lim
//CSE 222
//Programming Assignment #8 (Selection Sort)
//Feb 27, 2015
//
//***Description***
//	this program is about selection sort. it receives one argument integer from user and generation
//random # then store the random # in an unsorted array then copy to a sorted array and start sorting
//process on the sorted array by finding the max # then put it at the very end of the array and repeat
//until done. Finally, it will print out 2 lines output, unsorted list and sorted list.
//
//

#include <stdio.h>
#include <stdlib.h>

main(int argc, char **argv){


	int *unsort, *sort;				
	int arg, val, i, k, m, temp, max;				//arg is the # of data to be sorted


	k = 1;											//initialize counter to 1

	if(argc!=2){									//check for argument
		printf("Either Zero or Too Many Arguments Dectected.\n");
		exit(0);									//quit program
	}

	if(1 == sscanf(argv[1], "%d", &arg)){			//check and store arg[1] as length
		if(arg<=0){									//check if argument <= 0
			printf("Argument Must Be Positive Integer.\n");
			exit(0);								//quit program
		}
	} else {										//no integer detected
		printf("Argument Must Be Positive Integer.\n");
		exit(0);									//quit program
	}

	unsort = malloc((arg+1)*sizeof(int));			//allocate memory
	sort = malloc((arg+1)*sizeof(int));				//'+1' for '\0'

	for(i=0; i<arg; i++){        	                //generate random # and
        unsort[i] = rand()%100000;              	//store in unsored array
    }                                               //generated #s are b/w 0-99999
    unsort[i] = '\0';                               //nulterminate array

	for(i=0; i<arg; i++){							//make a copy of unsorted list
		sort[i] = unsort[i];
	}
	sort[i] = '\0';									//nulterminate array

	val = arg;										//set val to size of the list

	while(k!=arg){
		max = sort[0];								//initialize max to first spot #
		m = 0;										//initialize max locatio to first spot #

		for(i=0; i<val; i++){
			if(max<sort[i]){
				max = sort[i];						//reset max value
				m = i;								//remember location of max
			}
		}

		temp = sort[arg-k];							//swaping process
		sort[arg-k] = sort[m];						//move the found max # to the bottom
		sort[m] = temp;				
		k = k + 1;									//move up one spot for the next max
		val = val - 1;								//shrink list by one after one max found
	}

	printf("\n");
    for(i=0; i<arg; i++){                           //print unsorted list
        printf("%d ", unsort[i]);
    }
    printf("\n");

    for(i=0; i<arg; i++){                           //print sorted list
        printf("%d ", sort[i]);
    }
    printf("\n\n");

	free(unsort);									//free pointer
	free(sort);
}


//------------------------------------------end of code--------------------------------------------
