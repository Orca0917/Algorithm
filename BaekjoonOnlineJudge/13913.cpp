#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int s, e;
int p[200'001];
bool vis[200'001];

int bfs() {
    queue<pii> q;
    q.push({s, 0});
    vis[s] = true;
    p[s] = s;
    
    while (!q.empty()) {
        int here = q.front().first;
        int time = q.front().second;
        q.pop();

        if (here == e) return time;

        // 앞 뒤 이동
        if (here - 1 >= 0 && !vis[here - 1]) {
            vis[here - 1] = true;
            q.push({here - 1, time + 1});
            p[here - 1] = here;
        }

        if (here + 1 <= 100'000 && here < e&& !vis[here + 1]) {
            vis[here + 1] = true;
            q.push({here + 1, time + 1});
            p[here + 1] = here;
        }

        if (here * 2 <= 200'000 && here < e && !vis[here * 2]) {
            vis[here * 2] = true;
            q.push({here * 2, time + 1});
            p[here * 2] = here;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s >> e;

    memset(p, -1, sizeof(p));
    memset(vis, false, sizeof(vis));
    cout << bfs() << "\n";
    
    stack<int> st;
    while (e != p[e]) {
        st.push(e);
        e = p[e];
    } st.push(e);

    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    return 0;
}