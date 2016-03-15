//
//Soklong Lim
//CSE 222
//Programming Assignment #9 (Graph)
//March 06, 2015
//
//***Description***
//	this program is about directed graph. it takes 2 command-line argument such as (P9 A B, 
//A is the starting point & B is the stopping point). then the program will read an adjacency 
//file named "adj.data". finally, it will print out the path shortest path from the 2 points.
//example: A->D->F->B
//
//
//


#include <stdio.h>
#include <stdlib.h>
	
#define WHITE	-1 				//unvisited node is WHITE
#define GRAY 	-2				//visiting node is GRAY
#define BLACK 	-3				//already visited node is BLACK			
#define NIL		-4				//no parent flag is NIL


struct node{					
	int color;
	int distance;
	int parent;
};


main(int argc, char **argv){

	FILE *fp;												//pointer to open file and read
	struct node vertex[128];								//store all the vertices
	int matrix[128][128] = {0};								//adjacency matrix
	int que[128], path[128];								//queue array and path storing array	
	int head, tail;											//queue pointers
	int frm, to, i;											//temp var reading frm file
	int start, stop;										//2 command-line argument 
	int visiting;											//visiting node value
	char buff[10];											


	if(argc!=3){											//check for command-line arugment
		printf("Either Zero or Too Many Arguments Detected.\n");
		exit(0);											//quit program
	}

	if(1 == sscanf(argv[1], "%d", &start) && 1 == sscanf(argv[2], "%d", &stop)){
		if(start<0 || stop<0){								//check if star & stop < 0
			printf("Arguments Must Be Positive Integer.\n");
			exit(0);										//quit program	
		}
	} else {												//incorrect command-line argument
		printf("Arguments Must Be Positive Integer.\n");
		exit(0);											//quit program
	}

	fp = fopen("adj.data", "r");							//open file "adj.data" and read

	while(NULL != fgets(buff, 10, fp)){						//while no EOF found
		if(2 != sscanf(buff, "%d %d", &frm, &to)){			//capture 2 integers at a time 
			printf("File Content Error.\n");				//fail to convert to 2 integers
			exit(0);										//exit program
		}
		matrix[frm][to] = 1;								//mark adajacency as 1 for connection 
	}
	fclose(fp);												//close file pointer when done


	for(i=0; i<128; i++){									//preset all nodes
		vertex[i].color = WHITE;							//set unvisited flag
		vertex[i].distance = 0;								//set distance to '0'
		vertex[i].parent = NIL;								//set no parent flag
	}

	vertex[start].color = GRAY;								//set visiting flag
	vertex[start].parent = -44;								//start node flag
	vertex[start].distance = 0;								//

	head = tail = 0;										//set queue pointers to index '0'
	que[tail++] = start;									//add queue (add to tail)

	while( head != tail){									//check if queue is empty
		
		visiting = que[head];								//remove queue (remvoe frm head)
		if(head == 128){									//roll pointer over if hit upper bound
			head = 0;
		} else {
			head = head + 1;								//increment pointer to next remove data
		}

		for(i=0; i<128; i++){
			if(matrix[visiting][i] != 0){
				if(vertex[i].color == WHITE){ 				//check visiting status 
					vertex[i].color = GRAY;					//set visiting flag
					vertex[i].parent = visiting;			//set parent
					vertex[i].distance = vertex[visiting].distance + 1;
					if(i==stop){
						head = tail = -101;					//succeed flag
						break;								//break loop
					}
					que[tail] = i;							//add queue
					if(tail == 128){						//roll pointer over if hit upper bound
						tail = 0;		
					} else {	
						tail = tail + 1;					//increment pointer to next inserted slot
					}
				}
			}
		}
		vertex[visiting].color = BLACK;						//already visited 
	}

	if(head == tail && head == -101){						//path finding succeed with flag #
	 	i = 0;
 		path[i++] = stop;									//store stopping point first
		visiting = stop;
		while(visiting != start){ 							//saving path
			visiting = vertex[visiting].parent;				//move to parent node 
			path[i++] = visiting;							//store parent value
		}

		i = i - 1;											//length of path 
		printf("\n");
		for(i; i>=0; i--){									//print path by printing array backward
			printf("%d", path[i]);
			if(i!=0){
				printf("->");
			}
		}
		printf("\n\n");
	} else {												//fail to find path
		printf("\nNo Path Found.\n\n");
	}
}

//---------------------------------------------------------end of code-----------------------------------------------------
