#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m; 
int board[51][51];
int board_id[51][51];

int id = 1;
int movement[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

vector<int> result;

bool other_room[2505];
bool vis2[51][51];
int counts[2505];
int answer = 0;


int bfs(int x, int y) {
    queue<pii> q;
    q.push({x, y});
    board_id[x][y] = id;
    int cnt = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        ++cnt;

        for (int i = 0; i < 4; ++i) {
            int bit = (1 << i);
            if (board[x][y] & bit) continue;

            int xx = x + movement[i][0];
            int yy = y + movement[i][1];

            if (board_id[xx][yy]) continue;
            board_id[xx][yy] = id;

            q.push({xx, yy});

        }
    }
    
    return counts[id++] = cnt;
}
 

void bfs2(int x, int y) {
    memset(other_room, false, sizeof(other_room));

    queue<pii> q;
    q.push({x, y});
    vis2[x][y] = true;


    int cur_id = board_id[x][y];
    int cur_size = counts[cur_id];
    other_room[cur_id] = true;

    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int bit = (1 << i);
            int xx = x + movement[i][0];
            int yy = y + movement[i][1];

            if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;


            // 인접한 방
            if (board[x][y] & bit) {
                
                int adj_id = board_id[xx][yy];

                if (other_room[adj_id]) continue;
                other_room[adj_id] = true;

                int room_size = counts[adj_id];
                answer = max(answer, cur_size + room_size);

                continue;
            }


            if (vis2[xx][yy]) continue;
            vis2[xx][yy] = true;

            q.push({xx, yy});
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> m >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    memset(board_id, 0, sizeof(board_id));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (board_id[i][j]) continue;
            int area = bfs(i, j);
            result.push_back(area);
        }

    memset(vis2, false, sizeof(vis2));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (vis2[i][j]) continue;
            bfs2(i, j);
        }
    
    cout << result.size() << "\n";
    cout << *max_element(result.begin(), result.end()) << "\n";
    cout << answer << "\n";

    return 0;
}

 