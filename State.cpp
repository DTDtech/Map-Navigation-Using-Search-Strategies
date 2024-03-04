#include "State.h"
#include <math.h>  
using namespace std;

State::State(int x_Pos, int y_Pos) {
	x_Position = x_Pos;
	y_Position = y_Pos;
	costToState = 0;
	expansionDepth = 0;
	parentNodePointer = NULL;
}

void State::SetCostToState(int cost) {
	costToState = cost;
}

int State::GetCostToState() {
	return costToState;
}

void State::SetDepth(int depth) {
	expansionDepth = depth;
}

int State::GetDepth() {
	return expansionDepth;
}

int State::GetXPosition() {
	return x_Position;
}

int State::GetYPosition() {
	return y_Position;
}