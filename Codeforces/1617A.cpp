#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        string s, t; cin >> s >> t;

        string perm;
        vector<string> cand = {"abc", "acb", "bac", "bca", "cab", "cba"};
        
        bool hasa = false, hasb = false, hasc = false;
        for (char c : s)
            if (c == 'a') hasa = true;
            else if (c == 'b') hasb = true;
            else if (c== 'c') hasc = true;
        
        bool allContains = hasa && hasb && hasc;

        perm = cand[0];
        for (int i = 0; i < cand.size() && allContains; ++i)
            if (cand[i] != t) {
                perm = cand[i];
                break;
            }

        int cnt['z' - 'a' + 1];
        memset(cnt, 0, sizeof(cnt));
        string left;

        for (char c : s) {
            cnt[c - 'a']++;
            if (c > 'c') left += c;
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < cnt[perm[i] - 'a']; ++j)
                cout << perm[i];
        }

        sort(left.begin(), left.end());
        cout << left << "\n";
    }
       
    return 0;
}