/********************************************************************
 File: Sliding Puzzle.cpp
 Purpose: This program creates a 3x3 board of boxes with numbers that will be moved around by the user until they are in numerical order.
 Name: Chang-Syuan Wu
 Date: 05/30/2017
 Inputs: order, playAgain, start, movement, confirm
 Outputs: board[][], moveCount
 Functions:
 
	randomizeBoard (int [][]) - Randomly shuffles the elements of the 3x3 2D array passed to it.
 
	showBoard (int [][]) - Displays the elements of the 3x3 2D array passed to it in a 3x3 box.
 
	clearScreen () - Detects the operating system and clears the console screen using the OS specific way.
 
	pause () - Detects the operating system and uses the OS specific way to wait for user input.
 
	isValidMove (int, int) - Used the passed in row and column to determine if it is out-of-bounds for a 3x3 box. Returns true if not out-of-bounds and false if is out-of-bounds.
 
	up (int [][], int, int) - Swaps the value of the empty box (0) with the one above it if it would not put it out-of-bounds (Calls isValidMove). Makes it appear if the blank moved upwards.
 
	down (int [][], int, int) - Swaps the value of the empty box (0) with the one below it if it would not put it out-of-bounds (Calls isValidMove). Makes it appear if the blank moved downwards.
 
	left (int [][], int, int) - Swaps the value of the empty box (0) with the one to the left of it if it would not put it out-of-bounds (Calls isValidMove). Makes it appear if the blank moved leftwards.
 
	right (int [][], int, int) - Swaps the value of the empty box (0) with the one to the right it if it would not put it out-of-bounds (Calls isValidMove). Makes it appear if the blank moved rightwards.
 
	checkIfSolved (int [][], int [][]) - Compares the values of the first 2D array passed in to the second 2D array. If all values are equal, returns true.
 
	findBlank (&int, &int, int [][]) - Finds the location of 0 in the passed in 2D array. Returns the values using reference variables.
 
	checkIfInteger ($int) - Checks if cin received an integer. Loops until a integer value is entered.
 
 ********************************************************************/

// Headers
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <random>

using namespace std;


void randomizeBoard (int board[3][3]) {
	
	// Seeds the random number generator using the Mersenne Twister Engine
	random_device rd;
	mt19937 gen(rd());
	
	// Shuffles the elements of the array passed to it randomly
	shuffle(&board[0][0], &board[2][2], gen);
}

void showBoard (int board[3][3]) {
	
	// Outputs some space between the board and the top of the screen
	cout << endl << endl;
	
	// Loops for the number of rows (3)
	for (int i = 0; i < 3; i++) {
		// Outputs the horizontal lines and indents the box
		cout << "\t" << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
		cout << "\t";
		
		// Loops for the number of columns (3)
		for (int j = 0; j < 3; j++) {
			// Outputs the vertical lines
			cout << "|";
			
			// Outputs a blank space if the number is 0
			if (board[i][j] == 0) {
				cout << " " << " " << " ";
			}
			
			// Outputs the number if it is not 0
			else {
				cout << " " << board[i][j] << " ";
			}
		}
		
		// Outputs the vertical line at the end of the row
		cout << "|" << endl;
	}
	// Outputs the horizontal line at the bottom of the bow
	cout << "\t" << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
	
	// Outputs some space between the board and the text following it
	cout << endl << endl;
}

void clearScreen() {
	
	#ifdef _WIN32
		// Windows
		system("CLS");
	#else
		// Assuming its POSIX
		system("clear");
	#endif
}

void pause() {
	#ifdef _WIN32
		// Windows
		system("pause");
	#else
		// Assuming its POSIX
		cout << "Press enter to continue..." << endl;
		system("read");
	#endif
}

bool isValidMove(int row, int column) {
	
	// If moving to the passed in row and column would be out of bounds of a 3x3 box
	if ((row > 2) || (column > 2) || (row < 0) || (column < 0)) {
		return false;
	}
	
	else {
		return true;
	}
}


void up(int board[3][3], int row, int column) {
	
	// If moving to the box above the blank would not be out-of-bounds
	if (isValidMove(row - 1, column)) {
		
		// Swap values of the boxes
		int temp = board[row - 1][column];
		board[row - 1][column] = board[row][column];
		board[row][column] = temp;
		
	}
	
	else {
		cout << "Invalid move!" << endl;
		pause();
	}
}

