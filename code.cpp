#include<iostream>
using namespace std;

#define N_sudoku 9
int N_NQ;
int N_maze;

// function to print final sudoku solution
void print_sudoku(int grid[N_sudoku][N_sudoku]) 
{ 
	for (int i = 0; i < N_sudoku; i++)
    {
		for (int j = 0; j < N_sudoku; j++) 
			cout << grid[i][j] << " "; 
		cout << endl;
    }
    return;
}

// Checks whether it will be legal to assign num to the given cell in sudoku
bool isSafe_sudoku(int grid[N_sudoku][N_sudoku], int row, int col, int num) 
{ 
	// if we find the same num in the given row , we return false 
	for (int x = 0; x <= 8; x++) 
		if (grid[row][x] == num) 
			return false; 

	// if we find the same num in the given column , we return false 
	for (int x = 0; x <= 8; x++) 
		if (grid[x][col] == num) 
			return false; 

	// if we find the same num in the particular 3*3 matrix, we return false 
	int startRow = row - row % 3, startCol = col - col % 3; 
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			if (grid[i + startRow][j+startCol] == num) 
				return false; 

	return true; 
}

/* Takes a partially filled-in grid and attempts 
to assign values to all unassigned locations in 
such a way to meet the requirements for 
Sudoku solution (non-duplication across rows, 
columns, and boxes) */
bool solveSuduko(int grid[N_sudoku][N_sudoku], int row, int col) 
{ 
	// if we have reached the 8th row and 8th column, the problem has been solved
	if (row == N_sudoku - 1 && col == N_sudoku) 
		return true; 

	// if column value becomes 9, we move to next row and column start from 0 
	if (col == N_sudoku) 
    { 
		row++; 
		col = 0; 
	} 
	
	// if the current position of the grid is already filled, we iterate for next column 
	if (grid[row][col] > 0) 
		return solveSuduko(grid, row, col + 1); 

	for (int num = 1; num <= N_sudoku; num++) 
	{ 
		// if it is safe to place the num (1-9) in the given cell, we move to next cell 
		if (isSafe_sudoku(grid, row, col, num)) 
		{ 
		    //Assigning the num in to the current cell 
			grid[row][col] = num; 
			
			// Checking for next possibility with next cell 
			if (solveSuduko(grid, row, col + 1)) 
				return true; 
		} 
		
		// Removing the assigned num, since our assumption was wrong 
        // we go for next assumption with diff num value 
		grid[row][col] = 0; 
	} 
	return false; 
}

// main function to solve sudoku
void sudoku()
{
    int grid[N_sudoku][N_sudoku];

	cout<<"Give the sudoku problem"<<endl;

	for(int i=0; i<N_sudoku; i++)
		for(int j=0; j<N_sudoku; j++)
			cin>>grid[i][j];
	cout<<endl;

	if (solveSuduko(grid, 0, 0)) 
		print_sudoku(grid); 
	else
		cout << "no solution exists " << endl; 
	return;
}

// function to print solution
void printNQ(int board[][100]) 
{ 
	for (int i = 0; i < N_NQ; i++) 
    { 
		for (int j = 0; j < N_NQ; j++) 
			cout<<board[i][j]<<" "; 
		cout<<endl; 
	} 
} 

/* A utility function to check if a queen can 
be placed on selected cell. Note that this 
function is called when "col" queens are 
already placed in columns from 0 to col -1. 
So we need to check only left side for 
attacking queens */
bool isSafeNQ(int board[][100], int row, int col) 
{ 
	int i, j; 

	// Check this row on left side
	for (i = 0; i < col; i++) 
		if (board[row][i]) 
			return false; 

	// Check upper diagonal on left side
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
		if (board[i][j]) 
			return false; 

	// Check lower diagonal on left side
	for (i = row, j = col; j >= 0 && i < N_NQ; i++, j--) 
		if (board[i][j]) 
			return false; 

	return true; 
} 

// A recursive utility function to solve N Queen problem
bool solveNQUtil(int board[][100], int col) 
{ 
	// if all queens are placed then return true
	if (col >= N_NQ) 
		return true; 

	// Consider a column and try placing queen in all rows one by one
	for (int i = 0; i < N_NQ; i++) 
    { 
		// Check if the queen can be placed on board[i][col]
		if (isSafeNQ(board, i, col)) 
        { 
			// Place this queen in board[i][col]
			board[i][col] = 1; 

			// recur to place rest of the queens
			if (solveNQUtil(board, col + 1)) 
				return true; 

			// If placing queen in board[i][col] doesn't lead to a solution
            //then remove queen from board[i][col]
			board[i][col] = 0; // BACKTRACK 
		} 
	} 

	// If the queen cannot be placed in any row in this colum col then return false
	return false; 
} 

