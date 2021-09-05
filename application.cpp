#include "pch.h"
#include <iostream>
#include <fstream>
#include "application.h"
#include "board.h"
#include "square.h"
#include "list.h"


void application::title(){
	char ans = NULL;
	int counter = 0;
	for (int i = 2; i > 0; i--) {
		std::cout << "------------------" << std::endl;
	}
	std::cout << "Weak Chess Imitation" << std::endl;
	for (int i = 2; i > 0; i--) {
		std::cout << "------------------" << std::endl ;
	}
	std::cout << " Welcome to Weak Chess Imitation, press a key to (P)lay, (T)est, (L)oad or (Q)uit." << std::endl;
	std::cin >> ans;
	while (ans != 'P' && ans != 'T' && ans != 'Q' && ans != 't' && ans != 'p' && ans != 'q' && ans != 'L' && ans != 'l') {
		if (counter == 3) {
			std::cout << "You're getting on my nerves now, try again." <<  std::endl;
			counter++;
		}
		else if (counter == 5) {
			std::cout << "That's enough, you can leave then." << std::endl;
			break;
		}
		else {
			std::cout << " No thats not what I asked for, try again" << std::endl;
			counter++;
		}
		std::cin >> ans;
		
	}
	if ((ans == 'P') || (ans == 'p')) {
		reset();

	}
	if ((ans == 'T') || (ans == 't')) {
		test();
	}
	if ((ans == 'L') || (ans == 'l')) {
		load();
	}


}

int application::letter(char input) {
	if ((input == 'A') || (input == 'a')) {
		return 0;
	}
	if ((input == 'B') || (input == 'b')) {
		return 1;
	}
	if ((input == 'C') || (input == 'c')) {
		return 2;
	}
	if ((input == 'D') || (input == 'd')) {
		return 3;
	}
	if ((input == 'E') || (input == 'e')) {
		return 4;
	}
	if ((input == 'F') || (input == 'f')) {
		return 5;
	}
	if ((input == 'G') || (input == 'g')) {
		return 6;
	}
	if ((input == 'H') || (input == 'h')) {
		return 7;
	}
	else
		return 500;
}

void application::test() {
	char input, column_input, colour, piece;
	int row_input;
	board game;
	game.print_board();
	std::cout << "(P)rint a piece, (R)un the game, (Q)uit." << std::endl;
	std::cin >> input;
	while (input != 'Q') {
		if (input == 'P') {
			std::cout << "print a piece?(A5 wq)" << std::endl;
			std::cin >> column_input >> row_input >> colour >> piece;
			game.print_piece(letter(column_input), row_input-1, colour, piece);
			game.print_board();
		}
		if (input == 'R') {
			list list;
			run(game, list , true);
		}
		std::cout << "(P)rint a piece, (R)un the game, (Q)uit." << std::endl;
		std::cin >> input;
	}
}
void application::reset() {
	board game;
	list list;
	game.reset_board();
	run(game, list, true);
}

void application::load() {
	board game;
	list list;
	game.reset_board();
	char col, fut_col;
	int  row, fut_row;
	bool white = true;
	std::ifstream ifs;
	ifs.open("Chess_save.txt");
	while (true) {
		ifs >> col >> row >> fut_col >> fut_row;
		std::cout << col << row << " " << fut_col << fut_row << std::endl;
		if (game.is_legal(letter(col), row - 1, letter(fut_col), fut_row - 1, white)) {
			list.NewNode(row, col, fut_row, fut_col, game.board[fut_row - 1][letter(fut_col)].occupied, game.board[fut_row - 1][letter(fut_col)].piece, game.board[fut_row - 1][letter(fut_col)].white);
			game.move(letter(col), row - 1, letter(fut_col), fut_row - 1);
			white = !white;
		}
		else if (!ifs)
			break;
		else
			std::cout << "Bruh.";
	}
	run(game , list, white);
}

void application::run(board game,list list,bool white) {
	char column_input = NULL,column,future_column;
	int row_input = NULL, row, future_row;
	bool g = false;
	game.print_board();
	while (g != true) {
		int legal = 0;
		if (white) {
			std::cout << "Whites move, enter the row and column of the piece you wish to move and then where you wish to move it to. (eg. A5 A6, (R0)estart, (P0)rint moves,(S0)ave)" << std::endl;
		}
		else 
			std::cout << "Blacks move, enter the row and column of the piece you wish to move and then where you wish to move it to. (eg. A5 A6, (R0)estart,(P0)rint moves,(S0)ave)" << std::endl;
		while (legal != 1) {
			std::cin >> column_input >> row_input;
			if ((column_input == 'R')|| (column_input == 'r')) {
				
				reset();
			}  
			if (column_input == 'P' || column_input == 'p') {
				list.print_list();
			}
			if (column_input == 'S' || column_input == 's') {
				list.save();
			}
			if ((column_input != 'R') && (column_input != 'r') && (column_input != 'P') && (column_input != 'p') && (column_input != 'S') && (column_input != 's')) {
				row = row_input;
				column = column_input;
				std::cin >> column_input >> row_input;
				future_row = row_input;
				future_column = column_input;
				std::cout << std::endl;
				if (game.is_legal(letter(column), (row - 1), letter(future_column), (future_row - 1), white)) {
					list.NewNode(row, column, future_row, future_column,game.board[future_row - 1][letter(future_column)].occupied,game.board[future_row - 1][letter(future_column)].piece,game.board[future_row - 1][letter(future_column)].white);
					game.move(letter(column), (row - 1), letter(future_column), (future_row - 1));
					legal = 1;
				}
				else {
					std::cout << "Wait. That's Illegal! try again." << std::endl;
					legal = 0;
				}
			}
		}
		game.print_board();
		if (game.won() == true) {
			g = true;
		}
		white = !white;
	}
	if (white == false) {
		std::cout << "White has won the game!" << std::endl;
	}
	if (white == true) {
		std::cout << "Black has won the game!" << std::endl;
	}
}
