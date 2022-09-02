#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<pii> adj[50005];
bool is_gate[50005];
bool is_top[50005];

bool check(int mid, int start_gate) {
    bool vis[50005];
    memset(vis, false, sizeof(vis));
    
    queue<int> q;
    vis[start_gate] = true;
    q.push(start_gate);

    while (!q.empty()) {
        int now = q.front(); q.pop();

        if (is_gate[now]) return true;

        for (auto there_info : adj[now]) {
            int there = there_info.first;
            int cost = there_info.second;

            // 해당 intensity로 등반할 수 없습니다..ㅠㅠ
            if (cost > mid || vis[there] || is_top[there]) continue;
            vis[there] = true;
            q.push(there);
        }
    }

    return false;
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    /**
     * paramters
     * 
     * n : node의 수
     * paths : {i, j, w} : i <-> j (cost : w)
     * gates : 출발지 목록
     * summits : 봉우리 목록
     */
    sort(summits.begin(), summits.end());

    memset(is_gate, false, sizeof(is_gate));
    memset(is_top, false, sizeof(is_top));
    for (int e : gates) is_gate[e] = true;
    for (int e : summits) is_top[e] = true;

    vector<int> final_result;

    int min_intensity = 1e9;
    // make adjacency list => adj[start] = {end, cost}
    for (vector<int> path : paths) {
        int node1 = path[0];
        int node2 = path[1];
        int cost = path[2];

        adj[node1].push_back({node2, cost});
        adj[node2].push_back({node1, cost});
        min_intensity = min(min_intensity, cost);
    }

    // 1. 이분탐색을 수행한다.
    int lo = 0, hi = 1e8, answer = 0;
    int answer_point = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        bool can_go = false;

        // 2. 해당 경로를 통해서 봉우리에 도달할 수 있는지 확인한다.
        for (int summit : summits) {
            bool result = check(mid, summit);
            if (result) {
                can_go = true;
                answer_point = summit;
                break;
            }
        }

        if (can_go) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    // 4. 최종적으로 반환해야 하는 값은 [봉위 번호, intenstiy 최소값] 이다.

    final_result.push_back(answer_point);
    final_result.push_back(answer);
    return final_result;
}
