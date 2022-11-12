#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 200'001
using namespace std;

struct EDGE {
    int node1;
    int node2;
    int color;
};

int N;
int M;
int Q;

vector<EDGE> edges;
map<int, int> color_list[MAX];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M >> Q;

    int result = N - 1;
    edges.resize(N + 1);

    for (int index = 1; index < N; ++index) {
        cin >> edges[index].node1 >> edges[index].node2 >> edges[index].color;

        int u = edges[index].node1;
        int v = edges[index].node2;
        int c = edges[index].color;

        if (color_list[u].find(c) != color_list[u].end()) --result;
        if (color_list[v].find(c) != color_list[v].end()) --result;

        color_list[u][c] += 1;
        color_list[v][c] += 1;
    }

    while (Q--) {
        int index, color; cin >> index >> color;

        int u = edges[index].node1;
        int v = edges[index].node2;
        int c = edges[index].color;

        // 각 노드에 저장된 c 색상 1씩 감소
        color_list[u][c] -= 1;
        color_list[v][c] -= 1;

        // 연결된 색상이 단 하나 뿐이었던 것이 제거 됨 (조각 1개 감소)
        if (color_list[u][c] == 0 && color_list[v][c] == 0) --result;
        else if (color_list[u][c] > 0 && color_list[v][c] > 0) ++result;

        // 각 노드에 저장된 color 색상 1씩 증가
        color_list[u][color] += 1;
        color_list[v][color] += 1;

        // 두 노드 모두 이번 색상이 처음으로 삽입된 것이라면 조각 1개 증가
        if (color_list[u][color] == 1 && color_list[v][color] == 1) ++result;
        else if (color_list[u][color] > 1 && color_list[v][color] > 1) --result;


        cout << result << "\n";
    }
    
    return 0;
}