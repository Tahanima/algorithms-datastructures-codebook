#include <bits/stdc++.h>

using namespace std;

/*********************************************************************************************
 
 Given a grid consisting of the characters '.' and '*', find the number of connected components 
 consisting of the character '*'. The cells (x - 1, y), (x, y + 1), (x, y - 1), (x + 1, y) are
 directly connected with the cell (x, y).

 Input:
 4 4
 .*..
 **..
 ...*
 ...*

 Output:
 2

*********************************************************************************************/

const int MX = 10; 
typedef pair<int, int> pii;
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};
char G[MX];
int r, c;
bool grid[MX][MX], vis[MX][MX];

bool in_boundary(int i, int j){
	return (i >= 0 && i < r && j >= 0 && j < c);
}

void bfs(int i, int j){
	vis[i][j] = true;
	queue<pii> q;
	q.push(pii(i, j));

	for(; !q.empty() ;){
		pii u = q.front(); q.pop();

        for(int i = 0; i < 4; i++){
        	int ux = u.first + dx[i];
        	int uy = u.second + dy[i];

        	if(!in_boundary(ux, uy)) continue;
        	if(vis[ux][uy] || !grid[ux][uy]) continue;

        	q.push(pii(ux, uy));
        	vis[ux][uy] = true;
        }
	}
}

int main(){
	scanf("%d %d", &r, &c);
    
    for(int i = 0; i < r; i++){
    	scanf("%s", G);
    	for(int j = 0; j < c; j++){
           grid[i][j] = (G[j] == '.') ? false : true;
    	}
    }

    int num_of_components = 0;
    memset(vis, false, sizeof(vis));

    for(int i = 0; i < r; i++){
    	for(int j = 0; j < c; j++){
    		if(!grid[i][j]) continue;
    		if(!vis[i][j]){
    			num_of_components++;
                bfs(i, j);
    		}
    	}
    }

    printf("%d\n", num_of_components);
	return 0;
}