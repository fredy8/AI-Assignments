#include <bits/stdc++.h>
using namespace std;

class Position {
	public:
	int row, column;
	bool validPosition(int R, int C) {
		return row >= 0 && row < R && column >= 0 && column < C;
	}
	Position operator+(Position &other) {
		return Position{row + other.row, column + other.column};
	}
	double distanceTo(Position &other) {
		return sqrt(pow(row - other.row, 2) + pow(column - other.column, 2));
	}
	bool operator==(Position &other) {
		return row == other.row && column == other.column;
	}
};

class Node {
	public:
	Position position;
	double f;
	int d;
	bool operator<(const Node &b) const {
		return f > b.f;
	}
};

int main() {
	vector<string> grid;
	string line;
			while(cin >> line)
		grid.push_back(line);

	int R = grid.size(), C = grid[0].size();
	string movesOrder = "NESW";
	Position moves[4] = { Position{-1, 0}, Position{0, 1}, Position{1, 0}, Position{0, -1} };
	Position source{0, 0}, target{R-1, C-1};
	priority_queue<Node> pq;
#ifndef naive
	vector<vector<int> > dist(R, vector<int>(C, 1e9));
	dist[source.row][source.column] = 0;
#endif
	vector<string> direction(R, string(C, ' '));
	pq.push(Node{source, source.distanceTo(target), 0});
	int nodesExpanded = 0;
	while(!pq.empty()) {
		Position currentPosition = pq.top().position;
		double nodeF = pq.top().f;
		int nodeDist = pq.top().d;
		pq.pop();

#ifndef naive
		if (nodeDist != dist[currentPosition.row][currentPosition.column]) {
			continue;
		}
#endif

		if (nodesExpanded++ > 1e7) {
			cout << "Failure: too many nodes" << endl;
			return 0;
		}

		for(int i = 0; i < 4; i++) {
			Position neighbor = currentPosition + moves[i];
			if (neighbor.validPosition(R, C) && grid[neighbor.row][neighbor.column] == '0') {
#ifndef naive
				if (dist[neighbor.row][neighbor.column] > nodeDist + 1) {
					dist[neighbor.row][neighbor.column] = nodeDist + 1;
#endif
					direction[neighbor.row][neighbor.column] = movesOrder[i];
					pq.push(Node{neighbor, nodeDist + 1 + neighbor.distanceTo(target), nodeDist + 1});
#ifndef naive
				}
#endif
				if (neighbor == target) break;
			}
		}
	}

	if(direction[target.row][target.column] == '0') {
		cout << "Target unreachable." << endl;
		return 0;
	}

	cout << "Nodes Expanded: " << nodesExpanded << endl;

	stack<char> path;
	Position position = target;
	while(position.row != 0 || position.column != 0) {
		char dir = direction[position.row][position.column];
		path.push(dir);
		position = position + moves[(movesOrder.find(dir) + 2)%4];
	}

	cout << "Path: ";
	while(!path.empty()) {
		cout << path.top();
		path.pop();
	}
	cout << endl;
}
