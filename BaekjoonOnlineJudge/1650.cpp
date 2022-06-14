#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1002
#define INF 1e9
using namespace std;

struct Edge{
	int to, capacity, dist, flow;
	Edge *dual;
	
    Edge(): Edge(-1, -1, -1) {
        // pass
    }

	Edge(int to1, int c1, int d1): to(to1), capacity(c1), dist(d1){
		flow = 0;
		dual = nullptr;
	}

	int spare() { 
        return capacity - flow; 
    }

	int distance() { 
        return (flow < 0 ? -dist : dist);
    }


	void addFlow(int f1) {
		flow += f1;
		dual->flow -= f1;
	}
};

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	vector<Edge*> edge, adj[1000];
	for(int i = 0; i < M; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		u--; v--;
		Edge *e1 = new Edge(v, 1, w), *e2 = new Edge(u, 1, w);
		e1->dual = e2; e2->dual = e1;
		edge.push_back(e1); edge.push_back(e2);
		adj[u].push_back(e1); adj[v].push_back(e2);
	}

    int source = 0, sink = N - 1;

	int result = 0;
	for(int i=0; i<2; i++){
		int dist[1000];
		Edge *parent[1000] = {0};
		bool inQ[1000] = {0};
		queue<int> Q;
		fill(dist, dist + N, INF);

		dist[source] = source;
		inQ[source] = true;
		Q.push(source);

		while(!Q.empty()){
			int curr = Q.front();
			Q.pop();
			inQ[curr] = false;
			for(auto *e: adj[curr]){
				int next = e -> to, d = e -> distance();
				if(e->spare() > 0 && dist[next] > dist[curr] + d){
					dist[next] = dist[curr] + d;
					parent[next] = e;
					if(!inQ[next]){
						inQ[next] = true;
						Q.push(next);
					}
				}
			}
		}
		for(int node = sink; node != source; node = parent[node] -> dual -> to){
			result += parent[node]->distance();
			parent[node]->addFlow(1);
		}
	}
	printf("%d\n", result);
}