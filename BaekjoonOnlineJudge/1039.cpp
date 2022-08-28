#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

string n;
int k;
bool vis[1'000'001][2];

int bfs() {
    memset(vis, false, sizeof(vis));
    queue<pair<string, int>> q;
    q.push({n, 0});

    vector<int> cand;
    while (!q.empty()) {
        string x = q.front().first;
        int c = q.front().second;
        q.pop();

        if (c == k) break;

        int X = (int)x.length();
        for (int i = 0; i < X; ++i) {
            for (int j = i + 1; j < X; ++j) {
                string temp = x;
                swap(temp[i], temp[j]);
                int temp_i = stoi(temp);

                if (temp[0] == '0') continue;
                if (vis[temp_i][(c + 1) % 2]) continue;
                
                vis[temp_i][(c + 1) % 2] = true;
                q.push({temp, c + 1});

                if ((c + 1) % 2 == k % 2) cand.push_back(temp_i);
            }
        }
    }

    sort(cand.begin(), cand.end());
    if (cand.size() == 0) return -1;
    return cand.back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> k;

    cout << bfs() << "\n";
    
    return 0;
}