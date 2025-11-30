#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int>> getInput();
bool isSafe(const vector<int> &);
bool isMonotonic(const vector<int> &);
bool isTolerateSafe(const vector<int> &);

int main() {
    vector<vector<int>> input = getInput();
    int count = 0;

    for (const vector<int> &row : input) {
        if (isSafe(row) || isTolerateSafe(row)) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}

vector<vector<int>> getInput() {
    ifstream file("../input.txt");
    vector<vector<int>> input;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> row;
        int num;

        while (iss >> num) {
            row.push_back(num);
        }

        input.push_back(row);
    }

    return input;
}

bool isSafe(const vector<int> &row) {
    int prev = row[0];

    for (int i = 1; i < row.size(); i++) {
        int diff = abs(row[i] - prev);

        if (diff >= 4 || diff == 0) {
            return false;
        }

        prev = row[i];
    }

    return isMonotonic(row);
}

bool isMonotonic(const vector<int> &row) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 1; i < row.size(); i++) {
        if (row[i] > row[i - 1]) {
            decreasing = false;
        } else if (row[i] < row[i - 1]) {
            increasing = false;
        }
    }

    return increasing || decreasing;
}

bool isTolerateSafe(const vector<int> &row) {
    for (int i = 0; i < row.size(); i++) {
        vector<int> sub = row;
        sub.erase(sub.begin() + i);

        if (isSafe(sub)) {
            return true;
        }
    }

    return false;
}