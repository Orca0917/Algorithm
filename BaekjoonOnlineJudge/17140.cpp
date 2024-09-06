#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int r, c, k;
int arr[100][100];

int sort_and_update(vector<int> &line) {
    map<int, int> m;
    for (int x : line) if (x != 0) m[x] += 1;
    
    vector<pii> v(m.begin(), m.end());
    sort(v.begin(), v.end(), [](const pii &a, const pii &b) -> bool {
        if (a.second == b.second)
            return a.first < b.first;
        return a.second < b.second;
    });

    line.clear();
    for (const auto &p : v) {
        line.push_back(p.first);
        line.push_back(p.second);
    }

    return min((int)line.size(), 100);
}

void process(int &n_row, int &n_col, bool is_row_operation) {
    int new_size = 0;

    if (is_row_operation) {
        for (int i = 0; i < n_row; ++i) {
            vector<int> row(arr[i], arr[i] + n_col);
            int new_length = sort_and_update(row);
            
            for (int j = 0; j < 100; ++j) arr[i][j] = 0;
            for (int j = 0; j < new_length; ++j) arr[i][j] = row[j];
            new_size = max(new_size, new_length);
        }
        n_col = new_size;
    } 
    
    else {
        for (int j = 0; j < n_col; ++j) {
            vector<int> col;
            for (int i = 0; i < n_row; ++i) col.push_back(arr[i][j]);
            int new_length = sort_and_update(col);

            for (int i = 0; i < 100; ++i) arr[i][j] = 0;
            for (int i = 0; i < new_length; ++i) arr[i][j] = col[i];
            new_size = max(new_size, new_length);
        }
        n_row = new_size;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> r >> c >> k;

    int n_row = 3, n_col = 3;

    for (int i = 0; i < 3; ++i) 
        for (int j = 0; j < 3; ++j)
            cin >> arr[i][j];

    int _time = 0;
    while (arr[r - 1][c - 1] != k && _time <= 100) {
        
        if (n_row >= n_col) process(n_row, n_col, true);
        else process(n_row, n_col, false);

        ++_time;
    }

    if (_time > 100) _time = -1;
    cout << _time;
    
    return 0;
}
