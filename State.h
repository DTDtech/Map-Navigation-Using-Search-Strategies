#pragma once
#include "MapStructure.h"
#include <string>

class MapStructure;

class State {
	friend class MapStructure;

public:
	//State();
	State(int x_Pos, int y_Pos);
	//void SetStraightlineCostToGoal(int x_Pos, int y_Pos, int goal_X_Pos, int goal_Y_Pos);
	void SetCostToState(int cost);
	int GetCostToState();
	void SetDepth(int depth);
	int GetDepth();
	//double getStraightlineCostToGoal();
	int GetXPosition();
	int GetYPosition();

private:
	int x_Position;
	int y_Position;
	//double straightlineCostToGoal;
	int costToState;
	int expansionDepth;
	State* parentNodePointer;
};
