#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    vector<int> arr(m);
    for (int &e : arr) cin >> e;

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        bool open = false;
        int cnt = 0;
        for (int j = 0; j < m; ++j) {
            if (arr[j] > i) {
                if (open) answer += cnt, cnt = 0;
                else open = true;
            } 
            else if (open) ++cnt;
        }
    }

    cout << answer << "\n";

    
    return 0;
}