void down(int board[3][3], int row, int column) {
	
	// If moving to the box below the blank would not be out-of-bounds
	if (isValidMove(row + 1, column)) {
		
		// Swap values of the boxes
		int temp = board[row + 1][column];
		board[row + 1][column] = board[row][column];
		board[row][column] = temp;
		
	}
	
	else {
		cout << "Invalid move!" << endl;
		pause();
	}
}

void left(int board[3][3], int row, int column) {
	
	// If moving to the box to the left of the blank would not be out-of-bounds
	if (isValidMove(row, column - 1)) {
		
		// Swaps the values of the boxes
		int temp = board[row][column - 1];
		board[row][column - 1] = board[row][column];
		board[row][column] = temp;
		
	}
	
	else {
		cout << "Invalid move!" << endl;
		pause();
	}
}

void right(int board[3][3], int row, int column) {
	
	// If moving to the box to the right of the blank would not be out-of-bounds
	if (isValidMove(row, column + 1)) {
		
		// Swaps the values of the boxes
		int temp = board[row][column + 1];
		board[row][column + 1] = board[row][column];
		board[row][column] = temp;
		
	}
	
	else {
		cout << "Invalid move!" << endl;
		pause();
	}
}

bool checkIfSolved(int currentBoard[3][3], int answerBoard[3][3]) {
	
	// Initializes the number of correct boxes to 0
	int correctBoxes = 0;
	
	// Loops for the number of rows (3)
	for (int i = 0; i < 3; i++) {
		
		// Loops for the number of columns (3)
		for (int j = 0; j < 3; j++) {
			
			// If the current board is the same as the answer board in the same location
			if (currentBoard[i][j] == answerBoard[i][j]) {
				
				// Increment correct boxes
				correctBoxes++;
			}
		}
	}
	
	// If all 9 boxes are correct
	if (correctBoxes == 9) {
		return true;
	}
	
	else {
		return false;
	}
}

void findBlank(int &row, int &column, int board[3][3]) {
	
	// Loops for the number of rows (3)
	for (int i = 0; i < 3; i++) {
		
		// Loops for the number of columns (3)
		for (int j = 0; j < 3; j++) {
			
			// If 0 is found, return the coordinates of it using reference variables
			if (board[i][j] == 0) {
				row = i;
				column = j;
			}
		}
	}
}

void checkIfInteger(int &input) {
	while(cin.fail()) {
		cout << "Error: Enter an Integer Value" << endl;
		
		// Clear the fail flag
		cin.clear();
		
		// Clears the input
		cin.ignore(1000,'\n');
		
		// Gets the user input
		cin >> input;
	}
}

