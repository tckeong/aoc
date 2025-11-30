#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

using namespace std;

vector<vector<char>> getInput();
tuple<int, int, char> getCoordinateAndDirection(const vector<vector<char>> &);
int getTotalDistance(const tuple<int, int> &, char, vector<vector<char>> &);
int getUpDistance(int, int, vector<vector<char>> &, bool);
int getDownDistance(int, int, vector<vector<char>>&, bool);
int getLeftDistance(int, int, vector<vector<char>> &, bool);
int getRightDistance(int, int, vector<vector<char>> &, bool);
bool isTerminate(int, int, char, size_t, size_t);
char turnRight(char);
int countX(vector<vector<char>> &);
int getAllObstruction(const tuple<int, int> &, char, vector<vector<char>> &);
bool isRepeatObstruction(const tuple<int, int> &, char, vector<vector<char>> &);

int main() {
    vector<vector<char>> map = getInput();
    const tuple<int, int, char> coordinateAndDirection = getCoordinateAndDirection(map);
    const tuple<int, int> coordinate = make_tuple(get<0>(coordinateAndDirection), get<1>(coordinateAndDirection));
    const char direction = get<2>(coordinateAndDirection);

    cout << "All obstruction: " << getAllObstruction(coordinate, direction, map) << endl;

    const int totalDistance = getTotalDistance(coordinate, direction, map);

    cout << "Total distance: " << totalDistance << endl;

    return 0;
}

vector<vector<char>> getInput() {
    fstream file("../input.txt");
    string line;
    vector<vector<char>> results;

    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        results.push_back(row);
    }

    return results;
}

tuple<int, int, char> getCoordinateAndDirection(const vector<vector<char> > &map) {
    const auto n = map.size();
    const auto m = map[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char cell = map[i][j];
            if (cell == '^' || cell == 'v' || cell == '<' || cell == '>') {
                return make_tuple(i, j, cell);
            }
        }
    }

    return make_tuple(-1, -1, '?');
}

int getTotalDistance(const tuple<int, int> &coordinate, char direction, vector<vector<char> > &map) {
    const auto row = map.size();
    const auto col = map[0].size();
    int x = get<0>(coordinate);
    int y = get<1>(coordinate);
    int distance = 0;
    bool isFirst = true;

    while (!isTerminate(x, y, direction, row, col)) {
        if (isFirst) {
            isFirst = false;
        } else {
            direction = turnRight(direction);
        }

        switch (direction) {
            case '^':
                distance = getUpDistance(x, y, map, true);
                x -= distance;
                break;
            case '<':
                distance = getLeftDistance(x, y, map, true);
                y -= distance;
                break;
            case '>':
                distance = getRightDistance(x, y, map, true);
                y += distance;
                break;
            case 'v':
                distance = getDownDistance(x, y, map, true);
                x += distance;
                break;
            default:
                break;
        }
    }

    return countX(map);
}

char turnRight(const char direction) {
    switch (direction) {
        case '^':
            return '>';
        case '<':
            return '^';
        case '>':
            return 'v';
        case 'v':
            return '<';
        default:
            return '?';
    }
}


bool isTerminate(const int x, const int y, const char direction, const size_t row, const size_t col) {
    switch (direction) {
        case '^':
            return x == 0;
        case '<':
            return y == 0;
        case '>':
            return y == col - 1;
        case 'v':
            return x == row - 1;
        default:
            return false;
    }
}

int getUpDistance(int x, const int y, vector<vector<char> > &map, const bool isFill) {
    int distance = 0;
    while (x > 0 && map[x][y] != '#') {
        distance++;
        if (isFill) {
            map[x][y] = 'X';
        }
        x--;
    }

    if (map[x][y] == '#') {
        distance--;
    } else if (isFill) {
        map[x][y] = 'X';
    }

    return distance;
}

int getDownDistance(int x, const int y, vector<vector<char> >& map, const bool isFill) {
    int distance = 0;
    while (x < map.size() - 1 && map[x][y] != '#') {
        distance++;
        if (isFill) {
            map[x][y] = 'X';
        }
        x++;
    }

    if (map[x][y] == '#') {
        distance--;
    } else if (isFill) {
        map[x][y] = 'X';
    }

    return distance;
}

int getLeftDistance(const int x, int y, vector<vector<char> > &map, const bool isFill) {
    int distance = 0;
    while (y > 0 && map[x][y] != '#') {
        distance++;
        if (isFill) {
            map[x][y] = 'X';
        }
        y--;
    }

    if (map[x][y] == '#') {
        distance--;
    } else if (isFill) {
        map[x][y] = 'X';
    }

    return distance;
}

int getRightDistance(const int x, int y, vector<vector<char> > &map, const bool isFill) {
    int distance = 0;
    while (y < map[0].size() - 1 && map[x][y] != '#') {
        distance++;
        if (isFill) {
            map[x][y] = 'X';
        }
        y++;
    }

    if (map[x][y] == '#') {
        distance--;
    } else if (isFill) {
        map[x][y] = 'X';
    }

    return distance;
}

int countX(vector<vector<char> > &map) {
    int x = 0;

    for (auto &row : map) {
        for (const char &cell : row) {
            if (cell == 'X') {
                x++;
            }
        }
    }

    return x;
}

int getAllObstruction(const tuple<int, int> & coordinate,  const char direction, vector<vector<char> > & map) {
    int validObstruction = 0;
    const auto row = map.size();
    const auto col = map[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (map[i][j] == '.') {
                map[i][j] = '#';

                if (isRepeatObstruction(coordinate, direction, map)) {
                    validObstruction++;
                }

                map[i][j] = '.';
            }
        }
    }

    return validObstruction;
}

bool isRepeatObstruction(const tuple<int, int> &coordinate, char direction, vector<vector<char>> &map) {
    const auto row = map.size();
    const auto col = map[0].size();
    int x = get<0>(coordinate);
    int y = get<1>(coordinate);
    int totalDistance = 0;
    int distance = 0;
    bool isFirst = true;

    while (!isTerminate(x, y, direction, row, col)) {
        if (isFirst) {
            isFirst = false;
        } else {
            if (totalDistance > 10 * row * col) {
                return true;
            }

            direction = turnRight(direction);
        }

        switch (direction) {
            case '^':
                distance = getUpDistance(x, y, map, false);
                totalDistance += distance;
                x -= distance;
                break;
            case '<':
                distance = getLeftDistance(x, y, map, false);
                totalDistance += distance;
                y -= distance;
                break;
            case '>':
                distance = getRightDistance(x, y, map, false);
                totalDistance += distance;
                y += distance;
                break;
            case 'v':
                distance = getDownDistance(x, y, map, false);
                totalDistance += distance;
                x += distance;
                break;
            default:
                break;
        }
    }

    return false;
}
