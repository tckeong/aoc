#include <cmath>
#include <iostream>
#include <fstream>
#include <numeric>
#include <tuple>
#include <vector>
#include <sstream>

using namespace std;

vector<string> getInput();
vector<tuple<long long, vector<int>>> getEquations(const vector<string> &);
vector<long long> getValidEquations(const vector<tuple<long long, vector<int>>> &);
bool isValidEquation(long long, const vector<int> &, size_t, long long);
constexpr int getExp10(int);

int main() {
    const vector<string> input = getInput();
    const auto equations = getEquations(input);
    auto results = getValidEquations(equations);
    
    cout << "Results: " << accumulate(results.begin(), results.end(), static_cast<long long>(0)) << endl;

    return 0;
}

vector<string> getInput() {
    fstream file("../input.txt");
    string line;
    vector<string> results;

    while (getline(file, line)) {
        results.push_back(line);
    }

    return results;
}

vector<tuple<long long, vector<int>>> getEquations(const vector<string> &input) {
    vector<tuple<long long, vector<int>>> results;

    for (auto &s : input) {
        stringstream ss(s);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ':')) {
            tokens.push_back(token);
        }

        long long ans = stoll(tokens[0]);

        ss = stringstream(tokens[1]);
        vector<int> nums;

        while (getline(ss, token, ' ')) {
            if (!token.empty()) {
                nums.push_back(stoi(token));
            }
        }

        results.emplace_back(ans, nums);
    }

    return results;
}

vector<long long> getValidEquations(const vector<tuple<long long, vector<int> > > & equations) {
    vector<long long> results;

    for (auto &eq : equations) {
        const auto &ans = get<0>(eq);
        const auto &nums = get<1>(eq);

        if (isValidEquation(ans, nums, 0, 0)) {
            results.push_back(ans);
        }
    }

    return results;
}

bool isValidEquation(const long long ans, const vector<int> &nums, const size_t start, const long long sum) {
    if (start == nums.size() - 1) {
        return sum + nums[start] == ans || sum * nums[start] == ans || sum * getExp10(nums[start]) + nums[start] == ans;
    }

    return isValidEquation(ans, nums, start + 1, sum + nums[start]) ||
           isValidEquation(ans, nums, start + 1, sum * nums[start]) ||
           isValidEquation(ans, nums, start + 1, sum * getExp10(nums[start]) + nums[start]);
}

constexpr int getExp10(const int x) {
    if (x < 10) {
        return 10;
    }

    if (x < 100) {
        return 100;
    }

    if (x < 1000) {
        return 1000;
    }

    return 10000;
}
