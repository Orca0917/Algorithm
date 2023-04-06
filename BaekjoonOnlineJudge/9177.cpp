#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

string s1, s2, target;
int memo[201][201];

int dp(int word_index1, int word_index2) {
    int target_index = word_index1 + word_index2;
    if (target_index == target.length()) return 1;
    
    int &ret = memo[word_index1][word_index2];
    if (ret != -1) return ret;

    ret = 0;
    if (target[target_index] == s1[word_index1]) ret = max(ret, dp(word_index1 + 1, word_index2));
    if (target[target_index] == s2[word_index2]) ret = max(ret, dp(word_index1, word_index2 + 1));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    for (int tc = 1; tc <= testcase; ++tc) {
        cin >> s1 >> s2 >> target;
        memset(memo, -1, sizeof(memo));
        int result = dp(0, 0);
        cout << "Data set " << tc << ": " << (result? "yes" : "no") << "\n";
    }
    
    return 0;
}