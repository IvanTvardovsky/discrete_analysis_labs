#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

const int ALPHABET_CAPACITY = 100000;

int charToInt(char c) {
    if (c == '$') {
        return 0;
    } else {
        return c - 'a' + 1;
    }
}

char intToChar(int n) {
    if (n == 0) {
        return '$';
    } else {
        return n + 'a' - 1;
    }
}

template <typename T1, typename T2>
void countingSort(vector<pair<T1, T2>>& v, int length) {
    vector<int> numOfNums(ALPHABET_CAPACITY, 0);
    vector<int> cumulative(ALPHABET_CAPACITY, 0);
    for (int i = 0; i < length; ++i) {
        numOfNums[v[i].first] += 1;
    }
    vector<pair<T1, T2>> ans(length);
    cumulative[0] = numOfNums[0];
    for (int i = 1; i < ALPHABET_CAPACITY; ++i) {
        cumulative[i] += cumulative[i - 1] + numOfNums[i];
    }
    for (int i = length - 1; i >= 0; --i) {
        int key = v[i].first;
        int pos = cumulative[key] - 1;
        ans[pos] = v[i];
        cumulative[key] -= 1;
    }
    v = move(ans);
}

string getCycleWord(string input, int index, int length) {
    string word;
    int counter = 0;
    while (counter != length) {
        word += input[index];
        ++counter;
        ++index;
        if (index == int(input.length())) {
            index = 0;
        }
    }
    return word;
}

string BWT(const string &input) {
    int inputLength = input.size();
    vector<int> indices(inputLength);
    for (int i = 0; i < inputLength; ++i) {
        indices[i] = i;
    }

    sort(indices.begin(), indices.end(), [&](int x1, int x2) {
        for (int i = 0; i < inputLength; ++i) {
            if (input[(x1 + i) % inputLength] != input[(x2 + i) % inputLength]) {
                return input[(x1 + i) % inputLength] < input[(x2 + i) % inputLength];
            }
        }
        return false;
    });

    string ans;
    for (int i = 0; i < inputLength; ++i) {
        int index = indices[i];
        if (index == 0) {
            ans += input[inputLength - 1];
        } else {
            ans += input[index - 1];
        }
    }

    return ans;
}

// O(n * m)     это вроде можно ускорить
void MTF(string input, vector<int>& ans) {
    unordered_map<char, int> alphabet;
    alphabet['$'] = 0;

    for (char i = 'a'; i <= 'z'; ++i) {
        alphabet[i] = i - 'a' + 1;
    }

    for (auto symbol : input) { // chars
        int symbolPlace = alphabet[symbol]; // position of [i] symbol
        ans.push_back(symbolPlace);

        if (symbolPlace != 0) {
            for (auto it = alphabet.begin(); it != alphabet.end(); ++it) {
                if (it->second < symbolPlace) it->second += 1;
            }
        }
        alphabet[symbol] = 0;
    }
}

void RLE(vector<int>& v) {
    int counter = 1;
    for (int i = 1; i < int(v.size()); ++i) {
        if (v[i] == v[i - 1]) {
            ++counter;
        } else {
            cout << counter << " " << v[i - 1] << "\n";
            counter = 1;
        }
    }
    cout << counter << " " << v[v.size() - 1] << "\n";
}

void decompress_RLE(const vector<pair<int, int>>& v, vector<int>& ans) {
    int totalElements = 0;
    for (const auto& p : v) {
        totalElements += p.first;
    }

    ans.reserve(totalElements);

    for (const auto& p : v) {
        ans.insert(ans.end(), p.first, p.second);
    }
}

string decompress_MTF(vector<int>& v) {
    unordered_map<int, char> alphabet;
    alphabet[0] = '$';

    for (int i = 1; i <= 'z' - 'a' + 1; ++i) {
        alphabet[i] = char(i + 'a' - 1);
    }

    string ans;
    for (const auto number : v) {
        int charWithNumber = alphabet[number];
        ans.push_back(charWithNumber);
        unordered_map<int, char> prev = alphabet;
        for (int i = 1; i < number + 1; ++i) {
            alphabet[i] = prev[i - 1];
        }
        alphabet[0] = charWithNumber;
    }
    return ans;
}

void decompress_BWT(string input) {
    int inputLength = input.length();
    vector<pair<char, int>> symbols(inputLength);
    for (int i = 0; i < inputLength; ++i) {
        symbols[i] = make_pair(input[i], i);
    }
    sort(symbols.begin(), symbols.end());
    string result;
    int index = 0;
    for (int i = 0; i < inputLength; ++i) {
        index = symbols[index].second;
        result += symbols[index].first;
    }
    cout << result.erase(result.size() - 1) << endl;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //auto start_time = std::chrono::high_resolution_clock::now();
    string type;
    cin >> type;
    
    if (type == "compress") {
        string input;
        cin >> input;
        if (input == "") {
            return 0;
        }
        input += "$";
        input = BWT(input);
        vector<int> afterMTF;
        MTF(input, afterMTF);
        RLE(afterMTF);    
    } else if (type == "decompress") {
        vector<pair<int, int>> input;
        int x1, x2;
        while (cin >> x1 >> x2) {
            input.emplace_back(x1, x2);
        }
        vector<int> temp;
        decompress_RLE(input, temp);    
        string ans = decompress_MTF(temp);
        decompress_BWT(ans);
    } else {
        cout << "Wrong command.\n";
    }

    //auto end_time = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    //std::cout << duration.count() << std::endl;
    return 0;
}
