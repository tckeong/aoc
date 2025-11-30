#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;
vector<vector<int>> getInput();
int getDistances(const vector<int> &, const vector<int> &);
int getSimilarity(const vector<int> &, const vector<int> &);

int main() {
    const auto input = getInput();
    vector<int> firstList = input[0];
    vector<int> secondList = input[1];

    sort(firstList.begin(), firstList.end());
    sort(secondList.begin(), secondList.end());

    const int distance = getDistances(firstList, secondList);
    cout << "Distance: " << distance << endl;

    const int similarity = getSimilarity(firstList, secondList);
    cout << "Similarity: " << similarity << endl;

    return 0;
}

vector<vector<int>> getInput() {
    ifstream file("../input.txt");
    vector<vector<int>> input = {{}, {}};

    string line;

    while (getline(file, line)) {
        istringstream lineStream(line);
        string number;
        lineStream >> number;
        input[0].push_back(stoi(number));
        lineStream >> number;
        input[1].push_back(stoi(number));
    }

    return input;
}

int getDistances(const vector<int> &firstList, const vector<int> &secondList) {
    const auto n = firstList.size();
    int distances = 0;

    for (int i = 0; i < n; i++) {
        const int &first = firstList[i];
        const int &second = secondList[i];
        int distance = abs(first - second);
        distances += distance;
    }

    return distances;
}

int getSimilarity(const vector<int> &firstList, const vector<int> &secondList) {
    int score = 0;
    unordered_map<int, int> secondMap;

    for (const int &i : secondList) {
        secondMap[i]++;
    }

    for (const int &i : firstList) {
        if (secondMap.find(i) != secondMap.end()) {
            score += i * secondMap[i];
        }
    }

    return score;
}
