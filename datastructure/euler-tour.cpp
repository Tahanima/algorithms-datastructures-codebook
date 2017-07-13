#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;
vector<int> G[MX];
int _time, tin[MX], tout[MX], vis[MX], tree[MX], Arr[MX];

void dfs(int u, int par){
	vis[++_time] = u;
	tin[u] = _time;
	for(int v: G[u]){
		if(v == par) continue;
        dfs(v, u);
	}
	tout[u] = _time;
}

void update(int id, int val){
	for(; id < MX ; tree[id] += val, id += id & -id);
}

int query(int id){
	int sum = 0;
	for(; id > 0 ; sum += tree[id], id -= id & -id);
	return sum;
}

int main(){
	int N, M, Q, u, v;
	cin >> N >> M >> Q;
	for(int i = 1; i <= N; i++){
		cin >> Arr[i];
	}

	for(int i = 1; i <= M; i++){
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	_time = 0;
	dfs(1, 1);
	
	for(int i = 1; i <= N; i++){
		update(i, Arr[vis[i]]);
	}

	for(int i = 1; i <= Q; i++){
		cin >> u;
		int Ans = query(tout[u]) - query(tin[u] - 1);
		cout << Ans << endl;
	}

	return 0;
}