#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 701

using namespace std;

int m_size;
int n_days;
int worms[MAX][MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> m_size >> n_days;
    for (int i = 0; i < m_size; ++i)
        for (int j = 0; j < m_size; ++j)
            worms[i][j] = 1;

    // days만큼 진행
    while (n_days--) {

        int counts[3];
        for (int i = 0; i < 3; ++i) cin >> counts[i];
        int cnt_idx = 0;

        for (int i = m_size - 1; i >= 0; --i) {
            while (counts[cnt_idx] == 0) ++cnt_idx;
            worms[i][0] += cnt_idx;
            counts[cnt_idx]--;
        }

        for (int j = 1; j < m_size; ++j) {
            while (counts[cnt_idx] == 0) ++cnt_idx;
            worms[0][j] += cnt_idx;
            counts[cnt_idx]--;
        }
    }

    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            if (j == 0) cout << worms[i][j] << " ";
            else cout << worms[0][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}