#include <bits/stdc++.h>
using namespace std;

/**********************************************************************************************
 Given an array of N integers and Q queries. For each query of type l r, the number of distinct 
 numbers from indices l to r should be outputted.

 Input:
 8 5 -----------------------> N Q
 1 2 3 3 1 2 4 2 -----------> N numbers
 1 4  |
 3 8  |
 2 4  |---------------------> Q queries
 7 8  |
 3 6  |

 Output:
 3
 4
 2
 2
 3
**********************************************************************************************/

#define f first 
#define s second 
const int MX = 1e6 + 10;
typedef pair<int,int> pii;
typedef pair<pii,int> piii;
int N, Q, current_answer, BLOCK_SZ;
int cnt[MX], ans[MX], arr[MX];
piii queries[MX];

bool comp(piii x, piii y){
	int block_x = x.f.f/BLOCK_SZ;
	int block_y = y.f.f/BLOCK_SZ;
	return (block_x != block_y) ? block_x < block_y : x.f.s < y.f.s;
}

void add(int x){
	cnt[x]++;
	if(cnt[x] == 1) current_answer++;
}

void remove(int x){
	cnt[x]--;
	if(cnt[x] == 0) current_answer--;
}

int main(){
	int a, b;
	cin >> N >> Q;
	BLOCK_SZ = sqrt(N);
	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}

	for(int i = 0; i < Q; i++){
		cin >> a >> b;
		queries[i].f.f = --a;
        queries[i].f.s = --b;
		queries[i].s = i;
	}

	sort(queries, queries + Q, comp);
	int mo_left = 0, mo_right = -1;

	for(int i = 0; i < Q; i++){
		int left = queries[i].f.f;
		int right = queries[i].f.s;

		for(; mo_right < right ; mo_right++, add(arr[mo_right]));
		for(; mo_right > right ; remove(arr[mo_right]), mo_right--);
		for(; mo_left < left ; remove(arr[mo_left]), mo_left++);
		for(; mo_left > left ; mo_left--, add(arr[mo_left]));

		ans[queries[i].s] = current_answer;
	}

	for(int i = 0; i < Q; i++) cout << ans[i] << endl;
	return 0;
}