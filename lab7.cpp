#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAX_LENGTH = 100;

int main() {
    string s;
    cin >> s;
    
    long long dp[MAX_LENGTH][MAX_LENGTH];
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < s.size(); ++i) {
        dp[i][i] = 1;
    }
    
    for (int length = 1; length < s.size(); length++) {
        for (int i = 0; i + length < s.size(); i++) {
            int j = i + length;
            if (s[i] != s[j])
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
            else
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + 1;
        }
    }
    
    cout << dp[0][s.size() - 1] << "\n";

    return 0;
}
