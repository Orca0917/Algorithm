#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> books;
    int book;
    for (int i = 0; i < n; ++i) {
        cin >> book;
        if (books.empty() || books.back() < book) books.emplace_back(book);
        else {
            auto it = lower_bound(books.begin(), books.end(), book);
            *it = book;
        }
    }

    cout << n - books.size() << "\n";
    return 0;
}