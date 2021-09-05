#include "pch.h"
#include <iostream>
#include <cmath>
#include "board.h"
#include "square.h"

// used to use hex chars in these defines but it caused issues 
#define WHITE_SQUARE '||' 
#define BLACK_SQUARE '  '

bool first = true;

void board::print_piece(int column, int row, char colour, char piece) {
	if (first) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j].occupied = false;
			}
		}
		first = false;
	}
	
	board[row][column].piece = piece;
	if (colour == 'w') {
		board[row][column].white = true;
		board[row][column].occupied = true;
	}
	else if (colour == 'b') {
		board[row][column].white = false;
		board[row][column].occupied = true;
	}
	else {
		std::cout << "no." << std::endl;
	}
}

void board::reset_board() {
	board[0][0].piece = 'r';
	board[0][1].piece = 'n';
	board[0][2].piece = 'b';
	board[0][3].piece = 'q';
	board[0][4].piece = 'k';
	board[0][5].piece = 'b';
	board[0][6].piece = 'n';
	board[0][7].piece = 'r';
	for (int i = 0; i < 8; i++)
		board[1][i].piece = 'p';
	for (int i = 0; i < 8; i++)
		board[6][i].piece = 'p';
	board[7][0].piece = 'r';
	board[7][1].piece = 'n';
	board[7][2].piece = 'b';
	board[7][3].piece = 'q';
	board[7][4].piece = 'k';
	board[7][5].piece = 'b';
	board[7][6].piece = 'n';
	board[7][7].piece = 'r';

	board[7][0].white = false;
	board[7][1].white = false;
	board[7][2].white = false;
	board[7][3].white = false;
	board[7][4].white = false;
	board[7][5].white = false;
	board[7][6].white = false;
	board[7][7].white = false;
	for (int i = 0; i < 8; i++)
		board[6][i].white = false;
	for (int i = 0; i < 8; i++)
		board[1][i].white = true;
	board[0][0].white = true;
	board[0][1].white = true;
	board[0][2].white = true;
	board[0][3].white = true;
	board[0][4].white = true;
	board[0][5].white = true;
	board[0][6].white = true;
	board[0][7].white = true;

	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j].piece = ' ';
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].piece == ' ')
				board[i][j].occupied = false;
			else
				board[i][j].occupied = true;
		}
	}

	
}

void board::print_board(){
	bool printed = false;
	bool black = true;
	bool rowx = false;
	std::cout << "  A   B   C   D   E   F   G   H" << std::endl;
	for (int i = 0; i < 16; i++) {
		if (!rowx) {
			std::cout << ((i)/2)+1;
		}
		else {
			std::cout << " ";
		}
		for (int j = 0; j < 8; j++) {
			if (black == true) {
				if ((printed == false) && board[i/2][j].occupied == true) {
					std::cout << char(BLACK_SQUARE);
					if (board[i / 2][j].white == false)
						std::cout << 'b';
					else
						std::cout << 'w';
					std::cout << board[i / 2][j].piece;
					std::cout << char(BLACK_SQUARE);
					
				}
				else {
					for (int i =0;i<4;i++){
						std::cout << char(BLACK_SQUARE);
					}
					
				}
			}
				
			else {
				if ((printed == false) && board[i/2][j].occupied == true) {
					std::cout << char(WHITE_SQUARE);
					if (board[i / 2][j].white == false)
						std::cout << 'b';
					else
						std::cout << 'w';
					std::cout << board[i / 2][j].piece;
					std::cout << char(WHITE_SQUARE);
					
				}
				else {
					for (int i = 0; i < 4; i++) {
						std::cout << char(WHITE_SQUARE);
					}
					
				}
				
			}
			black = !black;
			
		}
		std::cout << std::endl;
		if (rowx == true) {
			black = !black;
		}
		rowx = !rowx;
		printed = !printed;
	}
}

