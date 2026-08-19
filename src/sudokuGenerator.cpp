#pragma once
#include "config.h"

NumberGrid cellNumbers[cellCount][cellCount] = {
	{0,1,0,0,0,4,0,0,0},
	{4,2,0,0,0,0,0,0,0},
	{0,3,0,0,0,0,4,0,0},
	{0,4,5,6,0,0,0,0,0},
	{0,0,0,7,0,0,0,0,4},
	{0,0,0,4,0,0,0,0,0},
	{0,0,4,0,0,0,0,0,0},
	{0,0,0,0,4,0,0,0,0},
	{0,0,0,0,0,0,0,4,0}
};

NumberGrid generateCompleteSudoku() {
	return;
}