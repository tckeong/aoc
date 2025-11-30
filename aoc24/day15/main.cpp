#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;
vector<string> getInput();
vector<string> getMap(const vector<string> &);
vector<string> getMovements(const vector<string> &);
vector<string> move(vector<string>, const vector<string> &);
pair<int, int> getInitialPosition(const vector<string> &);
pair<int, int> getDirection(const char &);
bool canMoveTo(const vector<string> &, int, int, const pair<int, int> &);
pair<int, int> getBound(const vector<string> &, int, int, const pair<int ,int> &);
void moveBox(vector<string> &, int, int, const pair<int, int> &);
long long countDistances(const vector<string> &);

vector<string> getNewMap(const vector<string> &);
vector<string> newMove(vector<string>, const vector<string> &);
bool newCanMoveTo(const vector<string> &, int, int, const pair<int, int> &);
vector<vector<int>> newGetBoxes(const vector<string> &, int, int, const pair<int ,int> &);
void newMoveBox(vector<string> &, int, int, const pair<int, int> &);
long long newCountDistances(const vector<string> &);
bool isLeftBox(const char &);

int main() {
    const vector<string> input = getInput();
    const vector<string> map = getMap(input);
    const vector<string> moves = getMovements(input);
    const vector<string> movedMap = move(map, moves);
    const long long distances = countDistances(movedMap);

    cout << "Part 1: " << distances << endl;

    vector<string> newMap = getNewMap(map);

    vector<string> newMovedMap = newMove(newMap, moves);
    const long long newDistances = newCountDistances(newMovedMap);

    cout << "Part 2: " << newDistances << endl;

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

vector<string> getMap(const vector<string> &input) {
    const auto it = find_if(input.begin(), input.end(), [](const string &line) {
        return line.empty();
    });

    return vector<string>(input.begin(), it);
}

vector<string> getMovements(const vector<string> &input) {
    const auto it = find_if(input.begin(), input.end(), [](const string &line) {
        return line.empty();
    });

    return vector<string>(it + 1, input.end());
}

vector<string> move(vector<string> map, const vector<string> &movements) {
    const pair<int, int> position = getInitialPosition(map);
    int x = position.first;
    int y = position.second;

    for (const string & s : movements) {
        for (const char & c : s) {
            const pair<int, int> direction = getDirection(c);
            if (canMoveTo(map, x + direction.first, y + direction.second, direction)) {
                moveBox(map, x + direction.first, y + direction.second, direction);
                map[x][y] = '.';
                x += direction.first;
                y += direction.second;
                map[x][y] = '@';
            }
        }
    }

    return map;
}

pair<int, int> getInitialPosition(const vector<string> & map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '@') {
                return make_pair(i, j);
            }
        }
    }

    return make_pair(0, 0);
}


pair<int, int> getDirection(const char &movement) {
    switch (movement) {
        case '^':
            return make_pair(-1, 0);
        case 'v':
            return make_pair(1, 0);
        case '>':
            return make_pair(0, 1);
        case '<':
            return make_pair(0, -1);
        default:
            return make_pair(0, 0);
    }
}

bool canMoveTo(const vector<string> &map, int x, int y, const pair<int, int> & direction) {
    if (map[x][y] == '.') {
        return true;
    }

    const pair<int, int> bound = getBound(map, x, y, direction);

    return map[bound.first][bound.second] == '.';
}

pair<int, int> getBound(const vector<string> &map, int x, int y, const pair<int, int> &direction) {
    while (map[x][y] == 'O') {
        x += direction.first;
        y += direction.second;
    }

    return make_pair(x, y);
}

void moveBox(vector<string> &map, int x, int y, const pair<int, int> &direction) {
    const pair<int, int> bound = getBound(map, x, y, direction);

    while (x != bound.first || y != bound.second) {
        x += direction.first;
        y += direction.second;
        map[x][y] = 'O';
    }
}

long long countDistances(const vector<string> &map) {
    long long distances = 0;

   for (int i = 0; i < map.size(); i++) {
       for (int j = 0; j < map[i].size(); j++) {
           if (map[i][j] == 'O') {
               distances += i * 100 + j;
           }
       }
   }

    return distances;
}

vector<string> getNewMap(const vector<string> &map) {
    vector<string> newMap;

    for (auto & s : map) {
        string line;
        for (const char & c : s) {
            switch (c) {
            case '#':
                line += "##";
                break;
            case 'O':
                line += "[]";
                break;
            case '@':
                line += "@.";
                break;
            default:
                line += "..";
            }
        }
        newMap.push_back(line);
    }

    return newMap;
}

vector<string> newMove(vector<string> map, const vector<string> &movements) {
    const pair<int, int> position = getInitialPosition(map);
    int x = position.first;
    int y = position.second;

    int i = 0;

    for (const string & s : movements) {
        for (const char & c : s) {
            i++;
            const pair<int, int> direction = getDirection(c);

            if (map[x + direction.first][y + direction.second] == '#') {
                continue;
            }

            if (newCanMoveTo(map, x + direction.first, y + direction.second, direction)) {
                if (map[x + direction.first][y + direction.second] != '.') {
                    newMoveBox(map, x + direction.first, y + direction.second, direction);
                }

                map[x][y] = '.';
                x += direction.first;
                y += direction.second;
                map[x][y] = '@';
            }
        }
    }

    return map;
}

