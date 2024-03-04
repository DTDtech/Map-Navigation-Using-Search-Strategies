#pragma once
#include <utility>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include "State.h"

class State;

class MapStructure {
public:
	MapStructure(std::pair<int, int> RowsAndCols, std::pair<int, int> InitialPos, std::vector <std::pair<int, int>> Goalpos, std::map<std::pair<int, int>, std::pair<int, int>> WallPos);

	//void printPositions();
	void CreateMapRepresentation();

	void ExpandFromRootNode(std::string algoName);
	void ExpandLeafNodesDFS(std::stack<State>& frontier, std::stack<std::string>& Path, int& numberOfNodes);
	void ExpandLeafNodesBFS(std::queue<State>& frontier, std::stack<std::string>& Path, int& numberOfNodes);
	void ExpandLeafNodesGBFS(std::list<State>& frontier, std::stack<std::string>& Path, int& numberOfNodes);
	void ExpandLeafNodesDLS(std::stack<State*>& frontier, std::stack<std::string>& Path, int maxDepth, int& numberOfNodes);

	bool UpNodeIsValid(State& node);
	bool LeftNodeIsValid(State& node);
	bool DownNodeIsValid(State& node);
	bool RightNodeIsValid(State& node);
	bool IsGoalState(State& node);

	void AddNodeToStack(State& node, std::stack<State>& frontier, std::string nodeToAddPosition);
	void AddNodeToQueue(State& node, std::queue<State>& frontier, std::string nodeToAddPosition);
	void AddNodeToList(State& node, std::list<State>& frontier, std::string nodeToAddPosition, std::string algoName);
	void AddNodePointerToStack(State& node, std::stack<State*>& frontier, std::string nodeToAddPosition);

	void RemoveNodeFromStack(State& node, std::stack<State>& frontier);
	void PrintPath(State& node, std::stack<std::string> Path);

private:
	std::pair <int, int> RowsAndColumns; 
	std::pair <int, int> InitialPosition;
	std::vector <std::pair<int, int>> GoalstatePositions;
	std::pair <int, int> chosenGoalState;
	std::map<std::pair<int, int>, std::pair<int, int>> Walls;
	std::vector<std::vector<std::string>> MapRepresentation;
	State* tempParentNodePointer;
};

