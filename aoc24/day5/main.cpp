#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <set>
#include <unordered_map>

using namespace std;

vector<string> getInput();
vector<vector<int>> parseRules(vector<string>);
vector<vector<int>> parseUpdates(vector<string>, size_t);
unordered_map<int, set<int>> buildRuleMap(vector<vector<int>>);
vector<vector<int>> findValidUpdates(unordered_map<int, set<int>>, vector<vector<int>>);
vector<vector<int>> findInvalidUpdates(unordered_map<int, set<int>>, vector<vector<int>>);
vector<int> sortWithRuleMap(unordered_map<int, set<int>>, const vector<int>&);
int getSum(vector<vector<int>>);

int main() {
    const vector<string> input = getInput();
    const vector<vector<int>> rules = parseRules(input);
    vector<vector<int>> updates = parseUpdates(input, rules.size());
    const unordered_map<int, set<int>> ruleMap = buildRuleMap(rules);
    const vector<vector<int>> validUpdates = findValidUpdates(ruleMap, updates);
    const vector<vector<int>> invalidUpdates = findInvalidUpdates(ruleMap, updates);
    const int sum = getSum(invalidUpdates);

    cout << sum << endl;

    return 0;
}

vector<string> getInput() {
    fstream file("../input.txt");
    string line;
    vector<string> results;

    while(getline(file, line)) {
        results.push_back(line);
    }

    return results;
}

vector<vector<int>> parseRules(vector<string> input) {
    vector<vector<int>> results;
    const regex re("\\d+");

    for (auto & line : input) {
        if (line.empty()) {
            break;
        }

        vector<int> rule;

        const sregex_token_iterator begin(line.begin(), line.end(), re);
        const sregex_token_iterator end;

        for (auto it = begin; it != end; it++) {
            rule.push_back(stoi(*it));
        }

        results.push_back(rule);
    }

    return results;
}

vector<vector<int>> parseUpdates(vector<string> input, const size_t rulesSize) {
    vector<vector<int>> results;
    const regex re("\\d+");

    for (size_t i = rulesSize + 1; i < input.size(); i++) {
        vector<int> update;

        const sregex_token_iterator begin(input[i].begin(), input[i].end(), re);
        const sregex_token_iterator end;

        for (auto it = begin; it != end; it++) {
            update.push_back(stoi(*it));
        }

        results.push_back(update);
    }

    return results;
}

/*
 * Build a rules map
 * key is the number, and the value is the number that must before it
 */
unordered_map<int, set<int>> buildRuleMap(vector<vector<int>> rules) {
    unordered_map<int, set<int>> results;

    for (auto & rule : rules) {
        int key = rule[1];
        const int value = rule[0];

        if (results.find(key) == results.end()) {
            results[key] = set<int>();
        }

        results[key].insert(value);
    }

    return results;
}

vector<vector<int>> findValidUpdates(unordered_map<int, set<int>> ruleMap, vector<vector<int>> updates) {
    vector<vector<int>> results;

    for (auto & update : updates) {
        bool isValid = true;

        for (int i = 0; i < update.size(); i++) {
            if (!isValid) {
                break;
            }

            if (ruleMap.find(update[i]) != ruleMap.end()) {
                set<int> current = ruleMap[update[i]];

                for (int j = i + 1; j < update.size(); j++) {
                    if (current.find(update[j]) != current.end()) {
                        isValid = false;
                        break;
                    }
                }
            }
        }

        if (isValid) {
            results.push_back(update);
        }
    }

    return results;
}

vector<vector<int>> findInvalidUpdates(unordered_map<int, set<int>> ruleMap, vector<vector<int>> updates) {
    vector<vector<int>> results;

    for (auto & update : updates) {
        bool isValid = true;

        for (int i = 0; i < update.size(); i++) {
            if (!isValid) {
                break;
            }

            if (ruleMap.find(update[i]) != ruleMap.end()) {
                set<int> current = ruleMap[update[i]];

                for (int j = i + 1; j < update.size(); j++) {
                    if (current.find(update[j]) != current.end()) {
                        isValid = false;
                        break;
                    }
                }
            }
        }

        if (!isValid) {
            update = sortWithRuleMap(ruleMap, update);
            results.push_back(update);
        }
    }

    return results;
}

int getSum(vector<vector<int>> updates) {
    int sum = 0;

    for (auto & update : updates) {
        const auto n = update.size();
        const int mid = update[n / 2];

        sum += mid;
    }

    return sum;
}

vector<int> sortWithRuleMap(unordered_map<int, set<int>> ruleMap, const vector<int>& update) {
    vector<int> results;
    const auto n =  update.size();
    set<int> used;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int current = update[j];

            if (used.find(j) != used.end()) {
                continue;
            }

            set<int> currentSet = ruleMap[current];
            bool isValid = true;

            for (int k = 0; k < n; k++) {
                if (used.find(k) != used.end()) {
                    continue;
                }

                if (currentSet.find(update[k]) != currentSet.end()) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                results.push_back(current);
                used.insert(j);
                break;
            }
        }
    }

    return results;
}