#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>


/*
    ---------------------------------------------- PROBLEM STATEMENT ----------------------------------------------
                                https://www.hackerrank.com/challenges/kingdom-division

    --------------------------------------------------- TITLE -----------------------------------------------------
                        Divide kingdom in such a way that inherents will not invade each other

    ------------------------------------------------- DESCRIPTION -------------------------------------------------

                King Arthur has a large kingdom that can be represented as a tree, 
                
                where nodes correspond to cities and edges correspond to the roads between cities. 
                The kingdom has a total of n cities numbered from 1 to n.
                
                The King wants to divide his kingdom between his two children, Reggie and Betty, 
                by giving each of them 0 or more cities; 
                
                However, they don't get along so he must divide the kingdom in such a way that they will not 
                invade each other's cities. 
                
                The first sibling will invade the second sibling's city 
                if the second sibling has no other cities directly connected to it. 
    ---------------------------------------------------------------------------------------------------------------

            INPUT:                                         |               OUTPUT:
                5                                          |                    4
                1 2                                        |
                1 3                                        |
                3 4                                        |
                3 5                                        |
    ---------------------------------------------------------------------------------------------------------------
    
*/


int **paths; // pointer to hold the adjacency matrix of paths between nodes (cities)


// data structure to represent solution vector
struct SolutionVector {

    /*
        length member of the structure is the number of cities in the kingdom which is also the length of the array

        Every element of the member array represents the node (city) of the tree (kingdom)
        Each element has either 0 or 1 as its value where

                0 -> City belongs to Reggie
                1 -> City belongs to Betty
        
    */

    int length; // length of the solution vector / number of elements
    int *array; // data of the solution vector
};


// function to check if the division of kingdom defined by parameter solVec (SolutionVector) is safe or not
int checkSafe(struct SolutionVector *solVec) {

    int isSafe = 1; // boolean variable initially set to safe ( 1 is safe | 0 is unsafe )

    // for loop to select every node (city) in the solution vector
    for(int i = 0; i < solVec->length; i++) {

        int friendly = solVec->array[i]; 
        /* 
            friendly variable stores the value 0 or 1 of the current node (city) 
            i.e. if the city belongs to Reggie or Betty 
        */

        int count = 0;
        /*
            count is counter variable to store the count of friendly nodes (cities) directly attached to the current node (city)
        */
        
        // for loop to look for available paths / nodes connected to the current node
        // loops in the adjacency matrix
        for(int j = 1; j <= solVec->length; j++) {
            
            // if path found i.e. node is connected to the current node
            if(paths[i + 1][j]) {

                // checks in the solution vector if the node connected is an ally or enemy
                if(solVec->array[j - 1] == friendly) {
                    
                    count++; // increments counter if neighbour is an ally
                
                }
            }
        }

        isSafe *= (count ? 1 : 0);
        /*

            SAFE CONDITION: A city is safe if atleast one friendly city is directly connected to it.

            after counting the number of friendly neighbours connected to the current node (city)
            if the count > 1 isSafe variable is multiplied by 1
            else it is multiplied by 0 as the node (city) is not safe

        */
        
        if(!isSafe)
            break;
        // Even if a single city is unsafe, further checking of the solution vector is discarded
    }

    return isSafe;  // returns isSafe (as a boolean) i.e. 1 for safe and 0 for not safe
}

