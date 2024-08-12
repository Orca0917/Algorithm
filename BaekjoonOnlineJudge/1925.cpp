#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<pii> p(3);
vector<int> lengths;

string solve() {

    // 세 점이 일직선 상에 위치하는 경우
    if (sqrt(lengths[0]) + sqrt(lengths[1]) - sqrt(lengths[2]) < 1e-9) {
        return "X";
    }

    // 세 변의 길이가 같은 경우
    if (lengths[0] == lengths[1] && lengths[1] == lengths[2])
        return "JungTriangle";


    // 가장 큰 각이 90보다 큰 경우
    if (lengths[2] > lengths[0] + lengths[1]) 
        return (lengths[0] == lengths[1] ? "Dunkak2Triangle" : "DunkakTriangle");

    // 가장 큰 각이 90 인 경우
    if (lengths[2] == lengths[0] + lengths[1]) 
        return (lengths[0] == lengths[1] ? "Jikkak2Triangle" : "JikkakTriangle");

    // 가장 큰 각이 90 보다 작은 경우
    if (lengths[2] < lengths[0] + lengths[1]) 
        return (lengths[0] == lengths[1] || lengths[1] == lengths[2] ? "Yeahkak2Triangle" : "YeahkakTriangle");
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (pii &e : p) cin >> e.first >> e.second;

    for (int i = 0; i < 3; ++i)
        for (int j = i + 1; j < 3; ++j)
            lengths.push_back(pow(p[i].first - p[j].first, 2) + pow(p[i].second - p[j].second, 2));
    sort(lengths.begin(), lengths.end());

    cout << solve();
    
    return 0;
}