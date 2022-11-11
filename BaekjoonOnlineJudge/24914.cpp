#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct EDGE {
    int node1;
    int node2;
    int color;
};

int N;  //  정점의 수
int M;  //  색상의 수
int Q;  //  쿼리의 수

map<int, int> color_list[200'001];      // 각 정점과 연결된 간선의 색상 정보를 담음
vector<EDGE> edges;                     // 간선의 정보

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M >> Q;

    edges.resize(N);

    int result = 0;
    for (int i = 1; i < N; ++i) {
        cin >> edges[i].node1 >> edges[i].node2 >> edges[i].color;
        color_list[edges[i].node1][edges[i].color] += 1;
        color_list[edges[i].node2][edges[i].color] += 1;

        ++result;

        // 양 쪽 노드중 한쪽이라도 색상이 같은 간선이 있다면, 조각은 1개 감소
        if (color_list[edges[i].node1][edges[i].color] >= 2) --result;
        if (color_list[edges[i].node2][edges[i].color] >= 2) --result;
    }

    while (Q--) {
        int index, color; cin >> index >> color;
        EDGE &e = edges[index];

        if (color == e.color) goto PRINT;

        // 각 정점에 연결된 색상 1씩 감소
        color_list[e.node1][e.color] -= 1;
        color_list[e.node2][e.color] -= 1;

        // (1) 이어져있던 간선이 둘로 쪼개짐
        if (color_list[e.node1][e.color] > 0 && color_list[e.node2][e.color] > 0) ++result;
        // (2) 연결된 간선이 없던 간선이 사라짐
        if (color_list[e.node1][e.color] == 0 && color_list[e.node2][e.color] == 0) --result;

        // 각 정점에 새롭게 연결된 색상 추가
        color_list[e.node1][color] += 1;
        color_list[e.node2][color] += 1;

        // (1) 이번에 새로운 간선이 추가됨 (연결된 간선 없음)
        if (color_list[e.node1][color] == 1 && color_list[e.node2][color] == 1) ++result;
        // (2) 이번의 간선이 추가됨으로서 양쪽의 간선집합이 합쳐짐
        if (color_list[e.node1][color] >= 2 && color_list[e.node2][color] >= 2) --result;

        e.color = color;
        
    PRINT:
        cout << result << "\n";
    }
    
    return 0;
}