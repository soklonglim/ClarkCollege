//
//Soklong Lim
//CSE 222
//Programming Assignment #8 (Merge Sort)
//Feb 27, 2015
//
//***Description***
//	this program is about merge sort. it receives one argument integer from user and
//generate random # then store the random # in an unsorted array then start sorting
//process by spliting the array into two halves and recursively splits each half into
//another two halves until each segment contains only one element and call the merge
//funciton to merge those splited arrays two at a time by storing from smallest # to
//largest # until it gets back to the same length as unsorted array but each element
//has been sorted and stored in sorted array.
//
//

#include <stdio.h>
#include <stdlib.h>


int *mergeSort(int *a, int length);
int *merge(int *temp1, int *temp2, int len1, int len2);


main(int argc, char **argv){


	int *unsort, *sort, *temp;
    int arg, i;												//arg is the # of data to be sorted


    if(argc!=2){											//check for argument
        printf("Either Zero or Too Many Arguments Dectected.\n");
        exit(0);											//quie program
    }

    if(1 == sscanf(argv[1], "%d", &arg)){					//check and store argv[1] as length
        if(arg<=0){
    	    printf("Argument Must Be Positive Integer.\n");
            exit(0);										//quit program
		}
    } else {												//not integer detected
        printf("Argument Must Be Positive Integer.\n");
        exit(0);											//quit program
    }

	unsort = malloc((arg+1)*sizeof(int));					//allocate memory
	temp = malloc((arg+1)*sizeof(int));						//'+1' for '\0'
	sort = malloc(arg*sizeof(int));

	for(i=0; i<arg; i++){                          			//generate random # and
        unsort[i] = rand()%100000;  		           		//store in unsored array
    }                                       	       		//generated #s are b/w 0-99999
    unsort[i] = '\0';                           	   		//nulterminate string

	for(i=0; i<arg; i++){									//make a copy of unsorted list
		temp[i] = unsort[i];
	}
	temp[i] = '\0';											//nulterminate string


	sort = mergeSort(temp, arg);							//call merge sort function

	
	printf("\n");	
	for(i=0; i<arg; i++){									//print unsorted list
        printf("%d ", unsort[i]);                    
    }
	printf("\n");

	for(i=0; i<arg; i++){                           		//print sorted list
        printf("%d ", sort[i]);                    
    }
	printf("\n\n");
	
	free(unsort);											//free pointer
	free(sort);												
	free(temp);												
}

//merge sort function-----------------------------------
int *mergeSort(int *a, int length){							//recursively splits array into 	
	int *temp1, *temp2;										//two halves until each segment contain
	int i, k, middle;										//only one or zero element

	if(length<=1){											//segment with one or zero element
		return a;											//will be returned
	} 

	middle = length/2;										//find middle point to split
	
	temp1 = malloc(middle*sizeof(int));
	temp2 = malloc((length-middle)*sizeof(int));

	for(i=0; i<middle; i++){								//make copy of first half
		temp1[i] = a[i];									//start storing frm 0 index
	}

	k = 0;
	for(i=middle; i<length; i++){							//make copy of leftover half
		temp2[k++] = a[i];									//start storing frm 0 index
	}
	
	temp1 = mergeSort(temp1, middle);						//recurse the first half
	temp2 = mergeSort(temp2, length-middle);				//recures leftover half
	a = merge(temp1, temp2, middle, length-middle);			//call merge array function

	free(temp1);											//free pointer
	free(temp2);

	return a;												//return after merging
}


//merge function-----------------------------------------
int *merge(int *temp1, int *temp2, int len1, int len2){
	int *temp3, t1, t2, i, len;								//t1: temp1 counter, len1: temp1 length
															//t2: temp2 counter, len2: temp2 length
	len = len1 + len2;										//total merged length
	t1 = t2 = i = 0;										//initialize counter to 0

	temp3 = malloc(len*sizeof(int));						//allocate memory to store the merged data

	while(t1<len1 && t2<len2){								//compare and merge
		if(temp1[t1] > temp2[t2]){							//
			temp3[i] = temp2[t2];							//store the smaller to merge array
			t2 = t2 + 1;	
			i = i + 1;
		} else {
			temp3[i] = temp1[t1];							//store the smaller to merge array
			t1 = t1 + 1;
			i = i + 1;
		}
	}

	if(t1==len1){											//data on temp1 is finished
		while(t2<len2){										//direct storing frm temp2
			temp3[i] = temp2[t2];
			t2 = t2 + 1;
			i = i + 1;
		}
	} else if(t2==len2){									//data on temp2 is finished
		while(t1<len1){										//direct storing frm temp1
			temp3[i] = temp1[t1];
			t1 = t1 + 1;
			i = i + 1;
		}
	}
	return temp3;											//return after sorting & merging
}

//-----------------------------------------------end of code----------------------------------------------------
