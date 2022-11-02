#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct BIRTH {
    string name;
    int year;
    int month;
    int day;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<BIRTH> birth(n);

    for (auto &e : birth)
        cin >> e.name >> e.day >> e.month >> e.year;

    sort(birth.begin(), birth.end(), [](BIRTH &a, BIRTH &b) {
        if (a.year == b.year) {
            if (a.month == b.month) return a.day < b.day;
            return a.month < b.month;
        }
        return a.year < b.year;
    });

    cout << birth.back().name << "\n" << birth.front().name << "\n";

    
    return 0;
}