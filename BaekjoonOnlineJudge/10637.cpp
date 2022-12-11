#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100001
#define val first
#define lazy second

using namespace std;

struct Edge {
    int index;
    int u;
    int v;
    int w;
};

int uf_parent[MAX];         // union-find 에서 사용하는 parent 변수

int hld_num[MAX];           // 1을 루트노드로 하여 방문한 순서
int hld_depth[MAX];         // hld를 적용시켰을 때, hld의 깊이
int hld_parent[MAX];        // 해당 hld의 부모 hld
int hld_head[MAX];          // 해당 hld의 시작 노드
int hld_cnt = 1;

int subtree_size[MAX];      // 해당 노드를 루트로하는 서브트리의 크기

vector<Edge> edge;          // 모든 간선의 정보 (index, 시작, 끝, 가중치)
vector<int> adj[MAX];       // MST 트리 정보
vector<pii> tree;           // Segment Tree with lazy propagation (값, lazy)

bool is_MST_edge[2 * MAX];  // 해당 간선이 MST 간선인지 확인
ll answer[2 * MAX];         // 최종 정답 (offline query)

int n, m;


// union-find의 find function
int find_f(int x) {
    if (uf_parent[x] != x) return uf_parent[x] = find_f(uf_parent[x]);
    return x;
}


// union-find의 union function
void union_f(int x, int y) {
    x = find_f(x);
    y = find_f(y);

    if (x == y) return;
    uf_parent[x] = y;
}


// segment tree with lazy propagation
void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy != 1e9) {
        tree[node].val = min(tree[node].val, tree[node].lazy);
        if (start != end) {
            tree[node * 2].lazy = min(tree[node * 2].lazy, tree[node].lazy);
            tree[node * 2 + 1].lazy = min(tree[node * 2 + 1].lazy, tree[node].lazy);
        }
        tree[node].lazy = 1e9;
    }
}


// segment tree의 업데이트
void update_tree(int node, int start, int end, int left, int right, int value) {
    lazy_propagation(node, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy = value;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, value);
    update_tree(node * 2 + 1, mid + 1, end, left, right, value);

    tree[node].val = min(tree[node * 2].val, tree[node * 2 + 1].val);
}


// segment tree의 쿼리
int query_tree(int node, int start, int end, int left, int right) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return 1e9;
    if (left <= start && end <= right) return tree[node].val;

    int mid = (start + end) / 2;
    int l = query_tree(node * 2, start, mid, left, right);
    int r = query_tree(node * 2 + 1, mid + 1, end, left, right);

    return min(l, r);
}


// 1을 루트로 하는 MST의 서브트리 크기 계산
void calc_subtree(int here, int parent) {
    subtree_size[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_subtree(there, here);
        subtree_size[here] += subtree_size[there];
        if (subtree_size[there] > subtree_size[adj[here][0]]) {
            swap(there, adj[here][0]);
        }
    }
}


// hld function
void heavy_light_decomposition(int here, int parent, int depth) {
    hld_num[here] = hld_cnt++;
    hld_depth[here] = depth;

    for (int there : adj[here]) {
        if (there == parent) continue;
        if (there == adj[here][0]) {
            hld_head[there] = hld_head[here];
            hld_parent[there] = hld_parent[here];
            heavy_light_decomposition(there, here, depth);
        }
        else {
            hld_head[there] = there;
            hld_parent[there] = here;
            heavy_light_decomposition(there, here, depth + 1);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    // MST가 생성될 수 없음 (트리가 만들어지지 않음)
    if (m < n - 1) {
        while (m--) cout << "-1\n";
        return 0;
    }

    // segment tree 크기 계산
    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {1e9, 1e9});


    // union-find를 위한 부모 자기자신으로 초기화
    for (int i = 0; i <= n; ++i) uf_parent[i] = i;


    // 모든 간선의 정보 입력받기
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        edge.push_back({i, u, v, w});
    }


    // edge를 가중치를 기준으로 정렬
    sort(edge.begin(), edge.end(), [](const Edge &a, const Edge &b) -> bool {
        return a.w < b.w;
    });

    
    int connected = 0, i = 0;
    ll MST_weight = 0;
    memset(is_MST_edge, false, sizeof(is_MST_edge));

    // 최소 스패닝 트리 구하기
    while (connected < n - 1) {
        Edge e = edge[i++];
        if (find_f(e.u) != find_f(e.v)) {
            union_f(e.u, e.v);
            MST_weight += e.w;
            ++connected;
            is_MST_edge[e.index] = true;
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
        }
    }


    // construct hld
    calc_subtree(1, 1);
    hld_head[1] = 1;
    heavy_light_decomposition(1, 0, 1);


    // MST 간선이 아닌 간선들 계산
    for (Edge e : edge) {
        if (is_MST_edge[e.index]) continue;

        int u = e.u, v = e.v;
        if (hld_depth[u] > hld_depth[v]) swap(u, v);
        while (hld_depth[u] < hld_depth[v]) {
            update_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v], e.w);
            v = hld_parent[v];
        }

        while (hld_head[u] != hld_head[v]) {
            update_tree(1, 1, n, hld_num[hld_head[u]], hld_num[u], e.w);
            update_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v], e.w);

            u = hld_parent[u];
            v = hld_parent[v];
        }

        if (hld_num[u] > hld_num[v]) swap(u, v);
        update_tree(1, 1, n, hld_num[u] + 1, hld_num[v], e.w);
    }


    // Offline query
    for (Edge e : edge) {
        if (!is_MST_edge[e.index]) {
            answer[e.index] = MST_weight;
            continue;
        }

        int result = 1e9;
        int u = e.u, v = e.v;
        if (hld_depth[u] > hld_depth[v]) swap(u, v);
        while (hld_depth[u] < hld_depth[v]) {
            result = min(result, query_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v]));
            v = hld_parent[v];
        }

        while (hld_head[u] != hld_head[v]) {
            result = min(result, query_tree(1, 1, n, hld_num[hld_head[u]], hld_num[u]));
            result = min(result, query_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v]));

            u = hld_parent[u];
            v = hld_parent[v];
        }

        if (hld_num[u] > hld_num[v]) swap(u, v);
        result = min(result, query_tree(1, 1, n, hld_num[u] + 1, hld_num[v]));

        answer[e.index] = (result == 1e9 ? -1 : MST_weight - e.w + result);
    }
    

    // 정답 출력
    for (int i = 0; i < m; ++i) cout << answer[i] << "\n";

    return 0;
}