#include <iostream>
#include<queue>
#include<cmath> 
#include<limits>
using namespace std;

const int INF = 1000;
int n,s,t,c;
int totaledge;
int head[100];
int d[200];
int f[5000];

struct {
	int v, cap, nxt;
}edge[5000];

void cleargraph() {
	totaledge = 0;
	memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int cap) {
	edge[totaledge].v = v;
	edge[totaledge].cap = cap;
	edge[totaledge].nxt = head[u];
	head[u] = totaledge;
	totaledge++;
}

bool bfs(int s, int t) {
	int u, v;
	memset(d, -1, sizeof(d));
	queue<int> temp;
	while (!temp.empty()) {
		temp.pop();
	}
	temp.push(s);
	d[s] = 0;//start point of path
	while (!temp.empty()) {
		u = temp.front();
		temp.pop();
		for (int e = head[u]; e != -1; e = edge[e].nxt) {
			v = edge[e].v;
			if ((d[v] == -1) && edge[e].cap > f[e]) {
				d[v] = d[u] + 1;
				temp.push(v);
			}
		}

	}
	return d[t]>=0;
}

int dinic(int s, int t, int sum) {
	if (s == t)
		return sum;
	int v, tp = sum;
	for (int e = head[s]; e != -1 && sum; e = edge[e].nxt) {
		v = edge[e].v;
		if (d[v] == d[s] + 1 && edge[e].cap > f[e]) {
			int canflow = dinic(v, t, min(sum, edge[e].cap - f[e]));
			f[e] += canflow;
			f[e + 1] -= canflow;
			sum -= canflow;
		}
	}
	return (tp-sum);
}

int maxFlow(int s,int t) {
	int sum = 0;
	while (bfs(s,t)) {
		sum += dinic(s, t, INF);
	}
	return sum;
}
int main() {
	cin >> n;
	queue<int> result;
	while (!cin.eof()&&n!=0) {
		cleargraph();
		cin >> s >> t >> c;
		
		int tempu, tempv, tempcap;
		for (int i = 0; i < c; i++) {
			cin >> tempu, tempv, tempcap;
			addEdge(tempu, tempv, tempcap);
			addEdge(tempv, tempu, tempcap);
		}
		result.push(maxFlow(s,t));
		cin >> n;
	}

	int count = 1;;
	while (!result.empty()) {
		cout << "Network " << count << endl;
		cout<<"The bandwidth is "<<result.front()<<"."<<endl;
		result.pop();
	}

	return 0;
}
