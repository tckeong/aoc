#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;
vector<string> getInput();
vector<vector<pair<long long, long long>>> getMachines(const vector<string> &);
long long getTokens(const vector<vector<pair<long long, long long>>> &);

int main() {
    const vector<string> input = getInput();
    const vector<vector<pair<long long, long long>>> machines = getMachines(input);
    const long long result = getTokens(machines);

    cout << "Result: " << result << endl;

    return 0;
}

vector<string> getInput() {
    fstream file("../input.txt");
    string line;
    vector<string> result;

    while (getline(file, line)) {
        result.push_back(line);
    }

    return result;
}

vector<vector<pair<long long, long long>>> getMachines(const vector<string> & input) {
    vector<vector<pair<long long, long long>>> result;

    for (int i = 0; i < input.size(); i++) {
        vector<pair<long long, long long>> temp;

        for (int j = 0; j < 3; j++) {
            const string &line = input[i + j];
            regex regex("\\d+");
            auto it = std::sregex_iterator(line.begin(), line.end(), regex);

            int x = stoi(it->str());
            int y = stoi((++it)->str());

            temp.emplace_back(x, y);
        }

        i += 3;
        result.push_back(temp);
    }

    return result;
}

long long getTokens(const vector<vector<pair<long long, long long> > > & machines) {
    long long totalTokens = 0;
    const long long offset = 10000000000000;

    for (auto & machine : machines) {
        const pair<long long, long long> buttonA = machine[0];
        const pair<long long, long long> buttonB = machine[1];
        const pair<long long, long long> destXY = machine[2];

        const long long sumX = offset + destXY.first;
        const long long sumY = offset + destXY.second;


        const long long tokenB = (buttonA.first * sumY - sumX * buttonA.second) /
                                 (buttonA.first * buttonB.second - buttonB.first * buttonA.second);

        const long long tokenA = (sumX - tokenB * buttonB.first) / buttonA.first;

        if (tokenA * buttonA.first + tokenB * buttonB.first == sumX &&
            tokenA * buttonA.second + tokenB * buttonB.second == sumY) {
            totalTokens += tokenA * 3 + tokenB;
        }
    }

    return totalTokens;
}