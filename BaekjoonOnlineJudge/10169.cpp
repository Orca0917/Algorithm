#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX_VERTEX 100001
#define MAX_EDGE 300001
#define INF 1e9 + 5
using namespace std;

// Edge정보를 저장할 구조체 생성 (Edge의 index, 시작점, 도착점, 가중치)
struct Edge {
    int index;
    int u;
    int v;
    int w;
};

int n, m;                           // 정점의 수, 간선의 수
int subtree_size[MAX_VERTEX];       // 서브트리의 크기
int uf_parent[MAX_VERTEX];          // union-find에서 사용하는 부모 변수
int hld_head[MAX_VERTEX];           // hld k 의 시작점
int hld_parent[MAX_VERTEX];         // hld k 의 부모
int hld_num[MAX_VERTEX];            // 정점 k의 hld 노드
int hld_depth[MAX_VERTEX];          // 정점 k의 hld 깊이
int hld_cnt = 1;                    // hld의 번호 매김 용도

bool is_MST_edge[MAX_EDGE];         // 해당 간선이 MST에 포함되는 간선인지 확인
ll answer[MAX_EDGE];                // 오프라인 쿼리에 적용

vector<int> adj[MAX_VERTEX];        // MST 간선 연결정보
vector<Edge> edge;                  // 모든 간선의 정보
vector<pii> tree;                   // 세그먼트 트리



void lazy_propagation(int node, int start, int end) {
    if (tree[node].second != INF) {
        tree[node].first = min(tree[node].first, tree[node].second);
        if (start != end) {
            tree[node << 1].second = min(tree[node << 1].second, tree[node].second);
            tree[node << 1 | 1].second = min(tree[node << 1 | 1].second, tree[node].second);
        }
        tree[node].second = INF;
    }
}



void update_tree(int node, int start, int end, int left, int right, int value) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].second = value;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = start + end >> 1;
    update_tree(node << 1, start, mid, left, right, value);
    update_tree(node << 1 | 1, mid + 1, end, left, right, value);
    tree[node].first = min(tree[node << 1].first, tree[node << 1 | 1].first);
}



int query_tree(int node, int start, int end, int left, int right) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return INF;
    if (left <= start && end <= right) return tree[node].first;

    int mid = start + end >> 1;
    int L = query_tree(node << 1, start, mid, left, right);
    int R = query_tree(node << 1 | 1, mid + 1, end, left, right);
    return min(L, R);
}



void calculate_subtree_size(int here, int par) {
    subtree_size[here] = 1;
    for (int &there : adj[here]) {
        if (there == par) continue;
        calculate_subtree_size(there, here);
        subtree_size[here] += subtree_size[there];
        if (subtree_size[there] > subtree_size[adj[here][0]]) swap(there, adj[here][0]);
    }
}



void heavy_ligth_decomposition(int here, int par, int level) {
    hld_num[here] = hld_cnt++;
    hld_depth[here] = level;

    for (int there : adj[here]) {
        if (there == par) continue;
        if (there == adj[here][0]) {
            hld_parent[there] = hld_parent[here];
            hld_head[there] = hld_head[here];
            heavy_ligth_decomposition(there, here, level);
        }
        else {
            hld_parent[there] = here;
            hld_head[there] = there;
            heavy_ligth_decomposition(there, here, level + 1);
        }
    }
}



void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}



int query(int u, int v) {
    int result = INF;
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

    return result;
}



void update(int u, int v, int w) {
    if (hld_depth[u] > hld_depth[v]) swap(u, v);
    while (hld_depth[u] < hld_depth[v]) {
        update_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v], w);
        v = hld_parent[v];
    }
    while (hld_head[u] != hld_head[v]) {
        update_tree(1, 1, n, hld_num[hld_head[u]], hld_num[u], w);
        update_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v], w);

        u = hld_parent[u];
        v = hld_parent[v];
    }
    if (hld_num[u] > hld_num[v]) swap(u, v);
    update_tree(1, 1, n, hld_num[u] + 1, hld_num[v], w);
}



int find_f(int x) {
    if (uf_parent[x] != x) return uf_parent[x] = find_f(uf_parent[x]);
    else return x;
}



void union_f(int x, int y) {
    x = find_f(x);
    y = find_f(y);

    if (x == y) return;
    uf_parent[x] = y;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;


    // MST 생성 불가
    if (m < n - 1) {
        while (m--) cout << "-1\n";
        return 0;
    }


    // 세그먼트 트리 크기 지정
    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {INF, INF});


    // union-find 부모 변수 초기화
    for (int i = 0; i <= n; ++i) uf_parent[i] = i;

    
    // 간선의 정보 입력
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        edge.push_back({i, u, v, w});
    }


    // 가중치를 기준으로 정렬
    sort(edge.begin(), edge.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });


    // MST
    ll MST_weight = 0LL;
    memset(is_MST_edge, false, sizeof(is_MST_edge));
    for (Edge e : edge) {
        if (find_f(e.u) != find_f(e.v)) {
            union_f(e.u, e.v);
            is_MST_edge[e.index] = true;
            add_edge(e.u, e.v);
            MST_weight += e.w;
        }
    }

    
    // heavy light decomposition
    calculate_subtree_size(1, 1);
    hld_head[1] = 1;
    heavy_ligth_decomposition(1, 0, 1);


    // MST가 아닌 간선 업데이트
    for (Edge e : edge) {
        if (is_MST_edge[e.index]) continue;
        update(e.u, e.v, e.w);
    }


    // 오프라인 쿼리
    for (Edge e : edge) {
        if (is_MST_edge[e.index]) {
            int result = query(e.u, e.v);
            answer[e.index] = (result == INF ? -1 : MST_weight - e.w + result);
        }
        
        else {
            answer[e.index] = MST_weight;
        }
    }

    
    // 정답 출력
    for (int i = 0; i < m; ++i) cout << answer[i] << "\n";
    
    return 0;
}