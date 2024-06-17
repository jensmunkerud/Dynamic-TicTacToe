#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

string playerA = "Cross";
string playerB = "Circle";
char emptyChar = ' ';
struct position {
	int x;
	int y;
};
// Comments

char board[3][3] = {{emptyChar, emptyChar, emptyChar}, 
					{emptyChar, emptyChar, emptyChar},
					{emptyChar, emptyChar, emptyChar}};


void printBoard(char board[3][3]) {
	// Prints out abc row
	cout << "\n  a b c \n +-+-+-+\n1";
	
	// Prints out cells
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			cout << "|" << board[row][col];
		}
		// Ternary operator (aka shorthand IF statement) counts rows
		string hey = (row + 1 < 3) ? to_string(row + 2) : "";
		cout << "|\n +-+-+-+\n" << hey;
	}
}

bool isValidMove(char board[3][3], int coord) {
	if (board[coord][coord] != emptyChar) {
		return false;
	}
	return true;
}

position decodeMove(char a, int b) {
	position result;
	switch (a) {
		case 'a':
			result.x= 0;
			break;
		case 'b':
			result.x = 1;
			break;
		case 'c':
			result.x = 2;
			break;
	}

	switch (b) {
		case 1:
			result.y = 0;
			break;
		case 2:
			result.y = 1;
			break;
		case 3:
			result.y = 2;
			break;
	}
	return result;
}

void makeMove(char board[3][3], position move, bool crossTurn) {
	board[move.y][move.x] = crossTurn ? 'x' : 'o';
	printBoard(board);

}

string hasAnyoneWon(char board[3][3]) {
	string winner = "none";
	// return either cross, circle or none
	for (int row = 0; row < 3; row ++) {
		for (int col = 0; col < 3; col ++) {
			// To make this scalable, i have to use some for loop or smthn to check
			// if we have a winner, for longer than 3...

			// Horizontal check
			if (col <= 0 && board[row][col] == board[row][col + 1] && board[row][col + 1] == board[row][col + 2] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
			}

			// Vertical check
			if (row <= 0 && board[row][col] == board[row + 1][col] && board[row + 1][col] == board[row + 2][col] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
			}

			// Obliquely right
			if (row <= 0 && col <= 0 && board[row][col] == board[row + 1][col + 1] && board[row + 1][col + 1] == board[row + 2][col + 2] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
				cout << "obliquely right\n";
			}

			// Obliquely left
			if (row <= 0 && col >= 2 && board[row][col] == board[row + 1][col - 1] && board[row + 1][col - 1] == board[row + 2][col - 2] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
				cout << "obliquely left\n";
			}
		}
	}
	return winner;
}



int main() {
	bool crossTurn = true;
	system("clear");
	printBoard(board);
	while (hasAnyoneWon(board) == "none") {
		char a = 'a';
		int b = 0;
		cout << (crossTurn ? playerA : playerB) << " turn: \n";
		cin >> a >> b;


		system("clear");
		makeMove(board, decodeMove(a, b), crossTurn);

		crossTurn = ! crossTurn;
		// sleep(1);
	}
	cout << hasAnyoneWon(board) << " won!!";
	cout << "\n";
	sleep(4);
	return 0;
}
