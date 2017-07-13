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
int Arr[MX], tree[MX];

void update(int id, int val){
	for(; id < MX ; tree[id] += val, id += id & -id);
}

int query(int id){
	int sum = 0;
	for(; id > 0 ; sum += tree[id], id -= id & -id);
	return sum;
}

int main(){
	int N, Q, type, l, r, val, num;
	cin >> N >> Q;

	for(int i = 1; i <= N; i++){
		cin >> Arr[i];
		update(i, Arr[i]);
	}

	for(int i = 0; i < Q; i++){
    	cin >> type;
    	// update
    	if(type == 1){
    		cin >> l >> val;
    		update(l, val - Arr[l]);
    		Arr[l] = val;
    	}
    	// query
    	else{
    		cin >> l >> r;
    		cout << query(r) - query(l - 1) << endl;
    	}
    }
	return 0;
}