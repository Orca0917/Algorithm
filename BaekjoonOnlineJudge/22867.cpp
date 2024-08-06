#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int to_milisecond(string t) {
    int hour = stoi(t.substr(0, 2));
    int miniute = stoi(t.substr(3, 2));
    int second = stoi(t.substr(6, 2));
    int milisecond = stoi(t.substr(9, 3));

    return hour * 60 * 60 * 1000 + miniute * 60 * 1000 + second * 1000 + milisecond;

}

vector<pii> timetable;
priority_queue<int, vector<int>, greater<int>> parkings;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n; 

    for (int i = 0; i < n; ++i) {
        string departure, arrival;
        cin >> departure >> arrival;
        int departure_ms = to_milisecond(departure);
        int arrival_ms = to_milisecond(arrival);

        timetable.emplace_back(departure_ms, arrival_ms);
    }

    sort(timetable.begin(), timetable.end());

    int answer = 0;
    for (pii information : timetable) {

        // 현재 들어오려는 차 이전의 차들은 모두 빼기
        while (!parkings.empty() && parkings.top() <= information.first) parkings.pop();
        parkings.push(information.second);
        answer = max(answer, (int)parkings.size());
    }

    cout << answer << "\n";

    
    return 0;
}