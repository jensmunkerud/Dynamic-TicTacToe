#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
using namespace std;

int mapSize = 3;
int consecutiveToWin = 3;
string playerA = "Cross";
string playerB = "Circle";
char emptyChar = ' ';
char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
struct position {
	int x;
	int y;
};

vector<vector<char>> board(mapSize, vector<char>(mapSize, emptyChar));

string repeatStr(string str, int n) {
	string result;
	for (int i = 0; i < n; i++) {
		result.append(str);
	}
	return result;
}

void printBoard(vector<vector<char>> board) {
	string smallIndent = (mapSize >= 10) ? " " : "";
	// Prints out abc row
	cout << "\n  " << smallIndent;
	for (int i = 0; i < mapSize; i++) {
		cout << alphabet[i] << " ";
	}
	cout << "\n " << smallIndent << repeatStr("+-", mapSize) << "+\n1" << smallIndent;

	// Prints out cells
	for (int row = 0; row < mapSize; row++) {
		for (int col = 0; col < mapSize; col++) {
			cout << "|" << board[row][col];
		}
		// Ternary operator (aka shorthand IF statement) counts rows
		string hey = (row + 1 < mapSize) ? to_string(row + 2) : "";
		cout << "|\n " << smallIndent << repeatStr("+-", mapSize) << "+\n" << hey << ((row < 8 && mapSize >= 10) ? " " : "");
	}
}

bool isValidMove(vector<vector<char>> board, position move) {
	if (board[move.y][move.x] != emptyChar) {
		return false;
	}
	return true;
}

position decodeMove(char a, int b) {
	position result;
	for (int i = 0; i < sizeof(alphabet); i++) {
		if (alphabet[i] == a) {
			result.x = i;
		}
	}
	result.y = b - 1;
	return result;
}

vector<vector<char>> makeMove(vector<vector<char>> board, position move, bool crossTurn) {
	board[move.y][move.x] = crossTurn ? 'x' : 'o';
	printBoard(board);
	return board;
}

string hasAnyoneWon(vector<vector<char>> board) {
	string winner = "none";
	// return either cross, circle or none
	for (int row = 0; row < mapSize; row ++) {
		for (int col = 0; col < mapSize; col ++) {
			// To make this scalable, i have to use some for loop or smthn to check
			// if we have a winner, for longer than 3...

			// Horizontal check
			if (col <= (mapSize - consecutiveToWin) && board[row][col] == board[row][col + 1] && board[row][col + 1] == board[row][col + 2] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
			}

			// Vertical check
			if (row <= (mapSize - consecutiveToWin) && board[row][col] == board[row + 1][col] && board[row + 1][col] == board[row + 2][col] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
			}

			// Obliquely right
			if (row <= (mapSize - consecutiveToWin) && col <= (mapSize - consecutiveToWin) && board[row][col] == board[row + 1][col + 1] && board[row + 1][col + 1] == board[row + 2][col + 2] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
			}

			// Obliquely left
			if (row <= (mapSize - consecutiveToWin) && col >= consecutiveToWin - 1 && board[row][col] == board[row + 1][col - 1] && board[row + 1][col - 1] == board[row + 2][col - 2] && board[row][col] != emptyChar) {
				winner = board[row][col] == 'x' ? playerA : playerB;
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
		cout << (crossTurn ? playerA : playerB) << " turn: \n";

		string input;
		cin >> input;

		if (input.length() < 2 || !isalpha(input[0])) {
						system("clear");
						printBoard(board);
						cout << "Invalid input. Please enter a letter followed by a number.\n";
						continue;
				}

		char a = input[0];
		int b;

		try {
			b = stoi(input.substr(1));
		} catch (exception& e) {
			system("clear");
			printBoard(board);
			cout << "Invalid input. Please enter a valid number after the letter.\n";
			continue;
		}

		if (b <= 0 || b > mapSize) {
						system("clear");
						printBoard(board);
						cout << "Invalid input. Please enter a number between 1 and " << mapSize << ".\n";
						continue;
				}


		// Handles positions that are already taken
		if (!isValidMove(board, decodeMove(a, b))) {
			system("clear");
			printBoard(board);
			cout << "That was an invalid move\n";
			continue;
		}

		system("clear");
		board = makeMove(board, decodeMove(a, b), crossTurn);

		crossTurn = ! crossTurn;
		// sleep(1);
	}
	cout << hasAnyoneWon(board) << " won!!";
	cout << "\n";
	sleep(4);
	return 0;
}
