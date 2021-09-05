#pragma once
#include "pch.h"
#include "board.h"
#include "list.h"
class application {
public:
	void title();
	void reset();
	void test();
	void run(board game,list list, bool white);
	void load();
	int letter(char input);
};