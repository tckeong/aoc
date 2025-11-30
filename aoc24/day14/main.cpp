#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

vector<string> getInput();
vector<vector<int>> getPositionsAndVelocities(const vector<string> &);
vector<pair<int, int>> getFinalPositions(const vector<vector<int>> &, const int &, const int &, const int &);
pair<int, int> simulate(const vector<int> &, const int &, const int &, const int &);
int countRegions(const vector<pair<int, int>> &, const int &, const int &);
void drawPositions(const vector<pair<int, int>> &, const int &, const int &);

int main() {
    const vector<string> input = getInput();
    const vector<vector<int>>& positionsAndVelocities = getPositionsAndVelocities(input);

    constexpr auto width = 101;
    constexpr auto height = 103;
    constexpr int seconds = 100;

    const vector<pair<int, int>> finalPositions = getFinalPositions(positionsAndVelocities, seconds, width, height);

    const int result = countRegions(finalPositions, width, height);
    cout << "Result: " << result << endl;

    drawPositions(getFinalPositions(positionsAndVelocities, 7051, width, height), width, height);

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

vector<vector<int> > getPositionsAndVelocities(const vector<string> &input) {
    vector<vector<int>> result;

    for (const string & line : input) {
        vector<int> temp;

        regex pattern("(-?\\d+)");
        const auto matches_begin = sregex_iterator(line.begin(), line.end(), pattern);
        auto matches_end = sregex_iterator();

        for (auto it = matches_begin; it != matches_end; ++it) {
            temp.push_back(stoi(it->str()));
        }

        result.push_back(temp);
    }

    return result;
}

vector<pair<int, int>> getFinalPositions(const vector<vector<int>> &positionsAndVelocities, const int &seconds,
                                         const int &width, const int &height) {
    vector<pair<int, int>> result;

    result.reserve(positionsAndVelocities.size());

    for (const vector<int> &vec : positionsAndVelocities) {
        result.push_back(simulate(vec, seconds, width, height));
    }

    return result;
}

pair<int, int> simulate(const vector<int> &vec, const int &seconds, const int &width, const int &height) {
    const int x = vec[0];
    const int y = vec[1];
    const int vx = vec[2];
    const int vy = vec[3];

    if (seconds == 0) {
        return make_pair(x, y);
    }

    int newX = x + vx;
    int newY = y + vy;

    if (newX < 0) {
        newX = width + newX;
    } else if (newX >= width) {
        newX = newX % width;
    }

    if (newY < 0) {
        newY = height + newY;
    } else if (newY >= height) {
        newY = newY % height;
    }

    return simulate({newX, newY, vx, vy}, seconds - 1, width, height);
}

int countRegions(const vector<pair<int, int>> &finalPositions, const int &width, const int &height) {
    int firstQuadrant = 0;
    int secondQuadrant = 0;
    int thirdQuadrant = 0;
    int fourthQuadrant = 0;

    const int halfWidth = (width - 1) / 2;
    const int halfHeight = (height - 1) / 2;

    for (const pair<int, int> &pos : finalPositions) {
        const int x = pos.first;
        const int y = pos.second;

        if (x < halfWidth && y < halfHeight) {
            ++firstQuadrant;
        } else if (x > halfWidth && y < halfHeight) {
            ++secondQuadrant;
        } else if (x < halfWidth && y > halfHeight) {
            ++thirdQuadrant;
        } else if (x > halfWidth && y > halfHeight) {
            ++fourthQuadrant;
        }
    }

    return firstQuadrant * secondQuadrant * thirdQuadrant * fourthQuadrant;
}

void drawPositions(const vector<pair<int, int>> &positions, const int &width, const int &height) {
    vector<vector<char>> grid(height, vector<char>(width, '.'));

    for (const pair<int, int> &pos : positions) {
        grid[pos.second][pos.first] = '#';
        // if (grid[pos.second][pos.first] == '.') {
        //     grid[pos.second][pos.first] = '1';
        // } else {
        //     grid[pos.second][pos.first]++;
        // }
    }

    for (const vector<char> &vec : grid) {
        for (const char &c : vec) {
            cout << c;
        }

        cout << endl;
    }

    cout << endl;
}