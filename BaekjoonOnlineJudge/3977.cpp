#include <bits/stdc++.h>

using namespace std;

int n; // 구역의 수 (정점)
int m; // 움직임의 수 (간선)

vector<int> adj[100001]; // 입력으로 받는 그래프
vector<int> sccGraph[100001]; // SCC로 재구성한 그래프
vector<int> inDegree(100001, 0); // sccGraph의 indegree를 기록

vector<int> sccID(100001, -1), discovered(100001, -1);
int sccNum = 0, vertexNum = 0;

// 하나의 SCC로 묶기 위한 스택
stack<int> st;

int scc(int here) {
    int ret = discovered[here] = vertexNum++;
    st.push(here);

    for (int there : adj[here]) {
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        else if (sccID[there] == -1)
            ret = min(ret, discovered[there]);
    }

    if (ret == discovered[here]) {
        while (true) {
            int now = st.top(); st.pop();
            sccID[now] = sccNum;
            if (now == here) break;
        }
        ++sccNum;
    }

    return ret;
}

vector<int> tarjanSCC() {
    for (int vertex = 0; vertex < n; ++vertex) {
        if (discovered[vertex] == -1)
            scc(vertex);
    }

    // SCC그래프 생성
    for (int vertex = 0; vertex < n; ++vertex) {
        for (int there : adj[vertex]) {
            if (sccID[vertex] != sccID[there]) {
                sccGraph[vertex].push_back(sccID[there]);
                ++inDegree[sccID[there]];
            }
        }
    }

    // inDegree 검사
    vector<int> zeroIndegree;
    for (int i = 0; i < sccNum; ++i) {
        if (inDegree[i] == 0) {
            zeroIndegree.push_back(i);
        }
    }

    return zeroIndegree;
}

int main() {
    // 빠른 입출력
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        // 테스트 케이스 마다 초기화 되어야 하는 변수
        fill(sccID.begin(), sccID.end(), -1);
        fill(discovered.begin(), discovered.end(), -1);
        fill(inDegree.begin(), inDegree.end(), 0);
        for (int i = 0; i < 100001; ++i) { adj[i].clear(); sccGraph[i].clear(); }

        sccNum = 0, vertexNum = 0;

        cin >> n >> m;

        for (int i = 0; i < m; ++i) {
            int from, to; cin >> from >> to;
            adj[from].push_back(to);
        }

        vector<int> zeroIndegree = tarjanSCC();
        if (zeroIndegree.size() == 1) {
            for (int v = 0; v < n; ++v) 
                if (sccID[v] == zeroIndegree[0])
                    cout << v << "\n";
        } else {
            cout << "Confused\n";
        }

        cout << "\n";
    }

}