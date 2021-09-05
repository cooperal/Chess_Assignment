#pragma once
#include "pch.h"
#include <cmath>
#include "board.h"
#include "square.h"

class list {
private:
	list *head, *tail;
	int row;
	char col;
	int fut_row;
	char fut_col;
	bool captured = false;
	char white;
	char piece;
	list *next;
public:
	list() {
		head = NULL;
		tail = NULL;
	}
	~list();
	void NewNode(int row, char col, int fut_row, char fut_col,bool occupied,char piece,bool white);
	void print_list();
	void save();
};