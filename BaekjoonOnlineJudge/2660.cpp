#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, u, v;
int dist[51][51];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    // 거리정보 무한대로 초기화 (단, 자기자신으로는 0)
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            dist[i][j] = 1e9;
        dist[i][i] = 0;
    }
    
    // 거리정보 입력 (1)
    while (cin >> u >> v) {
        if (u == -1 && v == -1) break;
        dist[u][v] = dist[v][u] = 1;
    }

    // 플로이드 워셜
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    vector<int> result;
    int min_dist = 1e9;

    // 각 사람별로 가장멀리 떨어진 사람은 누구 = 그게 곧 점수가 됨
    for (int i = 1; i <= n; ++i) {
        int max_dist = *max_element(dist[i] + 0, dist[i] + n + 1);
        
        // 새로운 후보의 등장! 기존의 후보는 모두 제거
        if (min_dist > max_dist) {
            min_dist = max_dist;
            result.clear();
        }

        // 후보목록에 추가
        if (min_dist == max_dist) {
            result.push_back(i);
        }
    }

    cout << min_dist << " " << (int)result.size() << "\n";
    sort(result.begin(), result.end());
    for (int e : result) cout << e << " ";
    
    return 0;
}