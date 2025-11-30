#include <cmath>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class MapNode {
public:
    int x;
    int y;
    char direction;

    MapNode() : x(0), y(0), direction('l') {}

    MapNode(const int x, const int y, const char direction) : x(x), y(y), direction(direction) {}
};

struct MapNodeHash {
    size_t operator()(const MapNode& mapNode) const {
        const size_t h1 = hash<int>()(mapNode.x);
        const size_t h2 = hash<int>()(mapNode.y);
        const size_t h3 = hash<char>()(mapNode.direction);

        // Combine the hashes (example combining strategy)
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

// Equality operator for Node
bool operator==(const MapNode& a, const MapNode& b) {
    return a.x == b.x && a.y == b.y && a.direction == b.direction;
}

vector<string> getInput();
pair<int, int> getStart(const vector<string> &);
pair<int, int> getEnd(const vector<string> &);
void searchPath(const vector<string> &);
pair<int, vector<MapNode>> shortestPathSearch(const vector<string> &, const int &, const int &);
vector<string> drawMap(const vector<string> &, const vector<MapNode> &);
vector<vector<MapNode>> getAllMinCostPaths(const vector<string> &, const int &, const int &,
    const pair<int, vector<MapNode>> &);
vector<string> drawAllPaths(const vector<string> &, const vector<vector<MapNode>> &);
int countSit(const vector<string> &);

int main() {
    const vector<string> input = getInput();
    searchPath(input);

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

pair<int, int> getStart(const vector<string> & input) {
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == 'S') {
                return make_pair(i, j);
            }
        }
    }

    return make_pair(0, 0);
}

pair<int, int> getEnd(const vector<string> & input) {
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == 'E') {
                return make_pair(i, j);
            }
        }
    }

    return make_pair(0, 0);
}

void searchPath(const vector<string> & map) {
    const pair<int, int> start = getStart(map);
    const pair<int, vector<MapNode>> result1 = shortestPathSearch(map, start.first, start.second);
    const int minCost = result1.first;
    cout << "Min Cost: " << minCost << endl;

    const vector<vector<MapNode>> allMinCostPaths = getAllMinCostPaths(map, start.first, start.second, result1);
    cout << "Number of paths: " << allMinCostPaths.size() << endl;
    const vector<string> allPathsMap = drawAllPaths(map, allMinCostPaths);
    const int result2 = countSit(allPathsMap);

    for (const string & row : allPathsMap) {
        cout << row << endl;
    }

    cout << "Sit: " << result2 << endl;

}

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        const size_t h1 = hash<int>()(p.first);
        const size_t h2 = hash<int>()(p.second);

        // Combine the hashes (example combining strategy)
        return h1 ^ (h2 << 1);
    }
};

class Node {
public:
    int x;
    int y;
    int cost;
    vector<MapNode> path;
    char direction;

    Node() : x(0), y(0), cost(0), path({}), direction('l') {}

    Node (const int x, const int y, const int cost, const vector<MapNode> & path, const char direction)
        : x(x), y(y), cost(cost), path(path), direction(direction) {}
};

// Custom comparator for the priority queue
struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        // Higher cost means lower priority
        return a.cost > b.cost;
    }
};

