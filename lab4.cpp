#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> fun(string s) {
    int l = 0, r = 0;
    int size = s.size();
    vector<int> ans(size);
    
    for (int i = 1; i < size; ++i) {
        if (i > r) {
            l = i;
            r = i;
            while (r < size && s[r] == s[r - l]) {
                ++r;
            }
            ans[i] = r - l;
            --r;
            
        } else {
            int i1 = i - l;
            if (ans[i1] < r - i + 1) {
                ans[i] = ans[i1];
            } else {
                l = i;
                while (r < size && s[r] == s[r - l]) {
                    ++r;
                }
                ans[i] = r - l;
                --r;
            }
        }
    }
    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    string haystack, needle;
    cin >> haystack >> needle;
    vector<int> nums = fun(needle + "~" + haystack);
    
    int needleSize = needle.size();
    
    for (int i = needleSize + 1; i < nums.size(); ++i) {
        if (nums[i] == needleSize) {
            cout << i - needleSize - 1 << "\n";  
        }
    }

    return 0;
}
