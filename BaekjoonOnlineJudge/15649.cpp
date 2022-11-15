#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
vector<vector<int>> answer;

void backtrack(mask) {
    if (perm.size() == m) {
        answer.push_back(perm);
        return;
    }

    for (int i = 1; i <= n; ++i) {
        bool pass = false;
        for (int e : perm) {
            if (e == i) {
                pass = true;
                break;
            }
        }
        if (pass) continue;

        perm.push_back(i);
        backtrack(perm);
        perm.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    backtrack(0);

    for (vector<int> &e : answer) {
        for (int elem : e) cout << elem << " ";
        cout << "\n";
    }
    
    return 0;
}