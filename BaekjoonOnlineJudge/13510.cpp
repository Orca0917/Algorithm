#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001

using namespace std;

int n; // 정점의 개수
vector<pii> adj[MAX];
pii edge[MAX];
vector<int> tree;

void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    else if (start == end) {
        tree[node] = value;
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, index, value);
    update_tree(node * 2 + 1, mid + 1, end, index, value);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return max(query_tree(node * 2, start, mid, left, right), \
                query_tree(node * 2 + 1, mid + 1, end, left, right));
}

int subtree_size[MAX];
int HLD_num[MAX];
int chain_depth[MAX];
int chain_head[MAX];
int chain_parent[MAX];

// here을 루트로 하는 서브트리의 크기 계산
// adj[here][0]에는 서브트리의 크기가 가장큰 인접 노드가 오도록 설정
void get_size(int here, int parent) {
    subtree_size[here] = 1;
    for (pii &there_info : adj[here]) {
        int there = there_info.first;

        if (there == parent) continue;

        get_size(there, here);
        subtree_size[here] += subtree_size[there];

        // Heavy 경로를 가장 맨 앞에 오도록 설정한다.
        if (subtree_size[there] > subtree_size[adj[here][0].first] || adj[here][0].first == parent) {
            swap(adj[here][0], there_info);
        }
    }
}

// Heavy Light Decomposition
int HLD_cnt = 1;
void HLD(int here, int parent, int level) {
    HLD_num[here] = HLD_cnt++;
    chain_depth[here] = level;
    bool is_first = true;
    
    for (pii there_info : adj[here]) {
        int there = there_info.first;
        int weight = there_info.second;

        if (there == parent) continue;

        // 서브트리의 크기가 가장 큰 곳으로 이동한 경우
        if (is_first) {
            is_first = false;
            chain_head[there] = chain_head[here];
            chain_parent[there] = chain_parent[here];
            HLD(there, here, level);
        } 
        
        // 그외의 경우
        else {
            chain_head[there] = there;
            chain_parent[there] = here;
            HLD(there, here, level + 1);
        }

        update_tree(1, 1, n, HLD_num[there], weight);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 노드의 개수 입력받기
    cin >> n;
    
    // 세그먼트 트리 크기 지정
    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (1 + tree_height));
    tree.resize(tree_size);

    // 간선의 정보 입력받기 (양방향)
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edge[i + 1] = {u, v};
    }
    
    // 서브트리의 크기 계산
    get_size(1, 0);
    chain_head[1] = 1;

    // Heavy Light Decomposition 진행
    HLD(1, 0, 1);

    int m; cin >> m;
    while (m--) {
        int option; cin >> option;
        if (option == 1) {
            int index, value; cin >> index >> value;
            int &u = edge[index].first;
            int &v = edge[index].second;
            if (HLD_num[u] > HLD_num[v]) swap(u, v);
            update_tree(1, 1, n, HLD_num[v], value);
        }

        else if (option == 2) {
            int u, v; cin >> u >> v;
            if (chain_depth[u] > chain_depth[v]) swap(u, v);


            int answer = 0;

            // 깊이 맞춰주기
            while (chain_depth[u] < chain_depth[v]) {
                answer = max(answer, query_tree(1, 1, n, HLD_num[chain_head[v]], HLD_num[v]));
                v = chain_parent[v];
            }

            // LCA 공통 조상노드로 올라가기
            while (chain_head[u] != chain_head[v]) {
                answer = max(answer, query_tree(1, 1, n, HLD_num[chain_head[u]], HLD_num[u]));
                answer = max(answer, query_tree(1, 1, n, HLD_num[chain_head[v]], HLD_num[v]));

                u = chain_parent[u];
                v = chain_parent[v];
            }

            if (HLD_num[u] > HLD_num[v]) swap(u, v);
            answer = max(answer, query_tree(1, 1, n, HLD_num[u] + 1, HLD_num[v]));

            cout << answer << "\n";
        }
    }

    return 0;
}