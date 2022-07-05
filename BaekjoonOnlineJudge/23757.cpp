#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m; // 선물 상자의 수, 아이들의 수
priority_queue<int> pq;

vector<int> w;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    
    w.resize(m);

    for (int i = 0; i < n; ++i) {
        int present_size; cin >> present_size;
        pq.push(present_size);
    }

    for (int &element : w) cin >> element;

    int answer = 1;
    for (int want : w) {
        int top_elem = pq.top();
        pq.pop();

        if (top_elem < want) {
            answer = 0;
            break;
        }

        top_elem -= want;
        pq.push(top_elem);
    }
    
    cout << answer << "\n";
    return 0;
}