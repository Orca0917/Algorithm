#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> powerOf2;
typedef long long ll;

int solve(string number, string target) {
	int np = 0;
	int tp = 0;
	int takeCnt = 0;
	
	while (np < number.length() && tp < target.length())
	{
		if (number[np] == target[tp]) {
			takeCnt++;
			++tp;
		}
		++np;
	}
	
	
	return number.length() - takeCnt + target.length() - takeCnt;
}

int main() {
	
	int testcase;
	cin >> testcase;
	
	for (ll i = 1; i <= (ll)2e18; i *= 2) 
		powerOf2.push_back(to_string(i));
		
	while (testcase--) {
		string number;
		cin >> number;
		int answer = number.length() + 1;
		for (auto target : powerOf2)
			answer = min(answer, solve(number, target));
			
		cout << answer << "\n";
	}
	
	return 0;
}