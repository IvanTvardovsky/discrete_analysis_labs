#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n;
    int n1, n2;
    cin >> n;
    
    set<pair<int, int>> s;
    vector<pair<int, int>> elems;
    vector<pair<int, int>> ans;
    
    for (int i = 0; i < n; ++i) {
        cin >> n1 >> n2;
        s.insert(make_pair(n1, n2));
        elems.push_back(make_pair(n1, n2));
    }
    
    int m;
    cin >> m;
    
    int leftNotIncluded = 0;
    bool noInterval = false;
    
    while (leftNotIncluded < m) {
        int max = -1;
        int first = -1;
        auto toBeDeleted = *(s.begin());
        for (auto itr : s) {
            if (itr.first <= leftNotIncluded && itr.second >= leftNotIncluded) {
                if (itr.second > max) {
                    max = itr.second;
                    first = itr.first;
                    toBeDeleted = itr;
                }
            }
        }
        if (max == -1) {
            noInterval = true;
            break;
        }
        
        leftNotIncluded = max;
        ans.push_back(make_pair(first, max));
        s.erase(toBeDeleted);
    }
    
    if (noInterval) {
        cout << "0" << "\n";
    } else {
        vector<pair<int, int>> finalAns;
        int counter = 0;
        for (auto elem : elems) {
            for (auto it = ans.begin(); it < ans.end(); ++it) {
                if (*it == elem) {
                    ans.erase(it);
                    finalAns.push_back(elem);
                    ++counter;
                }
            }
        }
        cout << counter << "\n";
        for (auto elem : finalAns) {
            cout << elem.first << " " << elem.second << "\n";
        }
    }

    return 0;
}
