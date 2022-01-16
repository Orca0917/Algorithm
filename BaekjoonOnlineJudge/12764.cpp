#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;

const int MAX = 100000;


int N;

pii arr[MAX];

set<int> save; //자동 정렬

int result[MAX];



int solve()

{

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //minHeap

        int seat = 0; //컴퓨터 좌석

 

        for (int i = 0; i < N; i++)

        {

                 while (!pq.empty())

                 {

                         //현재 시작 시간보다 빠른 사람들 pop

                         if (pq.top().first <= arr[i].first)

                         {

                                 save.insert(pq.top().second);

                                 pq.pop();

                         }

                         else

                                 break;

                 }

                 //남는 자리 없는 경우: 다음 번호의 컴퓨터를 준다

                 if (save.empty())

                 {

                         pq.push({ arr[i].second, seat });

                         result[seat]++;

                         seat++;

                 }

                 //set의 첫 번째 원소를 자리로 배정

                 else

                 {

                         auto idx = save.begin();

                         pq.push({ arr[i].second, *idx });

                         result[*idx]++;

                         save.erase(idx);

                 }

        }

       

        return seat;

}


int main()

{

        ios_base::sync_with_stdio(0);

        cin.tie(0);

        cin >> N;

 

        for (int i = 0; i < N; i++)
                 cin >> arr[i].first >> arr[i].second;

        sort(arr, arr + N);

 

        int seat = solve();

        cout << seat << "\n";

        for (int i = 0; i < seat; i++)
                 cout << result[i] << " ";
        cout << "\n";
        return 0;


}
