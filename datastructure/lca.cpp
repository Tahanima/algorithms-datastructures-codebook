#include <bits/stdc++.h>
using namespace std;

/*********************************************************************************************
Given a tree and some queries of the format u v, find the lowest common ancestor of u and v.

         0---1---2---3---8
         |   |   |
         |   |   |
         7   5   4
             |
             |
             6---9

 Input:
 10
 0 1
 0 7
 1 2
 1 5
 2 3
 2 4
 3 8
 5 6
 6 9
 5
 8 9
 8 4
 8 0
 4 9
 4 5

 Output:
 Lowest common ancestor of 8 and 9 is: 1
 Lowest common ancestor of 8 and 4 is: 2
 Lowest common ancestor of 8 and 0 is: 0
 Lowest common ancestor of 4 and 9 is: 1
 Lowest common ancestor of 4 and 5 is: 1

*********************************************************************************************/

const int N = 1e5 + 5;
const int LOGN = 20;
vector<int> G[N];
int n, q, level[N], par[LOGN][N];

void dfs(int u){
	int sz = G[u].size();
	for(int i = 0; i < sz; i++){
		int v = G[u][i];
        if(par[0][u] != v){
        	par[0][v] = u;
        	level[v] = level[u] + 1;
            dfs(v);
        }
	}
}

void preprocess(){
	level[0] = 0;
	par[0][0] = 0;
	dfs(0);
	for(int i = 1; i < LOGN; i++){
		for(int j = 0; j < n; j++){
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
}

int lca(int p, int q){
	if(level[p] > level[q]) swap(p, q);
    int dist = level[q] - level[p];
    for(int i = 0; i < LOGN; i++){
    	if(dist >= (1 << i)){
    		q = par[i][q];
    		dist -= (1 << i);
    	}
    }

    if(p == q) return p;
    for(int i = LOGN - 1; i >= 0; i--){
    	if(par[i][p] != par[i][q]){
    		p = par[i][p], q = par[i][q];
    	}
    }

    return par[0][p];
}

int main(){
	int u, v;
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++){
		scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
	}

	scanf("%d", &q);
	preprocess();
	for(int i = 0; i < q; i++){
		scanf("%d %d", &u, &v);
		printf("Lowest common ancestor of %d and %d is: %d\n", u, v, lca(u, v));
	}
	return 0;
}