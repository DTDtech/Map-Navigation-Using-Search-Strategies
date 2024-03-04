#include "MapStructure.h"
#include <utility>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <queue>
#include <stack>
#include <list>
#include "State.h"
using namespace std;

MapStructure::MapStructure(pair<int, int> RowsAndCols, std::pair<int, int> InitialPos, vector <std::pair<int, int>> GoalPos, map<std::pair<int, int>, std::pair<int, int>> WallPos) :
	RowsAndColumns(RowsAndCols), InitialPosition(InitialPos), GoalstatePositions(GoalPos), Walls(WallPos), tempParentNodePointer(NULL) {
	//Randomly choose goal state from list of goal states to be used for searching
	chosenGoalState = GoalstatePositions[rand() % GoalstatePositions.size()];

	//Create map representation using two dimensional vector
	MapRepresentation.reserve(RowsAndCols.second);
	for (int i = 0; i < RowsAndCols.second; i++) {
		vector<std::string>rows(RowsAndCols.first);
		MapRepresentation.push_back(rows);
	}
}

void MapStructure::CreateMapRepresentation() {
	//Create map representation using two dimensional vector
	//auto MapRepresentation = vector<vector<string>>(RowsAndColumns.second, vector<string>(RowsAndColumns.first));

	//Pin down wall positions
	for (auto WallStartingPosition : Walls) {
		for (int i = 0; i < WallStartingPosition.second.first; i++) {
			for (int j = 0; j < WallStartingPosition.second.second; j++) {
				MapRepresentation[WallStartingPosition.first.first + i][WallStartingPosition.first.second + j] = "wall";
			}
		}
	}
}

