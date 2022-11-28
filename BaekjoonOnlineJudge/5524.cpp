#include <bits/stdc++.h>

using namespace std;

char to_lower(char c) {
	if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
	else return c;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int n; cin >> n;
	while (n--) {
		string s; cin >> s;
		for (char c : s) cout << to_lower(c);
		cout << "\n";
	}
}