bool board::is_legal(int column, int row, int future_column, int future_row,bool white) {
	if (board[future_row][future_column].occupied == true) {
		if (board[future_row][future_column].white == white) { // prevents a colur from taking their own pieces.
			return false;
		}
	}
	
	if (board[row][column].white != white) { //prevents white from moving black pieces and vice versa.
		return false;
	}
	if ((future_row > 7) || (future_row < 0) || (future_column > 7) || (future_column < 0))
		return false;
	//knight.
	if (board[row][column].piece == 'n') {
		if (((future_column == (column - 1)) || (future_column == (column + 1)))
			&& ((future_row == (row + 2)) || (future_row == (row - 2)))) {
			return true;
		}
		if (((future_column == (column - 2)) || (future_column == (column + 2)))
				&& ((future_row == (row + 1)) || (future_row == (row - 1)))) {

			return true;
		}
		else return false;
	}
	//pawn.
	if (board[row][column].piece == 'p') {
		//black pawn
		if (board[row][column].white == false) {
			if ((board[row][column].HasMoved == false) && (future_row == row - 2) && (future_column == column)) {
				if ((board[row-1][column].occupied == false) && (board[row -2][column].occupied == false))
					return true;
			}
			if (((future_row) == (row - 1)) && (future_column == column)) {
				if (board[row - 1][column].occupied == false)
					return true;
			}
			if ((future_row == (row - 1) && ((future_column == (column + 1)) || (future_column == (column - 1)))
				&& (board[future_row][future_column].occupied == true))) {
				return true;
			}
			else
				return false;

		}
		//white pawn
		else  if (board[row][column].white == true){
			if ((board[row][column].HasMoved == false) && (future_row == row + 2) && (future_column == column)) {
				if ((board[row + 1][column].occupied == false) && (board[row + 2][column].occupied == false))
					return true;
			}
			if (((future_row) == (row + 1)) && (future_column == column)) {
				if (board[row+1][column].occupied == false)
					return true;
			}
			if ((future_row == (row + 1) && ((future_column == (column + 1)) || (future_column == (column - 1)))
				&& (board[future_row][future_column].occupied == true))) {
				return true;
			}
			else
				return false;
		}

	}
	//rook
	if (board[row][column].piece == 'r') {
		if (((row == future_row) || (column == future_column)) && ((row != future_row) || (column != future_column))) {
			for (int i = 1; i < abs(future_row - row); i++) {
				if (future_row != row) {
					if (future_row > row) {
						if (board[row + i][column].occupied == true) {
							return false;
						}
					}
					if (future_row < row) {
						if (board[row - i][column].occupied == true)
							return false;
					}
				}
			}
			for (int i = 1; i < abs(future_column - column); i++) {
				if (future_column != column) {
					if (future_column > column) {
						if (board[row][column + i].occupied == true) {
							return false;
						}
					}
					if (future_column < column) {
						if (board[row][column - i].occupied == true) {
							return false;
						}
					}
				}
			}
			return true;
		}
	}
	//bishop.
	if (board[row][column].piece == 'b') {
		if ((future_column == column) || (future_row == row)) {
			return false;
		}
		if (abs(future_column - column) != abs(future_row - row)) {
			return false;
		}
		for (int i = 1; i < abs(future_column - column); i++) {
			if ((future_column > column) && (future_row > row)) {
				if (board[row + i][column + i].occupied == true)
					return false;
			}
			if ((future_column > column) && (future_row < row)) {
				if (board[row - i][column + i].occupied == true)
					return false;
			}
			if ((future_column < column) && (future_row > row)) {
				if (board[row + i][column - i].occupied == true)
					return false;
			}
			if ((future_column < column) && (future_row < row)) {
				if (board[row - i][column - i].occupied == true)
					return false;
			}
		}
		return true;
	}
	//queen 
	if (board[row][column].piece == 'q') {
		//where queen acts like a rook.
		if (((row == future_row) || (column == future_column)) && ((row != future_row) || (column != future_column))) {
			bool possible = true;
			if (future_row != row) {
				for (int i = 1; i < abs(future_row - row); i++) {
					if (future_row > row) {
						if (board[row + i][column].occupied == true) {
							return false;
						}
					}
					if (future_row < row) {
						if (board[row - i][column].occupied == true)
							return false;
					}
				}
			}
			if (future_column != column) {
				for (int i = 1; i < abs(future_column - column); i++) {
					if (future_column > column) {
						if (board[row][column + i].occupied == true) {
							return false;
						}
					}
					if (future_column < column) {
						if (board[row][column - i].occupied == true) {
							return false;
						}
					}
				}
			}
			return true;

		}
		//where queen acts like bishop.
		if ((future_column != column) && (future_row != row)) {
			if (abs(future_column - column) != abs(future_row - row)) {
				return false;
			}
			for (int i = 1; i < abs(future_column - column); i++) {
				if ((future_column > column) && (future_row > row)) {
					if (board[row + i][column + i].occupied == true)
						return false;
				}
				if ((future_column > column) && (future_row < row)) {
					if (board[row - i][column + i].occupied == true)
						return false;
				}
				if ((future_column < column) && (future_row > row)) {
					if (board[row + i][column - i].occupied == true)
						return false;
				}
				if ((future_column < column) && (future_row < row)) {
					if (board[row - i][column - i].occupied == true)
						return false;
				}

			}
			return true;
		}

	}
	//King legality.
	if (board[row][column].piece == 'k') {
		if ((future_column == column + 2) && (board[row][column].HasMoved == false) && (board[row][column + 3].HasMoved == false)) {
			if ((board[row][column + 1].occupied == false) && (board[row][column + 2].occupied == false))
				return true;
		}
		
		if ((abs(future_column - column) > 1) || (abs(future_row - row) > 1)) {
			return false;
		}
		
		return true;
	}
	else
		return false;
}

