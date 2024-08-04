#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

char board[501][501];
int answer[501][501];
bool vis[501][501];
int n, m;

// 주어진 문자에 맞게 이동
pii dir_to_mv(char c) {
    if (c == 'U') return make_pair(-1, 0);
    else if (c == 'D') return make_pair(1, 0);
    else if (c == 'R') return make_pair(0, 1);
    else if (c == 'L') return make_pair(0, -1);
}


int solve(int x, int y) {

    // 밖으로 탈출하게 되는 경우
    if (x < 0 || x >= n || y < 0 || y >= m) return 1;

    // 계속해서 순환하게 되는 경우
    if (vis[x][y] && answer[x][y] == -1) return 0;

    // 이미 이 곳을 방문해서 결과를 얻은 적이 있는 경우?
    int &ret = answer[x][y];
    if (ret != -1) return ret;
    
    // 순환을 판단하기 위해 방문 처리
    vis[x][y] = true;

    // 다음 지역!
    char value = board[x][y];
    int nx = x + dir_to_mv(value).first;
    int ny = y + dir_to_mv(value).second;

    // dp
    return answer[x][y] = solve(nx, ny);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 행, 열
    cin >> n >> m;

    // 보드 입력
    for (int i = 0; i < n; ++i)
        for (int  j = 0 ; j < m; ++j)
            cin >> board[i][j];

    // 방문 및 정답 정보 초기화
    memset(vis, false, sizeof(vis));
    memset(answer, -1, sizeof(answer));

    // 정답 탐색 (DP)
    int result = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            result += solve(i, j);

    // 정답 출력
    cout << result << "\n";
    
    return 0;
}