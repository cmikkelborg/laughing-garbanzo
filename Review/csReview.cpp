// csReview.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>

using namespace std;

struct Move {
	int row; // 0 - 2
	int col; // 0 -2
	char symbol; // x or o
};

class Board {
public:
	Board();
	void display();
	bool place(Move move);
	bool isFull();
	bool didWin();
private:
	char board[3][3];
};



char players[] = { 'X', 'O' };

int main()
{
	Board myboard;
	//choose who goes first
	srand(time(NULL));
	int turn = rand() % 2;
	Move move;
	// loop until game over or win
	do {
		//		get user input
		cout << "It's " << players[turn] << "'s turn. " << endl;

		cout << "Input a row and colomn (1 2): ";
		//		generate move
		move.symbol = players[turn];
		cin >> move.row >> move.col;
		if (!myboard.place(move)) {
			continue;
		}
		//		build board
		myboard.place(move);
		//		show the board
		myboard.display();
		if (myboard.didWin()) {
			cout << endl << players[turn] << " a winner are you!\n";
			break;
		}
		if (myboard.isFull())
		{
			cout << "\nDraw!\n";
			break;
		}

		turn = !turn;
	} while (true);

	system("pause");
	return 0;
}

Board::Board()
{
	for (int j = 0; j <= 2; j++) {
		for (int i = 0; i <= 2; i++) {
			board[i][j] == ' ';
		}
	}
}

void Board::display()
{

	cout << flush;
	system("CLS");
	for (int j = 0; j <= 2; j++) {
		for (int i = 0; i <= 2; i++) {
			cout << board[i][j];
			if (i < 2) {
				cout << '|';
			}

		}
		cout << endl;
		if (j < 2) {
			cout << "-+-+-" << endl;
		}
	}

}

bool Board::place(Move move)
{
	if (move.row > 2 || move.col > 2) {
		return false;
	}
	if (board[move.row][move.row] != ' ') {
		return false;
	}
	board[move.row][move.col] = move.symbol;
	return true;
}

bool Board::isFull()
{
	for (int j = 0; j <= 2; j++) {
		for (int i = 0; i <= 2; i++) {
			board[i][j] == ' ';
			return false;
		}
	}
	return true;
}

bool Board::didWin()
{
	char rowSymbol, colSymbol;
	bool rowWin, colWin;
	for (int i = 0; i <= 2; i++) {
		
		for (int j = 0; j <= 2; j++) {
			colWin = false;
			if (i == 0) {
				colSymbol = board[i][j];
			}
			rowWin = true;
			if (j == 0) {
				rowSymbol = board[j][i];
			}
			cout << "j: " << j << " i: " << i << " board[j][i]: " << board[j][i] << endl;
			system("pause");
			if (board[j][i] == ' ') {
				
				rowWin = false;
			}
		}

	}
	return rowWin || colWin;
}
