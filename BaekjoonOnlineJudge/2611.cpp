#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N;  // 지점의 개수
vector<pii> adj[1001], answer;
vector<int> indeg;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N;
    indeg.resize(N + 1, 0);
    answer.resize(N + 1, {0, -1});  // {최대점수, 어디서?}
    
    int M; cin >> M;
    for (int i = 0; i < M; ++i) {
        int p, q, r; cin >> p >> q >> r;
        adj[p].push_back({q, r});
        indeg[q] += 1;
    }

    for (int i = 1; i <= N; ++i) answer[i] = {0, -1};

    queue<pii> q; // { 현재까지 점수, 현재 지점 }
    q.push({1, 0}); 

    while (!q.empty()) {
        int here = q.front().first;
        int here_score = q.front().second;
        q.pop();

        for (pii there : adj[here]) {
            int there_score = here_score + there.second;
            int there_point = there.first;
            if (indeg[there_point] == 0) continue;

            indeg[there_point] -= 1;
            if (answer[there_point].first < there_score) {
                answer[there_point] = {there_score, here};
            }

            if (indeg[there_point] == 0) {
                q.push({there_point, answer[there_point].first});
            }
        }
    }

    cout << answer[1].first << "\n";

    deque<int> path;
    path.push_back(1);
    
    int cur = answer[1].second;
    while (cur != 1) {
        path.push_front(cur);
        cur = answer[cur].second;
    }
    path.push_front(1);

    for (int item : path) cout << item << " ";

    return 0;
}