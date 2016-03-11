//
//Soklong Lim
//CSE 222
//Programming Assignment #8 (Insertion Sort)
//Feb 27, 2015
//
//***Description***
//	this program is about insertion sort. it receives one argument integer from user and generate random #  
//then store the random # in an unsorted array then start sorting process by picking one # at a time from
//the unsorted list (start at index 0) and insert to the new array (sorted list) by shifting data if neccesary
//to store the # then repeat until done. Finally, it will print out 2 lines output, unsorted list and
//sorted list.
//
//


#include <stdio.h>
#include <stdlib.h>

main(int argc, char **argv){


	int *unsort, *sort, *temp;
    int arg, i, j, k;										//arg is the # of data to be sorted

        
	if(argc!=2){											//check for argument
        printf("Either Zero or Too Many Arguments Dectected.\n");
        exit(0);											//quit program
    }

    if(1 == sscanf(argv[1], "%d", &arg)){					//check and store argv[1] as length
        if(arg<=0){
        	printf("Argument Must Be Positive Integer.\n");
            exit(0);										//quit program
		}
    } else {												//if integer detected
        printf("Argument Must Be Positive Integer.\n");
        exit(0);											//quit program
    }

	unsort = malloc((arg+1)*sizeof(int));					//allocate memory
	sort = malloc(arg*sizeof(int));							//'+1' for '\0'

	for(i=0; i<arg; i++){									//generate random # and 
		unsort[i] = rand()%100000;							//store in unsored array
	}														//generated #s are b/w 0-99999
	unsort[i] = '\0';										//nulterminate array	

	for(i=0; i<arg; i++){
	    if(i==0){											//direct insert for 1st #
    	    sort[i] = unsort[i];
        } else {
            for(j=0; j<i; j++){
	            if(sort[j] > unsort[i]){					//if smaller # found 
	                for(k=i; k>j; k--){						//perform shifting process by
    	                sort[k] = sort[k-1];				//moving up one spot
                    }
                    sort[j] = unsort[i];					//store data in after shifting
                    j = 4*i;								//break for-loop
                }
            }

            if(j==i){										//direct insert at the end 
	 	       sort[i] = unsort[i];							//when all #s in sorted array
            }												//are smaller than entry #
        }
    }

	printf("\n");
    for(i=0; i<arg; i++){									//print unsorted list
        printf("%d ", unsort[i]);
    }
	printf("\n");
        
	for(i=0; i<arg; i++){									//print sorted list
		printf("%d ", sort[i]);
	}
	printf("\n\n");

	free(unsort);											//free pointer
	free(sort);												//free pointer
}

//------------------------------------------end of code--------------------------------------------
