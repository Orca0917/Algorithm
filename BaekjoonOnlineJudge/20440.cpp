#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<pii> mosquito_time(n);
    for (pii &mosquito : mosquito_time)
        cin >> mosquito.first >> mosquito.second;
    sort(mosquito_time.begin(), mosquito_time.end());

    priority_queue<int, vector<int>, greater<int>> pq;

    int max_mosquito = 0;
    pii t;

    for (int i = 0; i < n; ++i) {
        int insert_time_in = mosquito_time[i].first;
        int insert_time_out = mosquito_time[i].second;

        // 다음으로 들어오는 모기 이전에 나가는 애들 다 빼기
        while (!pq.empty() && pq.top() <= insert_time_in) {
            pq.pop();
        }

        // 이번에 들어온 모기 count
        pq.push(insert_time_out);

        // 현재 시점이 최대 모기?
        if (max_mosquito < pq.size()) {
            max_mosquito = pq.size();
            t.first = insert_time_in;
            t.second = pq.top();
        } else if (max_mosquito == pq.size() && t.second == insert_time_in) {
            t.second = pq.top();
        }
    }

    cout << max_mosquito << "\n";
    cout << t.first << " " << t.second << "\n";
    return 0;
}