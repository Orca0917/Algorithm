#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

using namespace std;

int n, m;
char board[1000][1000];
bool occupied[1000][1000];
int dx[] = { 1, -1, 0, 0, 1, -1 };
int dy[] = { 0, 0, 1, -1, 1, 1 };

//비교가 용이하도록 숫자를 1차원 string으로 변환
string number[10] = {
	"**** ** ** ****", //0
	"**  *  *  * ***", //1
	"**   * * *  ***", //2
	"***  * **  ****", //3
	"  * *** ****  *", //4
	"****  **   ****", //5
	"*  *  **** ****", //6
	"***  * * *  *  ", //7
	"**** ***** ****", //8
	"**** ****  *  *"  //9
};

void input() {
	string s;

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
    	//입력에 문제가 생겼던 부분
        //size를 체크해서 다시 입력받는 방식으로 해결했다.
		getline(cin, s);
		if (!s.size()) getline(cin, s);
		for (int j = 0; j < m; j++) {
			board[i][j] = s[j];
		}
	}
}

tuple<int,int,int> bfs() {
	int minx, maxx;
	int curx, cury, nx, ny;
	int retx, rety, maxk = 0;
	queue<pair<int, int>> q;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (occupied[y][x]) continue;
			if (board[y][x] == '*') {
				maxx = x;
				minx = x;
				q.emplace(x, y);
				occupied[y][x] = 1;

				while (!q.empty()) {
					curx = q.front().first;
					cury = q.front().second;
					q.pop();
					
                    //x좌표의 최대, 최소값 갱신
					maxx = max(maxx, curx);
					minx = min(minx, curx);
					for (int i = 0; i < 6; i++) {
						nx = curx + dx[i], ny = cury + dy[i];
						if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
						if (occupied[ny][nx] || board[ny][nx] != '*') continue;

						q.emplace(nx, ny);
						occupied[ny][nx] = 1;
					}
				}
				
				if (maxk < (maxx + 1 - minx) / 3) {
					maxk = (maxx + 1 - minx) / 3;
					retx = minx, rety = y;
				}
			}
		}
	}
	return tie(retx, rety, maxk);
}

int check_number() {
	int sx, sy, k, ret = -1;
	string shape = "";

	tie(sx, sy, k) = bfs();
	for (int y = sy; y < sy + 5 * k; y += k) {
		for (int x = sx; x < sx + 3 * k; x += k) {
			shape.push_back(board[y][x]);
		}
	}

	for (int i = 0; i < 10; i++) {
		if (!number[i].compare(shape)) {
			ret = i; break;
		}
	}

	return ret;
}


void solution() {
	input();
	cout << check_number();
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	solution();

	return 0;
}