int main () {
	// Variables and arrays
	char playAgain;
	int answerBoard[3][3];
	int order;
	string start;
	
	// Welcome message
	cout << "Welcome to the 3x3 sliding puzzle solver!" << endl;
	
	// Loops if the user wants to play again
	do {
		// Variables and arrays that should to be re-initialized when the user wants to play again
		int board[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
		int moveCount = 0;
		bool exit = false;
		bool solved = false;
		bool validOrder = false;
		char movement;
		
		// Loops while the user does not enter a valid choice
		do {
			
			// Gets the order the user wants to solve the puzzle in
			cout << "Please select the order you would like to solve the puzzle in:" << endl;
			cout << "1. Ascending" << endl;
			cout << "2. Descending" << endl;
			cin >> order;
			
			// Checks to make sure the user entered an integer value so the program doesn't fall into an infinite loop
			checkIfInteger(order);
			
			switch (order) {
				
				// If the user chose ascending order
				case 1:
				
					// Changes validOrder to true
					validOrder = true;
				
					// Outputs instructions on how to play
					cout << "How to play:" << endl;
					cout << "\t" << "Move the blank space around the board using the movement commands to solve it in ascending order." << endl;
					cout << "The solved state is shown below:" << endl;
				
					// Sets the answerBoard to ascending order
					answerBoard[0][0] = 1;
					answerBoard[0][1] = 2;
					answerBoard[0][2] = 3;
					answerBoard[1][0] = 4;
					answerBoard[1][1] = 5;
					answerBoard[1][2] = 6;
					answerBoard[2][0] = 7;
					answerBoard[2][1] = 8;
					answerBoard[2][2] = 0;
				
					// Show the answer board
					showBoard(answerBoard);
					break;
				
				//If the user chose ascending order
				case 2:
				
					// Changes validOrder to true
					validOrder = true;
				
					// Outputs instructions on how to play
					cout << "How to play:" << endl;
					cout << "\t" << "Move the blank space around the board the movement commands to solve it in descending order." << endl;
					cout << "The solved state is shown below:" << endl;
				
					// Sets the answerBoard to descending order
					answerBoard[0][0] = 8;
					answerBoard[0][1] = 7;
					answerBoard[0][2] = 6;
					answerBoard[1][0] = 5;
					answerBoard[1][1] = 4;
					answerBoard[1][2] = 3;
					answerBoard[2][0] = 2;
					answerBoard[2][1] = 1;
					answerBoard[2][2] = 0;
				
					// Show the answer board
					showBoard(answerBoard);
					break;
				
				// If the user doesn't enter a valid choice
				default:
					cout << "Enter a valid choice!" << endl;
					break;
			}
			
		} while (!validOrder);
		
		// Waits for the user to enter anything (Instructs them to enter "start")
		cout << "Enter \"start\" to start the game." << endl;
		cin >> start;
		
		// Instructions on how to move blank space
		cout << "Use the movement commands to move the blank space around" << endl;
		
		// Randomizes the board
		randomizeBoard(board);
		
		// Loops while the board is not solved and the user doesn't want to exit
		do {
			// Clears the screen
			clearScreen();
			
			// Shows the board
			showBoard(board);
			
			// Gets the user input
			cout << "How would you like to move the blank?:" << endl;
			cout << "w. Up" << endl;
			cout << "s. Down" << endl;
			cout << "a. Left" << endl;
			cout << "d. Right" << endl;
			cout << "1. Show solved state" << endl;
			cout << "2. Exit" << endl;
			cout << "3. Solve the puzzle (Faster Testing)" << endl;
			cin >> movement;
			
			// Finds the location of 0 (The blank space)
			int row, column;
			findBlank(row, column, board);
			
			switch (movement) {
				
				// If the user chooses "Up"
				case 'w':
					
					// Calls the up function
					up(board, row, column);
					break;
				
				// If the user chooses "Down"
				case 's':
					
					// Calls the down function
					down(board, row, column);
					break;
				
				// If the user chooses "Left"
				case 'a':
					
					// Calls the left function
					left(board, row, column);
					break;
					
				// If the user chooses "Right"
				case 'd':
					
					// Calls the right function
					right(board, row, column);
					break;
					
				// If the user chooses "Show solved state"
				case '1':
					
					// Clears the screen
					clearScreen();
					
					// Shows the answer board
					cout << "Solved state:" << endl;
					showBoard(answerBoard);
					
					// Waits for user to input anything before returning to board
					pause();
					
					// Showing the answer board does not increment the number of moves
					continue;
	
				// If the user chooses "Exit"
				case '2':
					
					// Confirms if user wants to exit
					char confirm;
					cout << "Confirm Exit? All progress will be lost! (y/n)" << endl;
					cin >> confirm;
					if (confirm == 'y') {
						exit = true;
					}
					break;
					
				// Solves the board
				case '3':
					board[0][0] = answerBoard[0][0];
					board[0][1] = answerBoard[0][1];
					board[0][2] = answerBoard[0][2];
					board[1][0] = answerBoard[1][0];
					board[1][1] = answerBoard[1][1];
					board[1][2] = answerBoard[1][2];
					board[2][0] = answerBoard[2][0];
					board[2][1] = answerBoard[2][1];
					board[2][2] = answerBoard[2][2];
					break;
					
				// If the user doesn't enter a valid choice
				default:
					cout << "Enter a valid choice!" << endl;
					pause();
					continue;
			}
			
			// Increments the move count
			moveCount++;
			
			// Boolean variable checking if board is solved
			solved = checkIfSolved(board, answerBoard);
			
		} while ((!solved) && (!exit));
		
		// Clears the screen
		clearScreen();
		
		// If the board was solved (Not exited)
		if (solved) {
			// Shows the (Completed) board
			showBoard(board);
			
			// Tells user how many moves it took them to solve the board
			cout << "Congratulations! You solved the puzzle in " << moveCount << " moves!" << endl;
		}
		
		// Asks user if that want to play again
		cout << "Play again? (y/n)" << endl;
		cin >> playAgain;
		
	} while (playAgain == 'y');
	
	return 0;
}
