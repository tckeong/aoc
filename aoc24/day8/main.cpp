#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

vector<string> getInput();
unordered_map<char, vector<pair<int,int>>> getAntennasCoordinates(vector<string>);
int getAllPosition(vector<string> &,const unordered_map<char, vector<pair<int,int>>>&);
vector<pair<int, int>> getAntinodes(const pair<int, int> &, const pair<int, int> &);
vector<pair<int, int>> getGridAntiNodes(const pair<int, int> &, const pair<int, int> &, int, int);
int countAntennas(const vector<string> &);

int main() {
    const vector<string> input = getInput();
    const auto antennasCoordinates = getAntennasCoordinates(input);
    auto map = input;
    const int result = getAllPosition(map, antennasCoordinates);

    for (const auto &line : map) {
        cout << line << endl;
    }

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

unordered_map<char, vector<pair<int, int> > > getAntennasCoordinates(vector<string> input) {
    unordered_map<char, vector<pair<int, int>>> results;
    const auto n = input.size();
    const auto m = input[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = input[i][j];

            if (c != '.') {
                results[c].emplace_back(i, j);
            }
        }
    }

    return results;
}

int getAllPosition(vector<string> &map, const unordered_map<char, vector<pair<int, int> > >& antennasCoordinates) {
    const auto n = map.size();
    const auto m = map[0].size();

    for (const auto &p : antennasCoordinates) {
        const auto antennas = p.second;

        int count = 0;

        for (int i = 0; i < antennas.size(); i++) {
            for (int j = i + 1; j < antennas.size(); j++) {
                count++;
                vector<pair<int, int>> antiNodesCoordinate = getAntinodes(antennas[i], antennas[j]);
                vector<pair<int, int>> gridAntiNodesCoordinate = getGridAntiNodes(antennas[i], antennas[j], n, m);

                for (const auto &antiNode : gridAntiNodesCoordinate) {
                    const int x = antiNode.first;
                    const int y = antiNode.second;

                    if (x >= 0 && x < n && y >= 0 && y < m) {
                        map[x][y] = '#';
                    }
                }
            }
        }
    }

    return countAntennas(map);
}

int countAntennas(const vector<string> &map) {
    int result  = 0;

    for (const auto &line : map) {
        for (const auto &c : line) {
            if (c == '#') {
                result++;
            }
        }
    }

    return result;
}

vector<pair<int, int> > getAntinodes(const pair<int, int> &antenna1, const pair<int, int> &antenna2) {
    vector<pair<int, int>> results;
    const int distanceX = antenna1.first - antenna2.first;
    const int distanceY = antenna1.second - antenna2.second;

    results.emplace_back(antenna1.first + distanceX, antenna1.second + distanceY);
    results.emplace_back(antenna2.first - distanceX, antenna2.second - distanceY);

    return results;
}

vector<pair<int, int> > getGridAntiNodes(const pair<int, int> &antenna1, const pair<int, int> &antenna2, const int n, const int m) {
    vector<pair<int, int>> results;
    const int distanceX = antenna1.first - antenna2.first;
    const int distanceY = antenna1.second - antenna2.second;

    for (int i = 0; i < n; i++) {
        results.emplace_back(antenna1.first + i *distanceX, antenna1.second + i * distanceY);
        results.emplace_back(antenna2.first - i * distanceX, antenna2.second - i * distanceY);
    }

    if (abs(distanceX) == abs(distanceY)) {
        if ((distanceX > 0 && distanceY > 0) || (distanceX < 0 && distanceY < 0)) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i - j == antenna1.first - antenna1.second) {
                        results.emplace_back(i, j);
                    }
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i + j == antenna1.first + antenna1.second) {
                        results.emplace_back(i, j);
                    }
                }
            }
        }
    }

    return results;
}

