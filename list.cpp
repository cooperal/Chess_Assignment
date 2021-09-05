#include "pch.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "list.h"

void list::NewNode(int row, char col, int fut_row, char fut_col,bool occupied,char piece, bool white){
	list *temp;
	temp = new list;
	temp->row = row;
	temp->col = col;
	temp->fut_row = fut_row;
	temp->fut_col = fut_col;
	if (occupied == true) {
		temp->captured = true;
		if (white == true)
			temp->white = 'w';
		if (white == false)
			temp->white = 'b';
		temp->piece = piece;
	}
	temp->next = NULL;
	if (head == NULL) {
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else {
		tail->next = temp;
		tail = temp;

	}
	
}

void list::print_list() {
	list *temp = new list;
	temp = head;
	while (temp != NULL) {
		std::cout << temp->col << temp->row << " to " << temp->fut_col << temp->fut_row ;
		if (temp->captured == true) {
			std::cout << " capturing " << temp->white << temp->piece << "." << std::endl;
		}
		else
			std::cout << std::endl;
		temp = temp->next;
	}
}

void list::save() {
	std::ofstream ofs("Chess_save.txt");
	list *temp = new list;
	temp = head;
	while (temp != NULL) {
		ofs << temp->col << temp->row << " " << temp->fut_col << temp->fut_row << "\n";
		temp = temp->next;
	}
	std::cout << "Game saved! (probably...)" << std::endl;
}

list::~list(){
	while (head != NULL) {
		list *temp = new list;
		temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
	delete tail;
}

