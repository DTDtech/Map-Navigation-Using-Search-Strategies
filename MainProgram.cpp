#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <utility>
#include <map>
#include "MapStructure.h"
#include "State.h"
using namespace std;

int main(int argc, char** argv) {
	
	if (argc != 3) {
		cout << "Please supply two arguments to this program.";
		return -1;
	}

	//Get rows, columns, and positions using regex
	string fileName = argv[1];
	ifstream MapSpecifications(fileName);
	if (MapSpecifications.is_open()) {	

		string line;
		int lineCounter = 1;
		smatch regexFilterResult;
		regex mapPositionPattern("([0-9]+)(,)([0-9]+)");
		regex wallPositionPattern("([0-9]+)(,)([0-9]+)(,)([0-9]+)(,)([0-9]+)");

		pair <int, int> RowsAndColumns;
		pair <int, int> InitialPosition;
		vector <std::pair<int, int>> GoalstatePositions;
		map<std::pair<int, int>, std::pair<int, int>> WallPositions;

		string algorithmName;

		//Get number of rows and columns, and create a map
		while (getline(MapSpecifications, line)) {
			if (lineCounter == 1) {
				while (regex_search(line, regexFilterResult, mapPositionPattern)) {
					int rows = stoi(regexFilterResult[1]);
					int columns = stoi(regexFilterResult[3]);
					//cout << regexFilterResult[1] << regexFilterResult[3] << endl;
					RowsAndColumns = make_pair(rows, columns);
					//auto Map = std::vector<std::vector<int>>(rows, std::vector<int>(columns));
					line = regexFilterResult.suffix();
					lineCounter++;
				}
			}
			//Get initial position
			else if (lineCounter == 2) {
				while (regex_search(line, regexFilterResult, mapPositionPattern)) {
					int initialpos_X = stoi(regexFilterResult[1]);
					int initialpos_Y = stoi(regexFilterResult[3]);
					InitialPosition = make_pair(initialpos_X, initialpos_Y);
					//cout << regexFilterResult[1] << regexFilterResult[3] << endl;
					line = regexFilterResult.suffix();
					lineCounter++;
				}
			}
			//Get goal state position
			else if (lineCounter == 3) {
				while (regex_search(line, regexFilterResult, mapPositionPattern)) {
					int goalstate_X = stoi(regexFilterResult[1]);
					int goalstate_Y = stoi(regexFilterResult[3]);
					GoalstatePositions.push_back(make_pair(goalstate_X, goalstate_Y));
					//cout << regexFilterResult[1] << regexFilterResult[3] << endl;
					line = regexFilterResult.suffix();
					lineCounter++;
				}
			}
			else {
				while (regex_search(line, regexFilterResult, wallPositionPattern)) {
					int wall_X = stoi(regexFilterResult[1]);
					int wall_Y = stoi(regexFilterResult[3]);
					int wall_Width = stoi(regexFilterResult[5]);
					int wall_Height = stoi(regexFilterResult[7]);
					WallPositions.insert({ make_pair(wall_X, wall_Y), make_pair(wall_Width, wall_Height) });
					//cout << wall_X << wall_Y << wall_Width << wall_Height << endl;
					line = regexFilterResult.suffix();
					lineCounter++;
				}
			}

		}

		MapStructure RobotNavigation(RowsAndColumns, InitialPosition, GoalstatePositions, WallPositions);
		RobotNavigation.CreateMapRepresentation();
		cout << argv[1] << " " << argv[2] << " ";
		RobotNavigation.ExpandFromRootNode(argv[2]);
	}
	MapSpecifications.close();
	return 0;
}

