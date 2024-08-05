#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Node {
    int x;
    int y;
};

vector<Node> nodes;
int n;
Node source, target;
vector<bool> is_prime(10000, true);

int get_distance(Node a, Node b) {
    int dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return floor(sqrt(dist));
}

void eratos() {
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i < 10000; ++i) {
        if (!is_prime[i]) continue;
        for(int j = 2; i * j < 10000; ++j)
            is_prime[i * j] = false;
    }
}

int solve() {
    vector<int> dist(n, 1e9);

    // 우선순위큐를 사용하는 다익스트라를 사용
    priority_queue<pii> pq;
    pq.push({0, n});

    int answer = 1e9;

    while (!pq.empty()) {
        int cur_dist = -pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        int distance = get_distance(nodes[cur_node], target);
        if (is_prime[distance]) answer = min(answer, cur_dist + distance);

        for (int i = 0; i < n; ++i) {
            
            // 자기자신으로 되돌아오는 경우
            if (i == cur_node) continue;

            // 다음 마을로의 거리계산 + 소수인지 판별
            distance = get_distance(nodes[i], nodes[cur_node]);
            if (!is_prime[distance]) continue;

            // 더 짧은 거리인지?
            int new_dist = cur_dist + distance;
            if (dist[i] < new_dist) continue;

            dist[i] = new_dist;
            pq.push({-new_dist, i});
        }
    }

    return (answer == 1e9 ? -1 : answer);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 에라토스 테네스의 체를 사용하여 소수를 먼저 판별
    eratos();

    // 시작지점, 도착지점 입력받기
    cin >> source.x >> source.y >> target.x >> target.y;
    
    // 중간 마을의 수 와 정보 입력받기
    cin >> n;
    nodes.resize(n);
    for (Node &node : nodes) cin >> node.x >> node.y;
    nodes.push_back(source);

    // 다익스트라를 사용한 풀이
    cout << solve() << "\n";
    
    return 0;
}