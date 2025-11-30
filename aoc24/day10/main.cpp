#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
vector<string> getInput();
int getAllScore(const vector<string>&);
int countAllDistinctTrailHeads(const vector<string>&, const pair<int, int> &);
int countAllTrailHeads(const vector<string> &, const pair<int, int> &);

int main() {
    const auto input = getInput();
    const auto result = getAllScore(input);

    cout << "Result: " << result << endl;

    return 0;
}

vector<string> getInput() {
    fstream file("../input.txt");
    vector<string> input;
    string line;

    while (getline(file, line)) {
        input.push_back(line);
    }

    return input;
}

int getAllScore(const vector<string>& input) {
    int score = 0;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '0') {
                score += countAllTrailHeads(input, {i, j});
            }
        }
    }

    return score;
}

int countAllDistinctTrailHeads(const vector<string> &map, const pair<int, int> &initCoordinate) {
    set<pair<int,int>> visited;
    queue<pair<int, int>> q;
    int trailHeads = 0;
    q.push(initCoordinate);
    visited.insert(initCoordinate);
    const auto n = map.size();
    const auto m = map[0].size();

    while (!q.empty()) {
        const auto current = q.front();
        q.pop();
        const auto x = current.first;
        const auto y = current.second;
        const auto currentChar = map[x][y];

        if (currentChar == '9') {
            trailHeads++;
        } else {
            if (x - 1 >= 0 && map[x - 1][y] == currentChar + 1 && visited.find({x - 1, y}) == visited.end()) {
                q.emplace(x - 1, y);
                visited.insert({x - 1, y});
            }

            if (x + 1 < n && map[x + 1][y] == currentChar + 1 && visited.find({x + 1, y}) == visited.end()) {
                q.emplace(x + 1, y);
                visited.insert({x + 1, y});
            }

            if (y - 1 >= 0 && map[x][y - 1] == currentChar + 1 && visited.find({x, y - 1}) == visited.end()) {
                q.emplace(x, y - 1);
                visited.insert({x, y - 1});
            }

            if (y + 1 < m && map[x][y + 1] == currentChar + 1 && visited.find({x, y + 1}) == visited.end()) {
                q.emplace(x, y + 1);
                visited.insert({x, y + 1});
            }
        }
    }

    return trailHeads;
}

int countAllTrailHeads(const vector<string> &map, const pair<int, int> &initCoordinate) {
    queue<pair<int, int>> q;
    int trailHeads = 0;
    q.push(initCoordinate);
    const auto n = map.size();
    const auto m = map[0].size();

    while (!q.empty()) {
        const auto current = q.front();
        q.pop();
        const auto x = current.first;
        const auto y = current.second;
        const auto currentChar = map[x][y];

        if (currentChar == '9') {
            trailHeads++;
        } else {
            if (x - 1 >= 0 && map[x - 1][y] == currentChar + 1) {
                q.emplace(x - 1, y);
            }

            if (x + 1 < n && map[x + 1][y] == currentChar + 1) {
                q.emplace(x + 1, y);
            }

            if (y - 1 >= 0 && map[x][y - 1] == currentChar + 1) {
                q.emplace(x, y - 1);
            }

            if (y + 1 < m && map[x][y + 1] == currentChar + 1) {
                q.emplace(x, y + 1);
            }
        }
    }

    return trailHeads;
}
