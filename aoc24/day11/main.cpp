#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <future>
#include <unordered_map>

using namespace std;
typedef unsigned long long ull;

string getInput();
vector<ull> getStones(const string &);
size_t blink(const vector<ull> &, int);
size_t digitCount(ull);
pair<ull,ull> splitStone(ull);

int main() {
    const string input = getInput();
    const vector<ull> stones = getStones(input);
    const auto result = blink(stones, 75);

    cout << "Result: " << result << endl;

    return 0;
}

string getInput() {
    fstream file("../input.txt");
    string input;
    string line;

    while (getline(file, line)) {
        input += line;
    }

    return input;
}

vector<ull> getStones(const string &input) {
    vector<ull> stones;
    stringstream ss(input);
    string stone;

    while(getline(ss, stone, ' ')) {
        stones.push_back(stoull(stone));
    }

    return stones;
}

struct PairHash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        const size_t h1 = hash<T1>()(p.first);
        const size_t h2 = hash<T2>()(p.second);
        return h1 ^ (h2 << 1); // Combine the two hashes
    }
};

unordered_map<pair<ull,int>, size_t, PairHash> cache;

size_t blink(const vector<ull> & stones, const int times) {
    if (times == 0) {
        return stones.size();
    }

    vector<vector<ull>> newStones;

    for (auto &stone : stones) {
        vector<ull> newStone;

        if (stone == 0) {
            newStone.push_back(1);
        } else if (digitCount(stone) % 2 == 0) {
            const auto [first, second] = splitStone(stone);
            newStone.push_back(first);
            newStone.push_back(second);
        } else {
            newStone.push_back(stone * 2024);
        }

        newStones.push_back(newStone);
    }

    size_t result = 0;

    for (int i = 0; i < newStones.size(); i++) {
        pair<ull, int> stone = pair<ull, int>(stones[i], times);

        if (cache.find(stone) != cache.end()) {
            result += cache[stone];
        } else {
            const size_t count = blink(newStones[i], times - 1);
            cache[stone] = count;
            result += count;
        }
    }

    return result;
}

size_t digitCount(const ull n) {
    return to_string(n).length();
}

pair<ull,ull> splitStone(const ull stone) {
    const auto digits = digitCount(stone);
    const auto half = digits / 2;
    const ull first = stone / static_cast<ull>(pow(10, half));
    const ull second = stone % static_cast<ull>(pow(10, half));

    return make_pair(first, second);
}