bool MapStructure::UpNodeIsValid(State& node) {
	if ((node.GetYPosition() - 1 >= 0) && (node.GetYPosition() - 1 < RowsAndColumns.first)) {
		if (MapRepresentation[node.GetXPosition()][node.GetYPosition() - 1] != "discovered" && (MapRepresentation[node.GetXPosition()][node.GetYPosition() - 1] != "wall")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
bool MapStructure::LeftNodeIsValid(State& node) {
	if ((node.GetXPosition() - 1 >= 0) && (node.GetXPosition() - 1 < RowsAndColumns.second)) {
		if (MapRepresentation[node.GetXPosition() - 1][node.GetYPosition()] != "discovered" && (MapRepresentation[node.GetXPosition() - 1][node.GetYPosition()] != "wall")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
bool MapStructure::DownNodeIsValid(State& node) {
	if ((node.GetYPosition() + 1 >= 0) && (node.GetYPosition() + 1 < RowsAndColumns.first)) {
		if (MapRepresentation[node.GetXPosition()][node.GetYPosition() + 1] != "discovered" && (MapRepresentation[node.GetXPosition()][node.GetYPosition() + 1] != "wall")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
bool MapStructure::RightNodeIsValid(State& node) {
	if ((node.GetXPosition() + 1 >= 0) && (node.GetXPosition() + 1 < RowsAndColumns.second)) {
		if (MapRepresentation[node.GetXPosition() + 1][node.GetYPosition()] != "discovered" && (MapRepresentation[node.GetXPosition() + 1][node.GetYPosition()] != "wall")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
bool MapStructure::IsGoalState(State& node) {
	if (node.GetXPosition() == chosenGoalState.first && node.GetYPosition() == chosenGoalState.second) {
		return true;
	}
	else {
		return false;
	}
}

void MapStructure::AddNodeToStack(State& node, std::stack<State>& frontier, std::string nodeToAddPosition) {
	if (nodeToAddPosition == "up") {
		State* UpNode = new State(node.GetXPosition(), node.GetYPosition() - 1);
		UpNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = UpNode;
		frontier.push(*UpNode);
	}
	else if (nodeToAddPosition == "left") {
		State* LeftNode = new State(node.GetXPosition() - 1, node.GetYPosition());
		LeftNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = LeftNode;
		frontier.push(*LeftNode);
	}
	else if (nodeToAddPosition == "down") {
		State* DownNode = new State(node.GetXPosition(), node.GetYPosition() + 1);
		DownNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = DownNode;
		frontier.push(*DownNode);
	}
	else if (nodeToAddPosition == "right") {
		State* RightNode = new State(node.GetXPosition() + 1, node.GetYPosition());
		RightNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = RightNode;
		frontier.push(*RightNode);
	}
}


void MapStructure::AddNodeToQueue(State& node, queue<State>& frontier, string nodeToAddPosition) {
	if (nodeToAddPosition == "up") {
		State* UpNode = new State(node.GetXPosition(), node.GetYPosition() - 1);
		UpNode->parentNodePointer = tempParentNodePointer;
		frontier.push(*UpNode);
	}
	else if (nodeToAddPosition == "left") {
		State* LeftNode = new State(node.GetXPosition() - 1, node.GetYPosition());
		LeftNode->parentNodePointer = tempParentNodePointer;
		frontier.push(*LeftNode);
	}
	else if (nodeToAddPosition == "down") {
		State* DownNode = new State(node.GetXPosition(), node.GetYPosition() + 1);
		DownNode->parentNodePointer = tempParentNodePointer;
		frontier.push(*DownNode);
	}
	else if (nodeToAddPosition == "right") {
		State* RightNode = new State(node.GetXPosition() + 1, node.GetYPosition());
		RightNode->parentNodePointer = tempParentNodePointer;
		frontier.push(*RightNode);
	}
}

void MapStructure::AddNodeToList(State& node, list<State>& frontier, string nodeToAddPosition, string algoName) {
	if (algoName == "GBFS") {
		if (nodeToAddPosition == "up") {
			State* UpNode = new State(node.GetXPosition(), node.GetYPosition() - 1);
			UpNode->parentNodePointer = tempParentNodePointer;
			frontier.push_back(*UpNode);
		}
		else if (nodeToAddPosition == "left") {
			State* LeftNode = new State(node.GetXPosition() - 1, node.GetYPosition());
			LeftNode->parentNodePointer = tempParentNodePointer;
			frontier.push_back(*LeftNode);
		}
		else if (nodeToAddPosition == "down") {
			State* DownNode = new State(node.GetXPosition(), node.GetYPosition() + 1);
			DownNode->parentNodePointer = tempParentNodePointer;
			frontier.push_back(*DownNode);
		}
		else if (nodeToAddPosition == "right") {
			State* RightNode = new State(node.GetXPosition() + 1, node.GetYPosition());
			RightNode->parentNodePointer = tempParentNodePointer;
			frontier.push_back(*RightNode);
		}
	}
	else if (algoName == "AS") {
		if (nodeToAddPosition == "up") {
			State* UpNode = new State(node.GetXPosition(), node.GetYPosition() - 1);
			UpNode->parentNodePointer = tempParentNodePointer;
			UpNode->SetCostToState(tempParentNodePointer->GetCostToState() + 1);
			frontier.push_back(*UpNode);
		}
		else if (nodeToAddPosition == "left") {
			State* LeftNode = new State(node.GetXPosition() - 1, node.GetYPosition());
			LeftNode->parentNodePointer = tempParentNodePointer;
			LeftNode->SetCostToState(tempParentNodePointer->GetCostToState() + 1);
			frontier.push_back(*LeftNode);
		}
		else if (nodeToAddPosition == "down") {
			State* DownNode = new State(node.GetXPosition(), node.GetYPosition() + 1);
			DownNode->parentNodePointer = tempParentNodePointer;
			DownNode->SetCostToState(tempParentNodePointer->GetCostToState() + 1);
			frontier.push_back(*DownNode);
		}
		else if (nodeToAddPosition == "right") {
			State* RightNode = new State(node.GetXPosition() + 1, node.GetYPosition());
			RightNode->parentNodePointer = tempParentNodePointer;
			RightNode->SetCostToState(tempParentNodePointer->GetCostToState() + 1);
			frontier.push_back(*RightNode);
		}
	}
}

void MapStructure::AddNodePointerToStack(State& node, std::stack<State*>& frontier, std::string nodeToAddPosition) {
	if (nodeToAddPosition == "up") {
		State* UpNode = new State(node.GetXPosition(), node.GetYPosition() - 1);
		UpNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = UpNode;
		frontier.push(UpNode);
	}
	else if (nodeToAddPosition == "left") {
		State* LeftNode = new State(node.GetXPosition() - 1, node.GetYPosition());
		LeftNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = LeftNode;
		frontier.push(LeftNode);
	}
	else if (nodeToAddPosition == "down") {
		State* DownNode = new State(node.GetXPosition(), node.GetYPosition() + 1);
		DownNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = DownNode;
		frontier.push(DownNode);
	}
	else if (nodeToAddPosition == "right") {
		State* RightNode = new State(node.GetXPosition() + 1, node.GetYPosition());
		RightNode->parentNodePointer = tempParentNodePointer;
		tempParentNodePointer = RightNode;
		frontier.push(RightNode);
	}
}

void MapStructure::RemoveNodeFromStack(State& node, std::stack<State>& frontier) {
	tempParentNodePointer = frontier.top().parentNodePointer;
	frontier.pop();
}

void MapStructure::PrintPath(State& node, stack<string> Path) {
	if ((node.GetXPosition() != InitialPosition.first) || (node.GetYPosition() != InitialPosition.second)) {
		if (node.parentNodePointer->GetYPosition() == node.GetYPosition() + 1) {
			Path.push("up");
			PrintPath(*node.parentNodePointer, Path);
		}
		else if (node.parentNodePointer->GetYPosition() == node.GetYPosition() - 1) {
			Path.push("down");
			PrintPath(*node.parentNodePointer, Path);
		}
		else if (node.parentNodePointer->GetXPosition() == node.GetXPosition() + 1) {
			Path.push("left");
			PrintPath(*node.parentNodePointer, Path);
		}
		else if (node.parentNodePointer->GetXPosition() == node.GetXPosition() - 1) {
			Path.push("right");
			PrintPath(*node.parentNodePointer, Path);
		}
		else {
			Path.push("cannot track parent node");
		}
	}
	else {
		while (!empty(Path)) {
			cout << Path.top() << "; ";
			Path.pop();
		}
		cout << "\n";
	}
}

void MapStructure::ExpandFromRootNode(std::string algoName) {
	State* rootNodePointer = new State(InitialPosition.first, InitialPosition.second);
	tempParentNodePointer = rootNodePointer;
	int numberOfNodes = 1;
	stack<string> Path;
	MapRepresentation[InitialPosition.first][InitialPosition.second] = "discovered";
	if (algoName == "DFS") {
		stack<State> StackFrontier;
		StackFrontier.push(*rootNodePointer);
		if (IsGoalState(*rootNodePointer)) {
			cout << "Initial position is goal state." << endl;
		}
		else {
			if (UpNodeIsValid(*rootNodePointer)) {
				AddNodeToStack(*rootNodePointer, StackFrontier, "up");
				MapRepresentation[StackFrontier.top().GetXPosition()][StackFrontier.top().GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDFS(StackFrontier, Path, numberOfNodes);
			}
			else if (LeftNodeIsValid(*rootNodePointer)) {
				AddNodeToStack(*rootNodePointer, StackFrontier, "left");
				MapRepresentation[StackFrontier.top().GetXPosition()][StackFrontier.top().GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDFS(StackFrontier, Path, numberOfNodes);
			}
			else if (DownNodeIsValid(*rootNodePointer)) {
				AddNodeToStack(*rootNodePointer, StackFrontier, "down");
				MapRepresentation[StackFrontier.top().GetXPosition()][StackFrontier.top().GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDFS(StackFrontier, Path, numberOfNodes);
			}
			else if (RightNodeIsValid(*rootNodePointer)) {
				AddNodeToStack(*rootNodePointer, StackFrontier, "right");
				MapRepresentation[StackFrontier.top().GetXPosition()][StackFrontier.top().GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDFS(StackFrontier, Path, numberOfNodes);
			}
		}
	}
	else if (algoName == "BFS") {
		queue<State> QueueFrontier;
		if (IsGoalState(*rootNodePointer)) {
			cout << "Initial position is goal state." << endl;
		}
		else {
			if (UpNodeIsValid(*rootNodePointer)) {
				AddNodeToQueue(*rootNodePointer, QueueFrontier, "up");
				MapRepresentation[QueueFrontier.back().GetXPosition()][QueueFrontier.back().GetYPosition()] = "discovered";
				numberOfNodes++;
			}
			if (LeftNodeIsValid(*rootNodePointer)) {
				AddNodeToQueue(*rootNodePointer, QueueFrontier, "left");
				MapRepresentation[QueueFrontier.back().GetXPosition()][QueueFrontier.back().GetYPosition()] = "discovered";
				numberOfNodes++;
			}
			if (DownNodeIsValid(*rootNodePointer)) {
				AddNodeToQueue(*rootNodePointer, QueueFrontier, "down");
				MapRepresentation[QueueFrontier.back().GetXPosition()][QueueFrontier.back().GetYPosition()] = "discovered";
				numberOfNodes++;
			}
			if (RightNodeIsValid(*rootNodePointer)) {
				AddNodeToQueue(*rootNodePointer, QueueFrontier, "right");
				MapRepresentation[QueueFrontier.back().GetXPosition()][QueueFrontier.back().GetYPosition()] = "discovered";
				numberOfNodes++;
			}
			ExpandLeafNodesBFS(QueueFrontier, Path, numberOfNodes);
		}
	}
	else if (algoName == "GBFS") {
		list<State> listFrontier;
		if (IsGoalState(*rootNodePointer)) {
			cout << "Initial position is goal state." << endl;
		}
		else {
			if (UpNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "up", "GBFS");
				numberOfNodes++;
			}
			if (LeftNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "left", "GBFS");
				numberOfNodes++;
			}
			if (DownNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "down", "GBFS");
				numberOfNodes++;
			}
			if (RightNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "right", "GBFS");
				numberOfNodes++;
			}
			listFrontier.sort([&](State firstNode, State secondNode)
				{ return abs(chosenGoalState.first - firstNode.GetXPosition()) + abs(chosenGoalState.second - firstNode.GetYPosition()) <
				abs(chosenGoalState.first - secondNode.GetXPosition()) + abs(chosenGoalState.second - secondNode.GetYPosition()); });
			ExpandLeafNodesGBFS(listFrontier, Path, numberOfNodes);
		}
	}
	else if (algoName == "AS") {
		list<State> listFrontier;
		if (IsGoalState(*rootNodePointer)) {
			cout << "Initial position is goal state." << endl;
		}
		else {
			(*rootNodePointer).SetCostToState(0);
			if (UpNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "up", "AS");
				numberOfNodes++;
			}
			if (LeftNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "left", "AS");
				numberOfNodes++;
			}
			if (DownNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "down", "AS");
				numberOfNodes++;
			}
			if (RightNodeIsValid(*rootNodePointer)) {
				AddNodeToList(*rootNodePointer, listFrontier, "right", "AS");
				numberOfNodes++;
			}
			listFrontier.sort([&](State firstNode, State secondNode)
				{ return abs(chosenGoalState.first - firstNode.GetXPosition()) + abs(chosenGoalState.second - firstNode.GetYPosition()) + firstNode.GetCostToState() <
				abs(chosenGoalState.first - secondNode.GetXPosition()) + abs(chosenGoalState.second - secondNode.GetYPosition()) + secondNode.GetCostToState(); });
			ExpandLeafNodesGBFS(listFrontier, Path, numberOfNodes);
		}
	}
	else if (algoName == "CUS1") {
		int maximumDepthSearch;
		cout << "\nEnter a maximum depth for the search: ";
		cin >> maximumDepthSearch;
		while (std::cin.fail()) {
			std::cout << "Please enter an integer for maximum depth:" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> maximumDepthSearch;
		}
		stack<State*> StackFrontier;
		StackFrontier.push(rootNodePointer);
		StackFrontier.top()->SetDepth(0);
		if (IsGoalState(*rootNodePointer)) {
			cout << "Initial position is goal state." << endl;
		}
		else {
			if (UpNodeIsValid(*rootNodePointer)) {
				AddNodePointerToStack(*rootNodePointer, StackFrontier, "up");
				StackFrontier.top()->SetDepth(StackFrontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*StackFrontier.top()).GetXPosition()][(*StackFrontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDLS(StackFrontier, Path, maximumDepthSearch, numberOfNodes);
			}
			else if (LeftNodeIsValid(*rootNodePointer)) {
				AddNodePointerToStack(*rootNodePointer, StackFrontier, "left");
				StackFrontier.top()->SetDepth(StackFrontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*StackFrontier.top()).GetXPosition()][(*StackFrontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDLS(StackFrontier, Path, maximumDepthSearch, numberOfNodes);
			}
			else if (DownNodeIsValid(*rootNodePointer)) {
				AddNodePointerToStack(*rootNodePointer, StackFrontier, "down");
				StackFrontier.top()->SetDepth(StackFrontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*StackFrontier.top()).GetXPosition()][(*StackFrontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDLS(StackFrontier, Path, maximumDepthSearch, numberOfNodes);
			}
			else if (RightNodeIsValid(*rootNodePointer)) {
				AddNodePointerToStack(*rootNodePointer, StackFrontier, "right");
				StackFrontier.top()->SetDepth(StackFrontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*StackFrontier.top()).GetXPosition()][(*StackFrontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				ExpandLeafNodesDLS(StackFrontier, Path, maximumDepthSearch, numberOfNodes);
			}
			else {
				cout << "No solution found." << endl;
			}
		}
	}
	else {
		cout << "Invalid argument, please supply a valid method name." << endl;
	}
}

void MapStructure::ExpandLeafNodesDFS(stack<State>& frontier, stack<string>& Path, int& numberOfNodes) {
	if (IsGoalState(frontier.top())) {
		cout << "Initial position is goal state." << endl;
	}
	else {
		if (UpNodeIsValid(frontier.top())) {
			AddNodeToStack(frontier.top(), frontier, "up");
			MapRepresentation[frontier.top().GetXPosition()][frontier.top().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.top())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.top(), Path);
			}
			else {
				ExpandLeafNodesDFS(frontier, Path, numberOfNodes);
			}
		}
		else if (LeftNodeIsValid(frontier.top())) {
			AddNodeToStack(frontier.top(), frontier, "left");
			MapRepresentation[frontier.top().GetXPosition()][frontier.top().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.top())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.top(), Path);
			}
			else {
				ExpandLeafNodesDFS(frontier, Path, numberOfNodes);
			}
		}
		else if (DownNodeIsValid(frontier.top())) {
			AddNodeToStack(frontier.top(), frontier, "down");
			MapRepresentation[frontier.top().GetXPosition()][frontier.top().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.top())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.top(), Path);
			}
			else {
				ExpandLeafNodesDFS(frontier, Path, numberOfNodes);
			}
		}
		else if (RightNodeIsValid(frontier.top())) {
			AddNodeToStack(frontier.top(), frontier, "right");
			MapRepresentation[frontier.top().GetXPosition()][frontier.top().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.top())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.top(), Path);
			}
			else {
				ExpandLeafNodesDFS(frontier, Path, numberOfNodes);
			}
		}
		else {
			RemoveNodeFromStack(frontier.top(), frontier);
			ExpandLeafNodesDFS(frontier, Path, numberOfNodes);
		}
	}
}

void MapStructure::ExpandLeafNodesBFS(queue<State>& frontier, stack<string>& Path, int& numberOfNodes) {
	if (IsGoalState(frontier.front())) {
		cout << "Initial position is goal state." << endl;
	}
	else {
		State firstElementInFrontier = frontier.front();
		tempParentNodePointer = &firstElementInFrontier;
		if (UpNodeIsValid(frontier.front())) {
			AddNodeToQueue(frontier.front(), frontier, "up");
			MapRepresentation[frontier.back().GetXPosition()][frontier.back().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		if (LeftNodeIsValid(frontier.front())) {
			AddNodeToQueue(frontier.front(), frontier, "left");
			MapRepresentation[frontier.back().GetXPosition()][frontier.back().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		if (DownNodeIsValid(frontier.front())) {
			AddNodeToQueue(frontier.front(), frontier, "down");
			MapRepresentation[frontier.back().GetXPosition()][frontier.back().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		if (RightNodeIsValid(frontier.front())) {
			AddNodeToQueue(frontier.front(), frontier, "right");
			MapRepresentation[frontier.back().GetXPosition()][frontier.back().GetYPosition()] = "discovered";
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		frontier.pop();
		if (empty(frontier)) {
			cout << "No solution found.";
		}
		ExpandLeafNodesBFS(frontier, Path, numberOfNodes);
	}
}

void MapStructure::ExpandLeafNodesGBFS(list<State>& frontier, stack<std::string>& Path, int& numberOfNodes) {
	if (IsGoalState(frontier.front())) {
		cout << "Initial position is goal state." << endl;
	}
	else {
		MapRepresentation[frontier.front().GetXPosition()][frontier.front().GetYPosition()] = "discovered";
		State firstElementInFrontier = frontier.front();
		tempParentNodePointer = &firstElementInFrontier;
		if (UpNodeIsValid(frontier.front())) {
			AddNodeToList(frontier.front(), frontier, "up", "GBFS");
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		if (LeftNodeIsValid(frontier.front())) {
			AddNodeToList(frontier.front(), frontier, "left", "GBFS");
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		if (DownNodeIsValid(frontier.front())) {
			AddNodeToList(frontier.front(), frontier, "down", "GBFS");
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		if (RightNodeIsValid(frontier.front())) {
			AddNodeToList(frontier.front(), frontier, "right", "GBFS");
			numberOfNodes++;
			if (IsGoalState(frontier.back())) {
				cout << numberOfNodes << endl;
				PrintPath(frontier.back(), Path);
				return;
			}
		}
		frontier.pop_front();
		frontier.sort([&](State firstNode, State secondNode)
			{ return abs(chosenGoalState.first - firstNode.GetXPosition()) + abs(chosenGoalState.second - firstNode.GetYPosition()) <
			abs(chosenGoalState.first - secondNode.GetXPosition()) + abs(chosenGoalState.second - secondNode.GetYPosition()); });
		if (empty(frontier)) {
			cout << "No solution found.";
		}
		ExpandLeafNodesGBFS(frontier, Path, numberOfNodes);
	}
}

void MapStructure::ExpandLeafNodesDLS(std::stack<State*>& frontier, std::stack<std::string>& Path, int maxDepth, int& numberOfNodes) {
	if (IsGoalState((*frontier.top()))) {
		cout << "Initial position is goal state." << endl;
	}
	else {
		if ((*frontier.top()).GetDepth() < maxDepth) {
			if (UpNodeIsValid((*frontier.top()))) {
				AddNodePointerToStack((*frontier.top()), frontier, "up");
				frontier.top()->SetDepth(frontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*frontier.top()).GetXPosition()][(*frontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				if (IsGoalState((*frontier.top()))) {
					cout << numberOfNodes << endl;
					PrintPath((*frontier.top()), Path);
				}
				else {
					ExpandLeafNodesDLS(frontier, Path, maxDepth, numberOfNodes);
				}
			}
			else if (LeftNodeIsValid((*frontier.top()))) {
				AddNodePointerToStack((*frontier.top()), frontier, "left");
				frontier.top()->SetDepth(frontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*frontier.top()).GetXPosition()][(*frontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				if (IsGoalState((*frontier.top()))) {
					cout << numberOfNodes << endl;
					PrintPath((*frontier.top()), Path);
				}
				else {
					ExpandLeafNodesDLS(frontier, Path, maxDepth, numberOfNodes);
				}
			}
			else if (DownNodeIsValid((*frontier.top()))) {
				AddNodePointerToStack((*frontier.top()), frontier, "down");
				frontier.top()->SetDepth(frontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*frontier.top()).GetXPosition()][(*frontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				if (IsGoalState((*frontier.top()))) {
					cout << numberOfNodes << endl;
					PrintPath((*frontier.top()), Path);
				}
				else {
					ExpandLeafNodesDLS(frontier, Path, maxDepth, numberOfNodes);
				}
			}
			else if (RightNodeIsValid((*frontier.top()))) {
				AddNodePointerToStack((*frontier.top()), frontier, "right");
				frontier.top()->SetDepth(frontier.top()->parentNodePointer->GetDepth() + 1);
				MapRepresentation[(*frontier.top()).GetXPosition()][(*frontier.top()).GetYPosition()] = "discovered";
				numberOfNodes++;
				if (IsGoalState((*frontier.top()))) {
					cout << numberOfNodes << endl;
					PrintPath((*frontier.top()), Path);
				}
				else {
					ExpandLeafNodesDLS(frontier, Path, maxDepth, numberOfNodes);
				}
			}
			else {
				tempParentNodePointer = frontier.top()->parentNodePointer;
				frontier.pop();
				if (empty(frontier)) {
					cout << "No solution found.";
				} 
				else {
					ExpandLeafNodesDLS(frontier, Path, maxDepth, numberOfNodes);
				}
			}
		}
		else if ((*frontier.top()).GetDepth() == maxDepth) {
			if (IsGoalState((*frontier.top()))) {
				cout << numberOfNodes << endl;
				PrintPath((*frontier.top()), Path);
			}
			else {
				tempParentNodePointer = frontier.top()->parentNodePointer;
				frontier.pop();
				ExpandLeafNodesDLS(frontier, Path, maxDepth, numberOfNodes);
			}
		}
	}
}