// function to generate all possible solutions and check if they are safe
// recursive function 
// uses Depth First Search approach
int dfs(int level, struct SolutionVector solVec, int *noOfSol, int parent, int x) {
    /*
        parameters:
            level::int              :       current node

            solVec::SolutionVector  :       solution vector - array of int - contains 0 or 1 as values 
                                            representing cities assigned to which inherent
            
            noOfSol::int            :       count of safe kingdom division - safe solutions
            
            parent:: int 			:		x position (horizontal distance from the edge of screen) of the parent node
            x:: int 				:		width allowed for the nodes to take on a level
    */

    if(level < solVec.length) {

        /*
            For every recursive call level is incremented describing that the how many nodes (cities) have been visited
            
            when level will be equal to the length of the solution vector i.e. when all the cities are divided among the inherents
            this condition will be return false and will execute the else statements

            dfs will recurse until level < solVec.length

        */

       /*
                                                          NODE (1)
                                                             ||
                                                         0  /  \  1
                                            ----------------    ----------------
                                           /                                    \
                                        NODE (2)                            NODE (2)
                                          ||                                    ||
                                      0  /  \  1                             0 /  \  1
                                     ----    ----                          ----    ----
                                    /            \                        /            \
                                NODE (3)        NODE (3)              NODE (3)        NODE (3)

                                   ..               ..                  ..              .. 
       */
        
    
        solVec.array[level] = 0;    // assigning the current node (city) to Reggie (0)
        
        // logic to draw node in set space tree
		int x1 = parent - (x / 2);
        int y1 = (level + 2) * 100;
		setfillstyle(SOLID_FILL, RED);
		circle(x1, y1, 20);
        floodfill(x1 + 2, y1 + 2, WHITE);
        outtextxy(x1 - 5, y1 - 5, "R");
        line(parent, (level + 1) * 100, x1, y1);
        // end
        
        dfs(level + 1, solVec, noOfSol,  parent - (x / 2), x / 2);    // recursive call to explore further with this possibility 


        solVec.array[level] = 1;    // assiging the current node (city) to Betty (1)
        
        // logic to draw node in set space tree
        int x2 = parent + (x / 2);
        int y2 = (level + 2) * 100;
		setfillstyle(SOLID_FILL, BLUE);
		circle(x2, y2, 20);
        floodfill(x2 + 2, y2 + 2, WHITE);
		outtextxy(x2 - 5, y2 - 5, "B");
        line(parent, (level + 1) * 100, x2, y2);
        // end
        
        dfs(level + 1, solVec, noOfSol, parent + (x / 2), x / 2);    // recursive call to explore further with this possibility 

    } else {

        // When all the cities have been divided its solution vector is now checked to detect if a war will occur or not

        printf("\nSolution: [");

        for(int i = 0; i < solVec.length; i++) {    // printing solution vector
            printf(" %d ", solVec.array[i]);
        }
        printf("]");

        if(checkSafe(&solVec)) {    // calling checkSafe function with address of the solution vector as parameter
            // checkSafe function return 1 (true) if the division of cities is safe else 0 (false)
            printf(" --> SAFE");

            *noOfSol = *noOfSol + 1; // incrementing the number of safe solutions counter
            
            // logic to draw green circle indicating valid solution
            setfillstyle(SOLID_FILL, GREEN);
            circle(parent, (level + 2) * 100 - 50, 10);
            floodfill(parent, ((level + 2) * 100) - 50, WHITE);
            // end
            
        } else {
        	printf(" --> NOT SAFE");
        	
        	// logic to draw a 'x' string
        	outtextxy(parent - 5, (level + 2) * 100 - 60, "X");
            
		}
		
		getch();
    }
    
    return 0;
}

// function to start the DFS and find solution, takes number of cities as the parameter
int kingdomDivision(int n) {

    // declaring and initializing a solution vector structure with n as its length 
    // and pointing array to newly allocated memory of size n
    struct SolutionVector solVec = {n, (int *)malloc(sizeof(int) * n)};

    int numberOfSolutions = 0; // initializing a counter variable for number of safe solutions

    for(int i = 0; i < n; i++) 
        solVec.array[i] = -1;   // [OPTIONAL] assigning -1 to all the elements as default value, 
                                // representing that the node (city) is not visited yet
    
    int x = 30;
    for(int i = 0; i < n; i++)
    	x *= 2;
    
    circle(getmaxwidth() / 2, 100, 25);
    
    dfs(0, solVec, &numberOfSolutions, getmaxwidth() / 2, x); // starting the dept first search with 0 as the first city

    return numberOfSolutions; // function return the number of safe solutions when dfs is completed
}

