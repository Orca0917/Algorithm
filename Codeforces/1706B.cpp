#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> color_index[100'001];

int solve(int color) {
    if (!color_index[color].size()) return 0;

    int cur_pos = color_index[color][0];
    int answer = 1;

    for (int i : color_index[color]) {
        if ((i & 1) != (cur_pos & 1)) {
            ++answer;
            cur_pos = i;
        }
    }

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) color_index[i].clear();
        
        for (int i = 1; i <= n; ++i) {
            int color; cin >> color;
            color_index[color].push_back(i);
        }

        for (int i = 1; i <= n; ++i) cout << solve(i) << " \n"[i == n];
    }


    return 0;
}