bool newCanMoveTo(const vector<string> &map, const int x, const int y, const pair<int, int> & direction) {
    if (map[x][y] == '.') {
        return true;
    }

    if (map[x][y] == '#') {
        return false;
    }

    int xLeft = x;
    int yLeft = y;
    int xRight = x;
    int yRight = y;

    if (isLeftBox(map[x][y])) {
        yRight++;
    } else {
        yLeft--;
    }

    queue<vector<int>> q;
    q.push({xLeft, yLeft, xRight, yRight});
    const bool isHorizontal = direction.first == 0;

    while (!q.empty()) {
        const vector<int> current_box = q.front();
        q.pop();

        xLeft = current_box[0];
        yLeft = current_box[1];
        xRight = current_box[2];
        yRight = current_box[3];

        if (map[xLeft][yLeft] == '#' || map[xRight][yRight] == '#') {
            return false;
        }

        if (isHorizontal) {
            const int nextXLeft = xLeft + direction.first;
            const int nextYLeft = yLeft + 2 * direction.second;
            const int nextXRight = xRight + direction.first;
            const int nextYRight = yRight + 2 * direction.second;

            if (direction.second < 0 && map[nextXRight][nextYRight] != '.') {
                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }

            if (direction.second > 0 && map[nextXLeft][nextYLeft] != '.') {
                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }
        } else {
            xLeft += direction.first;
            yLeft += 2 * direction.second;
            xRight += direction.first;
            yRight += 2 * direction.second;

            if (map[xLeft][yLeft] != '.') {
                int nextXLeft = xLeft;
                int nextYLeft = yLeft;
                int nextXRight = xLeft;
                int nextYRight = yLeft;

                if (isLeftBox(map[xLeft][yLeft])) {
                    nextYRight++;
                } else {
                    nextYLeft--;
                }

                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }

            if (map[xRight][yRight] != '.' && map[xRight][yRight] != ']') {
                int nextXLeft = xRight;
                int nextYLeft = yRight;
                int nextXRight = xRight;
                int nextYRight = yRight;

                if (isLeftBox(map[xRight][yRight])) {
                    nextYRight++;
                } else {
                    nextYLeft--;
                }

                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }

        }
    }

    return true;
}

void newMoveBox(vector<string> &map, const int x, const int y, const pair<int, int> &direction) {
    vector<vector<int>> boxes = newGetBoxes(map, x, y, direction);
    boxes = vector<vector<int>>(boxes.rbegin(), boxes.rend());

    for (const vector<int> & box : boxes) {
        int xLeft = box[0];
        int yLeft = box[1];
        int xRight = box[2];
        int yRight = box[3];

        map[xLeft][yLeft] = '.';
        map[xRight][yRight] = '.';
        xLeft += direction.first;
        yLeft += direction.second;
        xRight += direction.first;
        yRight += direction.second;
        map[xLeft][yLeft] = '[';
        map[xRight][yRight] = ']';
    }
}

vector<vector<int>> newGetBoxes(const vector<string> &map, const int x, const int y, const pair<int, int> &direction) {
    int xLeft = x;
    int yLeft = y;
    int xRight = x;
    int yRight = y;

    if (isLeftBox(map[x][y])) {
        yRight++;
    } else {
        yLeft--;
    }

    vector<vector<int>> boxes;
    queue<vector<int>> q;
    const bool isHorizontal = direction.first == 0;
    q.push({xLeft, yLeft, xRight, yRight});

    while (!q.empty()) {
        const vector<int> current_box = q.front();
        q.pop();
        boxes.push_back(current_box);

        xLeft = current_box[0];
        yLeft = current_box[1];
        xRight = current_box[2];
        yRight = current_box[3];


        if (isHorizontal) {
            const int nextXLeft = xLeft + direction.first;
            const int nextYLeft = yLeft + 2 * direction.second;
            const int nextXRight = xRight + direction.first;
            const int nextYRight = yRight + 2 * direction.second;

            if (direction.second < 0 && map[nextXRight][nextYRight] != '.') {
                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }

            if (direction.second > 0 && map[nextXLeft][nextYLeft] != '.') {
                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }
        } else {
            xLeft += direction.first;
            yLeft += 2 * direction.second;
            xRight += direction.first;
            yRight += 2 * direction.second;

            if (map[xLeft][yLeft] != '.') {
                int nextXLeft = xLeft;
                int nextYLeft = yLeft;
                int nextXRight = xLeft;
                int nextYRight = yLeft;

                if (isLeftBox(map[xLeft][yLeft])) {
                    nextYRight++;
                } else {
                    nextYLeft--;
                }

                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }

            if (map[xRight][yRight] != '.' && map[xRight][yRight] != ']') {
                int nextXLeft = xRight;
                int nextYLeft = yRight;
                int nextXRight = xRight;
                int nextYRight = yRight;

                if (isLeftBox(map[xRight][yRight])) {
                    nextYRight++;
                } else {
                    nextYLeft--;
                }

                q.push({nextXLeft, nextYLeft, nextXRight, nextYRight});
            }

        }
    }

    return boxes;
}

bool isLeftBox(const char &c) {
    return c == '[';
}

long long newCountDistances(const vector<string> &map) {
    long long distances = 0;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '[') {
                distances += i * 100 + j;
            }
        }
    }

    return distances;
}