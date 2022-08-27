#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, t, g;
bool vis[100000];

int button_B(int num) {
    int temp = 1;
    while (num * 2 >= temp * 10) temp *= 10;
    return num * 2 - temp;
}


int bfs() {
    memset(vis, false, sizeof(vis));

    queue<pii> q;
    q.push({n, 0});
    vis[n] = true;

    while (!q.empty()) {
        int cur = q.front().first;
        int cnt = q.front().second;
        q.pop();

        if (cnt > t) break;
        if (cur == g) return cnt;

        if (cur + 1 < 100'000 && !vis[cur + 1]) {
            vis[cur + 1] = true;
            q.push({cur + 1, cnt + 1});
        }

        if (cur * 2 >= 100000) continue;
        int after_B = max(button_B(cur), 0);

        if (!vis[after_B]) {
            vis[after_B] = true;
            q.push({after_B, cnt + 1});
        }
    }

    return -1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> t >> g;

    int ret = bfs();
    if (ret == -1) cout << "ANG\n";
    else cout << ret << "\n";    
    
    return 0;
}