void board::move(int column, int row, int future_column, int future_row) {
	if (board[row][column].piece == 'p') { // manages pawn promotion.
		char input;
		board[future_row][future_column].HasMoved = true;
		if (board[row][column].white == false) {
			if (future_row == 0) {
				bool correct = false;
				std::cout << "You can promote your pawn! what piece would you like(eg. r,n,q,b)" << std::endl;
				std::cin >> input;
				if ((input == 'q') || (input == 'r') || (input == 'b') || (input == 'n')) {
					correct = true;
				}
				while (correct == false) {
					std::cout << "Thats not a correct letter! try again.(eg. n for knight)" << std::endl;
					std::cin >> input;
					if ((input == 'q') || (input == 'r') || (input == 'b') || (input == 'n')) {
						correct = true;
					}
				}
				board[row][column].piece = input;
			}
		}
		if (board[row][column].white == true) {
			if (future_row == 7) {
				bool correct = false;
				std::cout << "You can promote your pawn! what piece would you like(eg. r,n,q,b)" << std::endl;
				std::cin >> input;
				if ((input == 'q') || (input == 'r') || (input == 'b') || (input == 'n')) {
					correct = true;
				}
				while (correct == false) {
					std::cout << "Thats not a correct letter! try again.(eg. n for knight)" << std::endl;						std::cin >> input;
					if ((input == 'q') || (input == 'r') || (input == 'b') || (input == 'n')) {
						correct = true;
					}
				}
				board[row][column].piece = input;
			}
		}
	}

	if (board[row][column].piece == 'k') { // manages castling.(no queen side castle though)
		if (board[row][column].white == false) {
			if (future_column == column + 2) {
				move(7, 7, 5, 7);
			}
		}
		if (board[row][column].white == true) {
			if (future_column == column + 2) {
				move(7, 0, 5, 0);
			}
		}
	}
	// moves piece
	board[future_row][future_column].piece = board[row][column].piece;
	board[future_row][future_column].white = board[row][column].white;
	board[future_row][future_column].occupied = true;
	board[row][column].piece = ' ';
	board[row][column].occupied = false;
}


bool board::won() {
	int counter = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].piece == 'k') {
				counter++;
			}
		}
	}
	if (counter == 2) {
		return false;
	}
	if (counter == 1) {
		return true;
	}
	return false;
}