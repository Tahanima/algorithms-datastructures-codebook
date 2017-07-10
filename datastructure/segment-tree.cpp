#include <bits/stdc++.h>
using namespace std;

/**********************************************************************************************
 Given an array of N integers and Q queries. Queries are of two types:
 type 1 is of the format 1 a b, which means update the value at index a to b
 type 2 is of the format 2 a b, which means output the sum of the numbers from indices a to b

 Input:
 8 5 -----------------------> N Q
 1 2 3 3 1 2 4 2 -----------> N numbers
 2 1 4 |
 1 3 8 |
 2 2 4 |--------------------> Q queries
 1 6 8 |
 2 3 6 |
 
 Output:
 9
 13
 20
**********************************************************************************************/

const int MX = 1e5 + 5;
int Arr[MX], tree[4 * MX];

void build(int node, int st, int en){
	if(st == en) return Arr[node];
	else{
		int l = 2 * node, r = l + 1, mid = (st + en)/2;
		build(l, st, mid);
		build(r, mid + 1, en);
		tree[node] = tree[l] + tree[r];
	}
}

void update(int node, int st, int en, int idx, int val){
	if(en < idx || st > idx) return;
	else if(st >= idx && en <= idx){
		tree[node] = val;
		return;
	}else{
		int l = 2 * node, r = l + 1, mid = (st + en)/2;
		update(l, st, mid, idx, val);
		update(r, mid + 1, en, idx, val);
		tree[node] = tree[l] + tree[r];
	}
}

int query(int node, int st, int en, int i, int j){
	if(en < i || st > j) return 0;
	else if(st >= i && en <= j) return tree[node];
	else{
		int l = 2 * node, r = l + 1, mid = (st + en)/2;
        int p = query(l, st, mid, i, j);
        int q = query(r, mid + 1, en, i, j);
	}
}

int main(){
	int N, Q, type, l, r, val;
	cin >> N >> Q;

	for(int i = 0; i < N; i++){
		cin >> Arr[i];
	}

	build(1, 0, N - 1);
    for(int i = 0; i < Q; i++){
    	cin >> type;
    	// update
    	if(type == 1){
    		cin >> l >> val;
    		l--;
    		update(1, 0, N - 1, l, val)
    	}
    	// query
    	else{
    		cin >> l >> r;
    		cout << query(1, 0, N - 1, l - 1, r - 1) << endl;
    	}
    }
	return 0;
}