/* This function solves the N Queen problem using 
Backtracking. It mainly uses solveNQUtil() to 
solve the problem. It returns false if queens 
cannot be placed, otherwise, return true and 
prints placement of queens in the form of 1s. 
Please note that there may be more than one 
solutions, this function prints one of the 
feasible solutions.*/
bool solveNQ() 
{ 
	int board[100][100];

    for(int i=0; i<N_NQ; i++)
        for(int j=0; j<N_NQ; j++)
            board[i][j]=0; 

	if (solveNQUtil(board, 0) == false) 
    { 
		cout<<"Solution does not exist"; 
		return false; 
	} 
    else
    {
	    printNQ(board); 
	    return true;
    }
}

//main funtion to solve n_queen
void N_queen()
{
    cout<<"Enter the size of board to be solved: ";
    cin>>N_NQ;
	solveNQ(); 
	return;
}

//  function to print solution matrix sol[N][N]
void print_maze(int sol[][100]) 
{ 
	for (int i = 0; i < N_maze; i++) 
    { 
		for (int j = 0; j < N_maze; j++) 
			cout<<sol[i][j]<<" "; 
		cout<<endl; 
	} 
} 

// function to check if x, y is valid index for N*N maze
bool isSafe_maze(int maze[][100], int x, int y) 
{ 
	// if (x, y outside maze) return false 
	if (x >= 0 && x < N_maze && y >= 0 && y < N_maze && maze[x][y] == 1) 
		return true; 
	return false; 
} 

// A recursive function to solve Maze problem
bool solveMazeUtil(int maze[][100], int x, int y, int sol[][100]) 
{ 
	// if (x, y is goal) return true 
	if ( x == N_maze - 1 && y == N_maze - 1 && maze[x][y] == 1) 
    { 
		sol[x][y] = 1; 
		return true; 
	} 

	// Check if maze[x][y] is valid 
	if (isSafe_maze(maze, x, y) == true) 
    {
		// mark x, y as part of solution path 
		sol[x][y] = 1; 

		// Move forward in x direction
		if (solveMazeUtil(maze, x + 1, y, sol) == true) 
			return true; 

		// if moving in x direction doesn't give solution 
        // then, move down in y direction
		if (solveMazeUtil(maze, x, y + 1, sol) == true) 
			return true; 

		// If none of the above movements work then BACKTRACK 
        // unmark x, y as part of solution path
		sol[x][y] = 0; 
		return false; 
	} 

	return false; 
}

/* This function solves the Maze problem 
using Backtracking. It mainly uses 
solveMazeUtil() to solve the problem. 
It returns false if no path is possible, 
otherwise return true and prints the path 
in the form of 1s. Please note that there 
may be more than one solutions, this 
function prints one of the feasible 
solutions.*/
bool solveMaze(int maze[][100]) 
{ 
	int sol[100][100];

	if (solveMazeUtil(maze, 0, 0, sol) == false) 
    { 
		printf("Solution doesn't exist"); 
		return false; 
	} 
    else
    {
	    print_maze(sol); 
	    return true;
    }
}

// main function to solve maze
void maze()
{
    int maze[100][100];

	cout<<"Enter the size of grid for maze puzzle: ";
	cin>>N_maze;
	cout<<endl;

    cout<<"Enter a "<<N_maze<<"X"<<N_maze<<" grid puzzle"<<endl;
    
    for(int i=0; i<N_maze; i++)
        for(int j=0; j<N_maze; j++)
            cin>>maze[i][j];
    cout<<endl;

	solveMaze(maze); 
	return;
}

int main()
{
    cout<<endl<<"WELCOME TO GAME SOLVER"<<endl;
    int choice=0;
    while(choice!=4)
    {
        cout<<endl;
        cout<<"SELECT FROM THE FOLLOWING GAMES"<<endl;
        cout<<"1 -> SUDOKU"<<endl;
        cout<<"2 -> N_QUEEN"<<endl;
        cout<<"3 -> MAZE"<<endl;
        cout<<"4 -> EXIT"<<endl;
        cout<<endl;
        cin>>choice;
        cout<<endl;
        if(choice==1)
            sudoku();
        else if(choice==2)
            N_queen();
        else if(choice==3)
            maze();
        else if(choice==4)
            break;
        else
            cout<<"Invalid choice"<<endl<<"Choose again"<<endl;
    }
    return 0;
}