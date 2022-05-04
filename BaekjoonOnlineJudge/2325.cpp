#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n; // 정점의 수
int m; // 간선의 수
vector<pii> edge[100001];
int dist[100001];

vector<pii> get_fastest_path(int start_node, int end_node) {
    // 가장 빠른 경로 노드 탐색
    vector<pii> fastest_path;
    int node = end_node;
    int now_dist = dist[end_node];

    while (node != start_node) {
        for (auto there : edge[node]) {
            int there_node = there.first;
            int cost = there.second;

            if (dist[there_node] + cost == now_dist) {
                fastest_path.push_back({node, there_node});
                node = there_node;
                now_dist = now_dist - cost;
                break;
            }
        }
    }

    return fastest_path;
}

int dijkstra(int start_node, int end_node, pii del_path) {
    priority_queue<pii> pq;
    pq.push({0, start_node});
    dist[start_node] = 0;

    // dijkstra main algorithm
    while (!pq.empty()) {
        int cur_dist = -pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        // 이미 최적화된 경로가 존재하는 경우 pass
        if (dist[cur_node] < cur_dist) continue;

        for (auto there : edge[cur_node]) {
            int there_node = there.first;
            int cost = there.second;

            // 제거되는 경로인 경우에는 탐색하지 않는다.
            if (cur_node == del_path.first && there_node == del_path.second) continue;
            else if (cur_node == del_path.second && there_node == del_path.first) continue;

            if (dist[there_node] == -1 || dist[there_node] > cur_dist + cost) {
                dist[there_node] = cur_dist + cost;
                pq.push({-(cur_dist + cost), there_node});
            }
        }
    }

    return dist[end_node];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    // 간선의 정보 입력받기
    for (int i = 0; i < m; ++i) {
        int node_1, node_2, cost;
        cin >> node_1 >> node_2 >> cost;
        edge[node_1].push_back({node_2, cost});
        edge[node_2].push_back({node_1, cost});
    }

    // Dijkstra 실행
    memset(dist, -1, sizeof(dist));
    dijkstra(1, n, pii(0, 0));

    // 최단 경로에 포함된 간선 정보 받아오기
    vector<pii> fastest_path = get_fastest_path(1, n);

    // 최단 경로에 포함된 간선을 하나씩 지워보면서 cost 탐색
    int answer = 0;
    for (pii del_path : fastest_path) {
        memset(dist, -1, sizeof(dist));
        int result = dijkstra(1, n, del_path);
        answer = max(answer, result);
    }

    cout << answer << "\n";

    return 0;
}