// main function to run the program
int main() {
   
	int gui = initwindow(getmaxwidth( ), getmaxheight( ), "Kingdom Division"); // creating new gui window
	
	// logic to draw front page of gui
	setactivepage(0);
	setfillstyle(1, 3);
	floodfill(0,0,0);
	settextstyle(8, 0, 10);
	outtextxy(getmaxwidth() / 2 - textwidth("Kingdom"), getmaxheight() / 2 - textheight("D"), "Kingdom Divison");
	settextstyle(10, 0, 4);
	outtextxy(getmaxwidth() / 2 - textwidth("b"), getmaxheight() * 0.75 - textheight("b") * 2, "by");
	outtextxy(getmaxwidth() / 2 - textwidth("Ishwar "), getmaxheight() * 0.75 - textheight("I"), "Ishwar Jagdale");
	outtextxy(getmaxwidth() / 2 - textwidth("260"), getmaxheight() * 0.75, "26043");
	settextstyle(3, 0, 2);
	outtextxy(getmaxwidth() / 2 - textwidth("press any key"), getmaxheight() * 0.75 + textheight("p") * 3, "press any key to continue...");
	getch();
	setactivepage(1);
	settextstyle(0, 0, 0);
	setvisualpage(1);
	// end
	
	printf("---------------------------------------------- PROBLEM STATEMENT ----------------------------------------------\n");
    printf("                            https://www.hackerrank.com/challenges/kingdom-division\n\n");
    printf("--------------------------------------------------- TITLE -----------------------------------------------------\n");
    printf("                    Divide kingdom in such a way that inherents will not invade each other\n\n");
    printf("\n");
    printf("------------------------------------------------- DESCRIPTION -------------------------------------------------\n\n");
    printf("            King Arthur has a large kingdom that can be represented as a tree, \n");
    printf("            where nodes correspond to cities and edges correspond to the roads between cities. \n");
    printf("\n");
	printf("            The kingdom has a total of n cities numbered from 1 to n.\n");
    printf("            The King wants to divide his kingdom between his two children, Reggie and Betty, \n");
    printf("            by giving each of them 0 or more cities; \n");
    printf("            However, they don't get along so he must divide the kingdom in such a way that they will not \n");
    printf("            invade each other's cities. \n");
    printf("\n");
    printf("            The first sibling will invade the second sibling's city \n");
    printf("            if the second sibling has no other cities directly connected to it. 								\n");
    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
	
    int n;  // variable for number of cities
    printf("Enter number of cities: ");
    scanf("%d", &n);    // taking a number as an input from user

    /*
        paths is a global pointer
        It points to an adjacency matrix (2D array) which contains paths of the cities connected
    */
    // allocating memory to store integer pointers
    paths = (int **)malloc(sizeof(int *) * (n + 1));
    for(int i = 0; i <= n; i++)
        // allocating memory for the integer arrays
        paths[i] = (int *)malloc(sizeof(int) * (n + 1));
    
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n; j++)
            paths[i][j] = 0;        // assigning 0 to every element in matrix to get rid of garbage values


    printf("Enter %d edges: \n", n - 1); // As the kingdom can be represented like a tree so there will be n-1 edges for n nodes
    for(int i = 0; i < n - 1; i++) {    
        int u, v;                  // consider u and v as two cities
        printf("Enter edge %d: ", i + 1);
        scanf("%d %d", &u, &v);     // scanning n - 1 pair of integers i.e. the edges/path of the nodes (cities)
        paths[u][v] = paths[v][u] = 1;  // assigning 1 if there is a path between city u and city v
    }
    
    printf("---------------------------------------------------------------------------------------------------------------\n");

    // printing the adjacency matrix
    printf("ADJ MATRIX: \n");
	printf("\n");
	       
    for(int i = 0; i <= n; i++) {
    	if(!i) {
    		for(int k = 0; k <= n; k++) {
    			if(!k)
    				printf(" %d |", k);
    			else
    				printf(" %d ", k);
			}
    		printf("\n");
			for(int k = 0; k <= n; k++)
				printf("---");
			printf("\n");
		}
		else {
			for(int j = 0; j <= n; j++) {
	        	if(!j)
	        		printf(" %d |", i);
	        	else
	            	printf(" %d ", paths[i][j]);
			}
        	printf("\n");	
		}
    }

	printf("---------------------------------------------------------------------------------------------------------------\n");
    
	int noOfWays = kingdomDivision(n); // finding the number of safe solutions
    
	printf("\n---------------------------------------------------------------------------------------------------------------\n");
	
	printf("\nThe ways in which kingdom can be divided peacefully: %d", noOfWays);
    
	// printing the final solution on gui
	char str[100];
    sprintf(str, "The ways in which kingdom can be divided peacefully : %d", noOfWays);
	outtextxy(getmaxwidth() / 2 - textwidth("The ways in which kingdom "), getmaxheight() * 0.8, str);
	outtextxy(getmaxwidth() / 2 - textwidth("press any k"), getmaxheight() * 0.9, "press any key to exit");
	
	getch();
    
	return 0;
}
