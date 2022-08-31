#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int> 


using namespace std;


int dist[301][301];

int solution(int alp, int cop, vector<vector<int>> problems) {

    int max_alg = 0, max_cod = 0;
    for (vector<int> problem : problems) {
        max_alg = max(max_alg, problem[0]);
        max_cod = max(max_cod, problem[1]);
    }

    cout << max_alg << ", " << max_cod << "\n";

    int answer = 0;
    memset(dist, -1, sizeof(dist));

    priority_queue<pair<int, pii>> pq;
    pq.push({0, {alp, cop}});
    dist[alp][cop] = 0;

    while (!pq.empty()) {
        int alg = pq.top().second.first;
        int cod = pq.top().second.second;
        int time = -pq.top().first;
        pq.pop();

        if (dist[alg][cod] > time) continue;

        if (alg >= max_alg && cod >= max_cod) {
            answer = time;
            break;
        }

        // 시간 1을 소모해서 알고력을 1 높이기
        if (alg < max_alg && dist[alg + 1][cod] == -1 || dist[alg + 1][cod] > time + 1) {
            dist[alg + 1][cod] = time + 1;
            pq.push({-(time + 1), {alg + 1, cod}});
        }

        // 시간 1을 소모해서 코딩력을 1 높이기
        if (cod < max_cod && dist[alg][cod + 1] == -1 || dist[alg][cod + 1] > time + 1) {
            dist[alg][cod + 1] = time + 1;
            pq.push({-(time + 1), {alg, cod + 1}});
        }

        // 문제를 해결해서 알고력과 코딩력 높이기
        for (vector<int> problem : problems) {
            // 문제를 풀 수 없는 경우
            if (alg < problem[0] || cod < problem[1]) continue;

            int new_alg = alg + problem[2];
            int new_cod = cod + problem[3];
            int new_time = time + problem[4];

            new_alg = min(max_alg, new_alg);
            new_cod = min(max_cod, new_cod);

            if (dist[new_alg][new_cod] == -1 || dist[new_alg][new_cod] > new_time) {
                dist[new_alg][new_cod] = new_time;
                pq.push({-new_time, {new_alg, new_cod}});
            }
        }
    }

    return answer;
}