pair<int, vector<MapNode>> shortestPathSearch(const vector<string> & map, const int & startX, const int & startY) {
    const auto n = map.size();
    const auto m = map[0].size();
    pair<int, vector<MapNode>> minResult = make_pair(0, vector<MapNode>());
    priority_queue<Node, vector<Node>, CompareNode> pq;
    pq.push(Node(startX, startY, 0, {}, 'r'));
    unordered_set<MapNode, MapNodeHash> visited;

    while (!pq.empty()) {
        const Node currentNode = pq.top();
        pq.pop();
        const int x = currentNode.x;
        const int y = currentNode.y;
        const int cost = currentNode.cost;
        vector<MapNode> path = currentNode.path;
        const char direction = currentNode.direction;

        if (map[x][y] == 'E') {
            minResult = make_pair(cost, path);
            break;
        }

        if (visited.find({x, y, direction}) != visited.end() ||
            map[x][y] == '#') {
            continue;
        }

        path.emplace_back(x, y, direction);
        visited.insert({x, y, direction});

        switch (direction) {
        case 'u':
            if (x - 1 >= 0) {
                pq.emplace(x - 1, y, cost + 1, path, 'u');
            }
            if (x + 1 < n) {
                pq.emplace(x + 1, y, cost + 2001, path, 'd');
            }
            if (y - 1 >= 0) {
                pq.emplace(x, y - 1, cost + 1001, path, 'l');
            }

            if (y + 1 < m) {
                pq.emplace(x, y + 1, cost + 1001, path, 'r');
            }
            break;
        case 'd':
            if (x - 1 >= 0) {
                pq.emplace(x - 1, y, cost + 2001, path, 'u');
            }
            if (x + 1 < n) {
                pq.emplace(x + 1, y, cost + 1, path, 'd');
            }
            if (y - 1 >= 0) {
                pq.emplace(x, y - 1, cost + 1001, path, 'l');
            }

            if (y + 1 < m) {
                pq.emplace(x, y + 1, cost + 1001, path, 'r');
            }
            break;
        case 'l':
            if (x - 1 >= 0) {
                pq.emplace(x - 1, y, cost + 1001, path,'u');
            }
            if (x + 1 < n) {
                pq.emplace(x + 1, y, cost + 1001, path, 'd');
            }
            if (y - 1 >= 0) {
                pq.emplace(x, y - 1, cost + 1, path, 'l');
            }

            if (y + 1 < m) {
                pq.emplace(x, y + 1, cost + 2001, path, 'r');
            }
            break;
        case 'r':
            if (x - 1 >= 0) {
                pq.emplace(x - 1, y, cost + 1001, path, 'u');
            }
            if (x + 1 < n) {
                pq.emplace(x + 1, y, cost + 1001, path, 'd');
            }
            if (y - 1 >= 0) {
                pq.emplace(x, y - 1, cost + 2001, path, 'l');
            }

            if (y + 1 < m) {
                pq.emplace(x, y + 1, cost + 1, path, 'r');
            }
            break;
        }
    }

    return minResult;
}

int countHeuristic(const vector<string> & map, const int & x, const int & y) {
    const pair<int, int> end = getEnd(map);
    return static_cast<int>(sqrt(pow(end.first - x, 2) + pow(end.second - y, 2)));
}

vector<string> drawMap(const vector<string> & map, const vector<MapNode> & path) {
    vector<string> moveMap = map;

    for (const MapNode & mapNode : path) {
        char direction = '>';

        if (mapNode.direction == 'u') {
            direction = '^';
        } else if (mapNode.direction == 'd') {
            direction = 'v';
        } else if (mapNode.direction == 'l') {
            direction = '<';
        } else if (mapNode.direction == 'r') {
            direction = '>';
        }

        moveMap[mapNode.x][mapNode.y] = direction;
    }

    return moveMap;
}

vector<vector<MapNode> > getAllMinCostPaths(const vector<string> & map,
    const int & startX, const int & startY, const pair<int, vector<MapNode>> & minResult) {
    vector<vector<MapNode>> result = {};
    const int minCost = minResult.first;
    const vector<MapNode> minPath = minResult.second;
    unordered_set<pair<int, int>, PairHash> existed = {};
    unordered_set<pair<int, int>, PairHash> used = {};
    queue<MapNode> q;

    for (const MapNode & p : minPath) {
        q.push(p);
        existed.insert({p.x, p.y});
    }

    while (!q.empty()) {
        cout << "Queue size: " << q.size() << endl;
        const MapNode currentNode = q.front();
        q.pop();
        const int x = currentNode.x;
        const int y = currentNode.y;

        if (used.find({x, y}) != used.end()) {
            continue;
        }

        used.insert({x, y});

        auto newMap = map;
        newMap[x][y] = '#';
        const pair<int, vector<MapNode>> tempMin = shortestPathSearch(newMap, startX, startY);

        if (tempMin.first == minCost) {
            result.push_back(tempMin.second);

            for (const MapNode & p : tempMin.second) {
                if (existed.find({p.x, p.y}) != existed.end()) {
                    continue;
                }

                q.push(p);
                existed.insert({p.x, p.y});
            }
        }
    }

    return result;
}

vector<string> drawAllPaths(const vector<string> & map, const vector<vector<MapNode>> & paths) {
    vector<string> moveMap = map;

    for (const vector<MapNode> & path : paths) {
        for (const MapNode & mapNode : path) {
            moveMap[mapNode.x][mapNode.y] = 'O';
        }
    }

    return moveMap;
}

int countSit(const vector<string> & map) {
    int result = 0;

    for (auto & row : map) {
        for (auto & cell : row) {
            if (cell == 'S' || cell == 'E' || cell == 'O') {
                result++;
            }
        }
    }

    return result;
}
