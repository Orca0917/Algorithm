#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int w; cin >> w;

    vector<int> answer;
    int l = 1, r = 1;

    while (1 <= r && r <= 1e5) {
        int t = r * r - l * l;
        if (t < w) ++r;
        else if (t == w) answer.push_back(r++);
        else ++l;
    }

    if (answer.empty()) cout << "-1\n";
    else for (int e : answer) cout << e << "\n";
    
    return 0;
}