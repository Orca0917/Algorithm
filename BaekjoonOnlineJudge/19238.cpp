#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 22

#define ROAD 0
#define WALL 1
#define PASSENGER 2

using namespace std;

struct position {
    int x;
    int y;
};


int n, m, fuel; // 맵의 크기, 승객의 수, 연료의 양
int movement[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

position destination[MAX][MAX]; // 승객의 도착지 정보
int board[MAX][MAX]; // 백준의 활동 영역 지도

position get_best_passenger(vector<position> &candidates) {

    sort(candidates.begin(), candidates.end(), [](const position &p1, const position &p2) -> bool {
        if (p1.x == p2.x) return p1.y < p2.y;
        else return p1.x < p2.x;
    });

    return candidates.front();
}

int get_dist(position start, position end) {
    bool visited[MAX][MAX];
    memset(visited, false, sizeof(visited));
    
    queue<pair<position, int>> q;
    q.push({start, 0});
    visited[start.x][start.y] = true;
    
    while (!q.empty()) {
        position here = q.front().first;
        int move_cnt = q.front().second;
        q.pop();

        if (here.x == end.x && here.y == end.y) return move_cnt;

        for (int i = 0; i < 4; ++i) {
            int there_x = here.x + movement[i][0];
            int there_y = here.y + movement[i][1];

            if (there_x < 1 || there_y < 1 || there_x > n || there_y > n) continue;
            if (board[there_x][there_y] == WALL) continue;
            if (visited[there_x][there_y]) continue;
            visited[there_x][there_y] = true;

            q.push({{there_x, there_y}, move_cnt + 1});
        }
    }

    return -1;
}
bool drive(position &driver) {

    // 해당 지역을 방문했는지 check
    bool vis[MAX][MAX];
    memset(vis, false, sizeof(vis));
    
    // {현재 위치, 이동횟수}
    queue<pair<position, int>> q;
    q.push({driver, 0});
    vis[driver.x][driver.y] = true;

    // 다음 후보 승객들 목록
    vector<position> candidate_passenger;

    int min_dist = -1;
    while (!q.empty()) {
        position cur_pos = q.front().first; 
        int move_cnt = q.front().second;
        q.pop();

        if (min_dist != -1 && move_cnt > min_dist) break;

        // 현재 도착 지점에 승객이 존재하는 경우!!
        if (board[cur_pos.x][cur_pos.y] == PASSENGER) {

            if (min_dist == -1) {
                min_dist = move_cnt;

                // 가장 가까운 승객마저도 갈 수 없는 경우
                if (fuel < min_dist) return false;
            }

                
            if (min_dist == move_cnt) candidate_passenger.push_back(cur_pos);
            else break;
        
            continue;
        }


        // 상 하 좌 우 탐색
        for (int i = 0; i < 4; ++i) {
            position next_pos;
            next_pos.x = cur_pos.x + movement[i][0];
            next_pos.y = cur_pos.y + movement[i][1];
            
            // Cond.1 활동 반경 밖으로 벗어난 경우 + 벽으로는 이동할 수 없음
            if (next_pos.x < 1 || next_pos.y < 1 || next_pos.x > n || next_pos.y > n) continue;

            // Cond.2 벽으로 이동할 수 없음
            if (board[next_pos.x][next_pos.y] == WALL) continue;

            // Cond.3 이미 방문한 지역 check
            if (vis[next_pos.x][next_pos.y]) continue;
            vis[next_pos.x][next_pos.y] = true;

            q.push({next_pos, move_cnt + 1});
        }
    }

    // 승객에 절대 도달할 수 가 없는 경우
    if (candidate_passenger.empty()) return false;

    // 가장 가까운 거리의 승객에게 이동하는데 사용한 연료
    fuel -= min_dist;

    // 승객이 여러명인 경우 -> 가장 행, 열 작은 순
    position best_passenger = get_best_passenger(candidate_passenger);
    
    // 현재 승객의 자리를 도로로 변경 (처리 완료 표시)
    board[best_passenger.x][best_passenger.y] = ROAD;
    position dest = destination[best_passenger.x][best_passenger.y];

    // 승객의 출발지 ~ 도착지의 거리
    int to_destination = get_dist(best_passenger, dest);
    if (to_destination == -1) return false; // 택시를 타고 도달할 수 없는 지역에 도착지가 존재
    fuel -= to_destination;

    // 도착지로 가는중에 연료를 모두 소진하여 도달할 수 없음
    if (fuel < 0) return false;

    // 도착지에 도달하여 이동 거리 x 2 만큼의 연료 충전
    fuel += to_destination * 2;

    driver = dest;


    --m;

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 입력 : 맵의 크기, 승객 수, 연료
    cin >> n >> m >> fuel;

    // 입력 : 백준의 활동 영역 지도
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n ;++j)
            cin >> board[i][j];

    // 입력 : 백준의 초기 위치
    position driver; // 백준의 위치
    cin >> driver.x >> driver.y;

    // 입력 : 승객의 출발지와 도착지 정보
    for (int i = 0; i < m; ++i) {
        position start, end;
        cin >> start.x >> start.y >> end.x >> end.y;

        destination[start.x][start.y] = end;
        board[start.x][start.y] = PASSENGER;
    }

    // 백준의 택시 운행
    int answer = 0;
    while (fuel && m) {
        bool result = drive(driver);
        if (result == false) {
            answer = -1;
            break;
        }
    }

    // 출력 1 : 연료가 부족하여 목적지에 도달하지 못하거나, 모든 승객을 처리하지 못한 경우 = -1
    // 출력 2 : 연료가 0 이상이며, 모든 승객을 처리한 경우 = 남은 연료의 양 출력    
    if (answer == -1 || m > 0) cout << answer << "\n";
    else cout << fuel << "\n";

    return 0;
}