#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<string> getInput();
vector<pair<int, int>> getPlantsPosition(const vector<string> &);
int countTotalPrices(const vector<string> &, const vector<pair<int, int>> &);
int countPlant(vector<string> &, const pair<int, int> &);
int countFence(vector<string> &, const pair<int, int> &);
int countSide(vector<string> &, const pair<int, int> &);
void markPlants(vector<string> &, const pair<int, int> &);
void markSpaces(vector<string> &, int, int);
int countSpaces(const vector<string> &, int, int);
int countAngles(const vector<string> &);

int main() {
    const vector<string> input = getInput();
    const vector<pair<int, int>> plantsPosition = getPlantsPosition(input);
    const int result = countTotalPrices(input, plantsPosition);

    cout << "Result: " << result << endl;

    return 0;
}

vector<string> getInput() {
    vector<string> input;
    fstream file("../input.txt");
    string line;

    while (getline(file, line)) {
        input.push_back(line);
    }

    return input;
}

vector<pair<int, int>> getPlantsPosition(const vector<string> &input) {
    vector<pair<int, int>> plantsPosition;
    vector<string> plantsMap = input;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
           if (plantsMap[i][j] != '.') {
                markPlants(plantsMap, {i, j});
                plantsPosition.emplace_back(i, j);
           }
        }
    }

    return plantsPosition;
}

void markPlants(vector<string> & map, const pair<int, int> & coordinate) {
    const int x = coordinate.first;
    const int y = coordinate.second;
    const char plant = map[x][y];

    map[x][y] = '.';

    if (x - 1 >= 0 && map[x - 1][y] == plant) {
        markPlants(map, {x - 1, y});
    }

    if (x + 1 < map.size() && map[x + 1][y] == plant) {
        markPlants(map, {x + 1, y});
    }

    if (y - 1 >= 0 && map[x][y - 1] == plant) {
        markPlants(map, {x, y - 1});
    }

    if (y + 1 < map[x].size() && map[x][y + 1] == plant) {
        markPlants(map, {x, y + 1});
    }
}

int countTotalPrices(const vector<string> &input, const vector<pair<int, int>> &plantsPosition) {
    int result = 0;

    for (auto & p : plantsPosition) {
        vector<string> map1 = input;
        vector<string> map2 = input;
        vector<string> map3 = input;

        const int plantCount = countPlant(map1, p);
        const int fenceCount = countFence(map2, p);
        const int sideCount = countSide(map3, p);

        result += plantCount * sideCount;
    }

    return result;
}

int countPlant(vector<string>& map, const pair<int, int> & position) {
    const int x = position.first;
    const int y = position.second;
    const char plant = map[x][y];

    int result = 0;

    map[x][y] = '.';

    if (x - 1 >= 0 && map[x - 1][y] == plant) {
        result += countPlant(map, {x - 1, y});
    }

    if (x + 1 < map.size() && map[x + 1][y] == plant) {
        result += countPlant(map, {x + 1, y});
    }

    if (y - 1 >= 0 && map[x][y - 1] == plant) {
        result += countPlant(map, {x, y - 1});
    }

    if (y + 1 < map[x].size() && map[x][y + 1] == plant) {
        result += countPlant(map, {x, y + 1});
    }

    return result + 1;
}

int countFence(vector<string>& map, const pair<int, int> & position) {
    const int x = position.first;
    const int y = position.second;
    const char plant = map[x][y];
    int result = 4;

    map[x][y] = '.';

    if (x - 1 >= 0 && map[x - 1][y] == '.') {
        result -= 2;
    }

    if (x + 1 < map.size() && map[x + 1][y] == '.') {
        result -= 2;
    }

    if (y - 1 >= 0 && map[x][y - 1] == '.') {
        result -= 2;
    }

    if (y + 1 < map[x].size() && map[x][y + 1] == '.') {
        result -= 2;
    }

    if (x - 1 >= 0 && map[x - 1][y] == plant) {
        result += countFence(map, {x - 1, y});
    }

    if (x + 1 < map.size() && map[x + 1][y] == plant) {
        result += countFence(map, {x + 1, y});
    }

    if (y - 1 >= 0 && map[x][y - 1] == plant) {
        result += countFence(map, {x, y - 1});
    }

    if (y + 1 < map[x].size() && map[x][y + 1] == plant) {
        result += countFence(map, {x, y + 1});
    }

    return result;
}

int countSide(vector<string> & map, const pair<int, int> & position) {
    markPlants(map, position);

    return countAngles(map);
}

struct PairHash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        const size_t h1 = hash<T1>()(p.first);  // Hash the first element
        const size_t h2 = hash<T2>()(p.second); // Hash the second element
        return h1 ^ (h2 << 1); // Combine the two hashes
    }
};

int countAngles(const vector<string> & map) {
    int result = 0;
    unordered_map<pair<int, int>, int, PairHash> angles;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '.') {
                angles[{i, j}]++;
                angles[{i, j + 1}]++;
                angles[{i + 1, j}]++;
                angles[{i + 1, j + 1}]++;
            }

            // special cases
            if (i + 1 < map.size() && j + 1 < map[i].size() && j + 1 < map[i + 1].size() &&
                map[i][j] == '.' && map[i + 1][j + 1] == '.' &&
                map[i + 1][j] != '.' && map[i][j + 1] != '.') {
                result += 2;
            }

            if (i - 1 >= 0 && j + 1 < map[i - 1].size() && j + 1 < map[i].size() &&
                map[i][j] == '.' && map[i - 1][j + 1] == '.' &&
                map[i - 1][j] != '.' && map[i][j + 1] != '.') {
                result += 2;
            }
        }
    }

    for (auto & a : angles) {
        if (a.second % 2 == 1) {
            result++;
        }
    }

    return result;
}
