#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

string getInput();
vector<string> getAllMatch(string, const regex&);
int getSum(const vector<string> &);
vector<int> getNum(const string &);
vector<string> getValidMatch(const vector<string> &);

int main() {
    const string input = getInput();
    vector<string> results = getAllMatch(input, regex(R"(mul\(-?\d+,-?\d+\)|do\(\)|don\'t\(\))"));
    results = getValidMatch(results);
    const int sum = getSum(results);

    cout << "Sum: " << sum << endl;

    return 0;
}

string getInput() {
    fstream file("../input.txt");
    string input;
    string line;

    while (file >> line) {
        input += line;
    }

    return input;
}

vector<string> getAllMatch(string input, const regex& pattern) {
    auto begin = sregex_iterator(input.begin(), input.end(), pattern);
    const auto end = sregex_iterator();
    vector<string> results;

    for (; begin != end; begin++) {
       results.push_back(begin->str());
    }

    return results;
}

int getSum(const vector<string> &results) {
    int sum = 0;

    for (const string &result : results) {
        const vector<int> nums = getNum(result);
        const int first = nums[0];
        const int second = nums[1];
        sum += first * second;
    }

    return sum;
}

vector<int> getNum(const string &line) {
    vector<int> nums;

    const int first = stoi(line.substr(4, line.find(',')));
    const int second = stoi(line.substr(line.find(',') + 1, line.size() - 1));

    nums.push_back(first);
    nums.push_back(second);

    return nums;
}

vector<string> getValidMatch(const vector<string> &results) {
    vector<string> valid;
    bool isDo = true;

    for (const string &line : results) {
        if (line == "do()") {
            isDo = true;
        } else if (line == "don't()") {
            isDo = false;
        } else if (isDo) {
            valid.push_back(line);
        }
    }

    return valid;
}
