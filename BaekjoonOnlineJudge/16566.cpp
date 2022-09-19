#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 4'000'001

using namespace std;

vector<int> parent(MAX);
vector<int> arr;

int find_f(int x) {
    if (parent[x] == x) return x;
    else return find_f(parent[x]);
}

void union_f(int x, int y) {
    x = find_f(x);
    y = find_f(y);

    if (x != y) parent[x] = y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (int i = 1; i < MAX; ++i) parent[i] = i;

    int n, m, k; cin >> n >> m >> k;

    arr.resize(m);
    for (int &e : arr) cin >> e;
    sort(arr.begin(), arr.end());
    
    while (k--) {
        int chulsu; cin >> chulsu;
        int index = upper_bound(arr.begin(), arr.end(), chulsu) - arr.begin();
        index = find_f(index);

        cout << arr[index] << "\n";
        union_f(index, index + 1);
    }
    
    return 0;
}