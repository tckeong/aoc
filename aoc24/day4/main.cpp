#include <fstream>
#include <iostream>
#include <vector>

#define let const auto

using namespace std;

vector<string> getInput();
int countXMAS(const vector<string> &);
int getXMASCount(const vector<string> &, int, int);
int countX_MAS(const vector<string> &);
int isValidX_MAS(const vector<string> &, int, int);

int main() {
    const vector<string> input = getInput();
    const int count = countX_MAS(input);
    cout << "Count: " << count << endl;
    return 0;
}

vector<string> getInput() {
    ifstream file("../input.txt");
    string line;
    vector<string> result;

    while (getline(file, line)) {
        result.push_back(line);
    }

    return result;
}

int countXMAS(const vector<string> &input) {
    int count = 0;
    let row = input.size();
    let col = input[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (input[i][j] == 'X') {
                count += getXMASCount(input, i, j);
            }
        }
    }

    return count;
}

int getXMASCount(const vector<string> &input, int i, int j) {
    let row = input.size();
    let col = input[0].size();
    let word = string("XMAS");
    int count = 0;

    if (j + word.size() <= col) {
        bool found = true;

        for (int k = 0; k < word.size(); k++) {
            if (input[i][j + k] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    if (static_cast<int>(j - word.size() + 1) >= 0) {
        bool found = true;

        for (int k = 0; k < word.size(); k++) {
            if (input[i][j - k] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    if (i + word.size() <= row) {
        bool found = true;
        for (int k = 0; k < word.size(); k++) {
            if (input[i + k][j] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    if (static_cast<int>(i - word.size() + 1) >= 0) {
        bool found = true;
        for (int k = 0; k < word.size(); k++) {
            if (input[i - k][j] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    if (i + word.size() <= row && j + word.size() <= col) {
        bool found = true;
        for (int k = 0; k < word.size(); k++) {
            if (input[i + k][j + k] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    if (static_cast<int>(i - word.size() + 1) >= 0 && static_cast<int>(j - word.size() + 1) >= 0) {
        bool found = true;
        for (int k = 0; k < word.size(); k++) {
            if (input[i - k][j - k] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    if (i + word.size() <= row && static_cast<int>(j - word.size() + 1) >= 0) {
        bool found = true;
        for (int k = 0; k < word.size(); k++) {
            if (input[i + k][j - k] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    if (static_cast<int>(i - word.size() + 1) >= 0 && j + word.size() <= col) {
        bool found = true;
        for (int k = 0; k < word.size(); k++) {
            if (input[i - k][j + k] != word[k]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    return count;
}

int countX_MAS(const vector<string> &input) {
    int count = 0;
    let row = input.size();
    let col = input[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i + 2 < row && j + 2 < col) {
                if ((input[i][j] == 'M' || input[i + 2][j + 2] == 'M') &&
                    (input[i + 2][j] == 'M' || input[i][j + 2] == 'M')) {
                        count = isValidX_MAS(input, i, j) ? count + 1 : count;
                    }
            }
        }
    }

    return count;
}

int isValidX_MAS(const vector<string> &input, int i, int j) {
    if (input[i][j] == 'M') {
        if (!(input[i + 1][j + 1] == 'A' && input[i + 2][j + 2] == 'S')) {
            return 0;
        }
    }

    if (input[i + 2][j + 2] == 'M') {
        if (!(input[i + 1][j + 1] == 'A' && input[i][j] == 'S')) {
            return 0;
        }
    }

    if (input[i + 2][j] == 'M') {
        if (!(input[i + 1][j + 1] == 'A' && input[i][j + 2] == 'S')) {
            return 0;
        }
    }

    if (input[i][j + 2] == 'M') {
        if (!(input[i + 1][j + 1] == 'A' && input[i + 2][j] == 'S')) {
            return 0;
        }
    }

    return 1;
}

