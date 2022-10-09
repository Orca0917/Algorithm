#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;

    vector<int> v;
    int cnt = 1;
    for (int i = 0; i < n - 1; ++i) {
        int width; cin >> width;
        if (width <= k) ++cnt;
        else {
            v.push_back(cnt);
            cnt = 1;
        }
    }
    v.push_back(cnt);

    int answer = max(2, v[0]);
    for (int i = 0; i < v.size() - 1; ++i)
        answer = max(answer, v[i] + v[i + 1]);
    cout << answer << "\n";
    
    return 0;
}