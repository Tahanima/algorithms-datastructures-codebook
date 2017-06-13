#include <bits/stdc++.h>
using namespace std;

/*********************************************************************************************
 
 Given an array with N elements, indexed from 1 to N. Now you will be given some queries 
 in the form I J, your task is to find the minimum value from index I to J. 

 The first line contains N. Then the next line contains N space separated integers. The next
 line contains Q, the number of queries. The next Q lines will contain a query which is in the 
 form I J (1 ≤ I ≤ J ≤ N).

 Input:
 5
 78 1 22 12 3
 3
 1 2
 3 5
 4 4

 Output:
 1
 3
 12

*********************************************************************************************/

const int N = 1e5 + 5;
const int LOGN = 18;
const int INF = 1e9 + 5;
int n, q, Arr[N], table[N][LOGN];

void init(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < LOGN; j++){
			table[i][j] = INF;
		}
	}
}

void build(){
    init();

	for(int i = 0; i < n; i++){
		table[i][0] = Arr[i];
	}

	for(int j = 1; j < LOGN; j++){
		for(int i = 0; i <= n - (1 << j); i++){
			int next = i + (1 << (j - 1));
			table[i][j] = min(table[i][j - 1], table[next][j - 1]);
		}
	}
}

int query(int l, int r){
	int len = r - l + 1, Ans = INF;

	for(int i = LOGN - 1; i >= 0; i--){
		if(len >= (1 << i)){
			Ans = min(Ans, table[l][i]);
            len -= (1 << i);
            l += (1 << i);
		}
	}

	return Ans;
}

int main(){
	int l, r;
	scanf("%d", &n);

	for(int i = 0; i < n; i++){
		scanf("%d", &Arr[i]);
	}

	build();
	scanf("%d", &q);

	for(int i = 0; i < q; i++){
		scanf("%d %d", &l, &r);
        printf("%d\n", query(l - 1, r - 1));
	}
	return 0;
}