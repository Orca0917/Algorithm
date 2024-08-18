#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

char student[25];
int movement[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int answer = 0;

int solve(vector<int> &bits) {

    // bits를 각 좌석으로 생각하고, 좌석들이 모두 연결되어 있는지 확인한다.
    vector<bool> vis(26, false);
    map<char, int> grp;

    // 선택한 좌석 7개중 아무거나 시작지점으로 해보자 (선택됨: bits[i] == true)
    int start = 0;
    for (start = 0; start < 25 && !bits[start]; ++start) ;
    
    // BFS로 상하좌우 인접한 것 선택 (단, 선택된 좌석만 갈 수 있음)
    queue<int> q;
    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        grp[student[cur]] += 1;

        // index를 좌표로 변환
        int cur_x = cur / 5;
        int cur_y = cur % 5;

        // 인접한 상하좌우 탐색하기
        for (int i = 0; i < 4; ++i) {
            int nxt_x = cur_x + movement[i][0];
            int nxt_y = cur_y + movement[i][1];
            int nxt = nxt_x * 5 + nxt_y;

            if (nxt_x < 0 || nxt_x >= 5 || nxt_y < 0 || nxt_y >= 5) continue;
            if (vis[nxt] || !bits[nxt]) continue;

            q.push(nxt);
            vis[nxt] = true;
        }
    }

    // 결과로 7좌석 모두 확인되어야 하며(인접함) + 다솜파의 인원이 더 많아야 함
    return grp['S'] > grp['Y'] && grp['S'] + grp['Y'] == 7;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 여학생들의 자리표 입력받기
    for (int i = 0; i < 25; ++i) cin >> student[i];
    
    // 25자리 중 7좌석을 선택하는 모든 조합을 생성해보자
    vector<int> bits;
    bits.insert(bits.end(), 18, 0);
    bits.insert(bits.end(), 7, 1);

    // STL next_permutation을 활용하여 모든 조합 생성
    do {
        answer += solve(bits);
    } while (next_permutation(bits.begin(), bits.end()));
    
    cout << answer;

    return 0;
}