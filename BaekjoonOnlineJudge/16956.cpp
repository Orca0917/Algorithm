#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int r, c;
string a[500];
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,1,-1 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> r >> c;
	for (int i = 0; i < r; ++i)
		cin >> a[i];

	bool isSheep = false;
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
		{
			if (a[i][j] == 'S') {

				// S 상하좌우에 양이 있다면 0을 출력해야 한다.
				for (int k = 0; k < 4; ++k) {
					int ny = i + dy[k];
					int nx = j + dx[k];

					if (!(0 <= ny && ny < r && 0 <= nx && nx < c)) continue;

					if (a[ny][nx] == 'W')
						isSheep = true;
				}
			}
		}

	if (isSheep)
		cout << 0 << "\n";
	else {
		cout << 1 << "\n";
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j) {

				if (a[i][j] == 'S') {

					for (int k = 0; k < 4; ++k) {
						int ny = i + dy[k];
						int nx = j + dx[k];

						if (!(0 <= ny && ny < r && 0 <= nx && nx < c)) continue;

						if (a[ny][nx] == '.')
							a[ny][nx] = 'D';
					}
				}
			}

		for (int i = 0; i < r; ++i)
			cout << a[i] << "\n";
    }

    return 0;
}