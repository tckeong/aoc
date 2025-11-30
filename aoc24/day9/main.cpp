#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

using namespace std;
string getInput();
vector<pair<int,int>> getIds(const string &);
vector<int> getSpaces(const string &);
long long moveWholeFiles(vector<pair<int,int>> &, const vector<int> &);
long long movePartialFiles(vector<pair<int,int>> &, const vector<int> &);
long long countChecksum(const vector<int> &);

int main() {
    const string input = getInput();
    vector<pair<int,int>> ids = getIds(input);
    const vector<int> spaces = getSpaces(input);

    const long long checksum = movePartialFiles(ids, spaces);

    cout << "Checksum: " << checksum << endl;

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

vector<pair<int,int>> getIds(const string &input) {
    vector<pair<int, int>> results;
    const auto n = input.size();

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            results.emplace_back(i / 2, input[i] - '0');
        }
    }

    return results;
}

vector<int> getSpaces(const string &input) {
    vector<int> results;
    const auto n = input.size();

    for (int i = 0; i < n; i++) {
        if (i % 2 == 1) {
            results.push_back(input[i] - '0');
        }
    }

    return results;
}

long long moveWholeFiles(vector<pair<int,int>> &ids, const vector<int> &spaces) {
    vector<int> checksums;
    auto left = 0;
    auto right = ids.size() - 1;

    while (left / 2 <= right) {
        if (left % 2 == 0) {
            const int index = left / 2;

            for (int i = 0; i < ids[index].second; i++) {
                checksums.push_back(ids[index].first);
            }

            ids[index].second = 0;
        } else {
            const int index = (left - 1) / 2;

            for (int i = 0; i < spaces[index]; i++) {
                if (ids[right].second <= 0) {
                    right--;
                }

                if (ids[right].second <= 0) {
                    break;
                }

                checksums.push_back(ids[right].first);
                ids[right].second--;
            }
        }

        left++;
    }

    return countChecksum(checksums);
}

long long movePartialFiles(vector<pair<int, int> > &ids, const vector<int> &spaces) {
    vector<int> checksums;
    const auto n = ids.size() + spaces.size();

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            const int index = i / 2;
            for (int j = 0; j < ids[index].second; j++) {
                checksums.push_back(ids[index].first);
            }
        } else {
            const int index = (i - 1) / 2;
            for (int j = 0; j < spaces[index]; j++) {
                checksums.push_back(-1);
            }
        }
    }

    long long right = checksums.size() - 1;

    while (right >= 0) {
        int files = 0;

        while (right >= 0 && checksums[right] < 0) {
            right--;
        }

        if (checksums[right] >= 0) {
            files++;

            while (checksums[right - 1] == checksums[right]) {
                files++;
                right--;
            }
        }

        int left = 0;

        while (left < right) {
            int space = 0;

            if (checksums[left] == -1) {
                while (checksums[left + space] == -1) {
                    space++;
                }
            }

            if (space >= files) {
                const int file = checksums[right];
                for (int i = 0; i < files; i++) {
                    checksums[left + i] = file;
                    checksums[right + i] = -1;
                }
            }

            left++;
        }

        right--;
    }

    return countChecksum(checksums);
}


long long countChecksum(const vector<int> &checksums) {
    long long checksum = 0;

    for (int i = 0; i < checksums.size(); i++) {
        if (checksums[i] > 0) {
            checksum += i * checksums[i];
        }
    }

    return checksum;
}