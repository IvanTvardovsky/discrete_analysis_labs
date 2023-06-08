#include <iostream>
#include <vector>

const int MAX_AMOUNT = 65536;

using namespace std;

int main() {
    int n;
    int x;
    string s;
    
    vector<pair<int, string>> pairs;
    vector<int> numOfNums(MAX_AMOUNT, 0);
    vector<int> cumulative(MAX_AMOUNT, 0);
    
    while (cin >> x >> s) {
        pairs.push_back(make_pair(x, s));
        numOfNums[x] += 1;
        ++n;
    }
    
    vector<pair<int, string>> ans(n);
    
    cumulative[0] = numOfNums[0];
    for (int i = 1; i < MAX_AMOUNT; ++i) {
        cumulative[i] += cumulative[i - 1] + numOfNums[i];
    }
    
    for (int i = n - 1; i >= 0; --i) {
        int key = pairs[i].first;
        int pos = cumulative[key] - 1;
        ans[pos] = pairs[i];
        cumulative[key] -= 1;
    }
    
    for (int i = 0; i < n; ++i) {
        cout << ans[i].first << "\t" << ans[i].second << endl;
    }

    return 0;
}
