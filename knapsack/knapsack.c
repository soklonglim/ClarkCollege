//
//Soklong Lim
//CSE 222
//Programming Assignment #7 (knapsack problem/dynamic programming)
//Feb 20, 2015
//
//***Description***
//	this program is for solving the 0/1 knapsack problem. it will expect a single 
//argument which is the weight capacity of the knapsack. it will read the content frm file
//'knapsack.data' in current directory and print out content of the file and the maximum 
//value allowed in the bucket and the selected items.
//Note: maximum items 128, maximum weight of each item 1024, maximum item name 30 char
//


#include <stdio.h>
#include <stdlib.h>


struct item{
	int weight;
	int value;
	char name[32];
};


int maxVal(struct item *list, int itemNum, int capacity);
int maxSave[10000] = {0};									//store calculated max 
int inventory[10000][128] = {0};							//store the selected items


main(int argc, char **argv){								//take argv as the bucket capacity


	FILE *fp;												//pointer to open a file
	struct item myList[10];									//array to hold max # of items	
	char frm_file[100];										//read frm file
    int weightCapacity;										//bucket capacity
	int mostValue;				
	int itemNum, val, i;

	itemNum = val = i = 0;									//initialize var to zero

	system("clear");

	if(argc==2){											//one argument capture

	val = sscanf(argv[1], "%d", &weightCapacity);			//check if argv is a #
		if(val != 0){
			weightCapacity = atoi(argv[1]);					//convert string to integer
			if(weightCapacity>0){							//check if argv < 0
				printf("Bucket Capacity: %d.\n\nList:\n", weightCapacity);
			} else {
				printf("!!!Invalid Argument Detected.\n");
				exit(0);
			}
		} else {
			printf("!!!Invalid Argument Detected.\n");
			exit(0);				
		}
	} else { 												//unrecognized input
		printf("!!!Invalid Argument Detected.\n");
		exit(0);
	}

	fp = fopen("./knapsack.data", "r");						//open file frm current dir

	if(fp==NULL){											//check if file exist or readable
		printf("'knapsack.data' NOT FOUND\n");

	} else {

		while(NULL != fgets(frm_file, 100, fp)){			//read until hit EOF
			if(3 != sscanf(frm_file, "%d %d %s", &myList[i].weight, &myList[i].value, &myList[i].name){
				printf("File Format Error\n");				//check if the file does not follow the fixed 
				exit(0);									//format %d %d %s
			}

			if(myList[i].weight<=1024){						//skip if item weights > 1024
				i = i + 1;     								//keep track # of items
			}
			
			if(i>128){										//read no more than 128 items 
				i = 128;									//
				break;
			}
        }
		itemNum = i;										//total items found
		
        for(i=0; i<itemNum; i++){							//echo the list
			printf("%d %d %s\n", myList[i].weight, myList[i].value, myList[i].name);

        }

		mostValue = maxVal(myList, itemNum, weightCapacity);	//calculate max value in the bucket
		printf("\nMaximum Value: %d.\n", mostValue);
		printf("Selected Items:\n");

		for(i=0; i<itemNum; i++){
			if(inventory[weightCapacity][i]>0){
				printf("%d : %s\n", inventory[weightCapacity][i], myList[i].name);
			}
		}
	}
	printf("\n");
}


//knapsack function----------------------------------------
int maxVal(struct item *list, int itemNum, int capacity){			
	int possible, mymax, i, k;
	mymax = 0;													//	

	if(capacity<=0){
		inventory[0][0] = 0;
		return 0;												//return '0' when capacity
	}															//is zero
																
	if(maxSave[capacity]>0){									//dynamiclly return the calculated
		return maxSave[capacity];								//maximum when possible
	}
	
    for(i=0; i<itemNum; i++){									//loop thru all items on the list

        if(capacity>=list[i].weight){

			//possible max value is  value[i] plus  max[capacity-weight[i]]//
            possible = list[i].value + maxVal(list, itemNum, capacity-list[i].weight);
			

            if(possible>mymax){									//compare to find the bigger #
                mymax = possible;								//reset mymax

				for(k=0; k<128; k++){							//
					inventory[capacity][k] = inventory[capacity-list[i].weight][k];
				}
				inventory[capacity][i] = inventory[capacity][i] + 1;	//
        	}
		}
	}
		
	maxSave[capacity] = mymax;								//saved calculated max
	return mymax;											//return each max found
	
}

//-------------------------end of code----------------------

/*
example: possible @ 5 = v[1] + maxVal[4];
		 inventory[5] = mouse + inventory[4] = 1 mouse + 2 cellphone

=>	inventory[capacity][k] = inventory[capacity-list[i].weight][k];
mean:	inventory[5] = inventory[4] = 2 cellphone

=>	inventory[capacity][i] = inventory[capacity][i] + 1;
mean:	inventory[5] = inventory[5] + 1 = inventory[4] + mouse = 2 cellphone + 1 mouse

*/
