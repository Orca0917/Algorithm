#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 701

using namespace std;

int m_size;
int n_days;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> m_size >> n_days;
    vector<int> worms(m_size * 2, 1);

    // days만큼 진행
    while (n_days--) {
        int index = 0;
        for (int i = 0; i < 3; ++i) {
            int counts; cin >> counts;
            while (counts--) worms[index++] += i;
        }
    }

    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            if (j == 0) cout << worms[m_size - 1 - i] << " ";
            else cout << worms[m_size + j - 1] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}