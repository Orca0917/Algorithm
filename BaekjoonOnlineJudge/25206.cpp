#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string name, grade;
    double score;

    map<string, double> gr2sc;
    gr2sc["A+"] = 4.5;
    gr2sc["A0"] = 4.0;
    gr2sc["B+"] = 3.5;
    gr2sc["B0"] = 3.0;
    gr2sc["C+"] = 2.5;
    gr2sc["C0"] = 2.0;
    gr2sc["D+"] = 1.5;
    gr2sc["D0"] = 1.0;
    gr2sc["F"] = 0.0;

    double sum = 0, cnt = 0;
    while (cin >> name >> score >> grade) {
        if (grade == "P") continue;

        sum += score * gr2sc[grade];
        cnt += score;
    }

    cout.precision(6);
    cout << fixed << sum / cnt;

    return 0;
}