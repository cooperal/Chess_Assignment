#pragma once
#include "square.h"
class board {
public:
	void print_board();
	void reset_board();
	void move(int column, int row,int future_column, int future_row);
	void print_piece(int column, int row, char colour, char piece);
	bool is_legal(int column, int row, int future_column, int future_row,bool white);
	bool won();
	square board[8][8];
};