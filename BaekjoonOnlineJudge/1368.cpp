#include <bits/stdc++.h>
#define pii pair<int, int>
#define MAX 301
#define ll long long

using namespace std;

int n;
int node_cnt = 0;
int answer = 0;

int weight[MAX][MAX];
int cost[MAX];

bool vis_edge[MAX][MAX];
bool vis_node[MAX];

priority_queue<pii> pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    // initialization
    memset(cost, 0, sizeof(cost));
    memset(weight, 0, sizeof(weight));
    memset(vis_edge, false, sizeof(vis_edge));
    memset(vis_node, false, sizeof(vis_node));

    // 논에 직접 우물을 파는 경우
    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
        pq.push({-cost[i], i});
    }

    // 물을 길러 오는 경우
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> weight[i][j];

    
    // priority_queue
    // 1. cost가 작은 것 먼저 선택
    //  - 이미 방문하지 않은 노드 : vis_node로 관리
    //  - priority_queue에 삽입된 간선은 다시 추가하지 않기 위해 vis로 관리
    // 2. n개의 노드가 모두 선택된 경우 종료
    while (!pq.empty() && node_cnt < n) {
        int x = pq.top().second;
        int d = -pq.top().first;
        pq.pop();

        // 새로운 노드인 경우 추가
        if (vis_node[x] == false) {
            vis_node[x] = true;
            answer += d;
            node_cnt += 1;
        } else {
            continue;
        }
        
        // 주변 노드 탐색
        for (int there = 1; there <= n; ++there) {
            if (weight[x][there] > 0 && vis_edge[x][there] == false) {
                vis_edge[x][there] = true;
                pq.push({-weight[x][there], there});
            }
        }
    }

    cout << answer << "\n";

    
    return 0;
}