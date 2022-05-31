#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int K; // 가져올 수 있는 최대 접시의 수
int N; // 사람의 수
int D; // 음식의 종류

vector<int> adj[303];
int capacity[303][303], flow[303][303];

int ff(int source, int sink) {
    int result = 0;

    while (true) {
        vector<int> parent(303, -1);
        queue<int> q;

        q.push(source);
        parent[source] = source;

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
                    q.push(there);
                    parent[there] = here;
                }
            }
        }

        if (parent[sink] == -1) break;

        ////// 역방향 간선 계산 //////

        int amount = 1e9;

        for (int node = sink; node != source; node = parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }

        result += amount;
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    /// initialize ///
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    cin >> N >> K >> D;

    // 1. source - person
    for (int person = 1; person <= N; ++person) {
        adj[0].push_back(person);
        adj[person].push_back(0);
        capacity[0][person] = K;
    }

    // 2. food - sink
    for (int food = 1; food <= D; ++food) {
        adj[food + 200].push_back(301);
        adj[301].push_back(food + 200);
        cin >> capacity[food + 200][301];
    }

    // 3. person - food
    for (int person = 1; person <= N; ++person) {
        int can_make; cin >> can_make;
        while (can_make--) {
            int food; cin >> food;
            adj[person].push_back(food + 200);
            adj[food + 200].push_back(person);
            capacity[person][food + 200] = 1;
        }
    }

    cout << ff(0, 301) << "\n";

    return 0;
}