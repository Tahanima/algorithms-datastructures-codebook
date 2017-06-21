#include <bits/stdc++.h>
using namespace std;

const int N = 10;
int Arr[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int BLOCK_SIZE, block[N];

void build(){
	BLOCK_SIZE = sqrt(N);

	for(int i = 0; i < N; i++){
		int block_number = i/BLOCK_SIZE;
		block[block_number] += Arr[i];
	}
}

void update(int index, int val){
	int block_number = index/BLOCK_SIZE;
	block[block_number] += (val - Arr[index]);
    Arr[index] = val;
}

int query(int left, int right){
	int sum = 0;
	for(; left < right && (left % BLOCK_SIZE) != 0 ; left++){
		sum += Arr[left];
	}
	
	for(; left + BLOCK_SIZE <= right ; left += BLOCK_SIZE){
		sum += block[left/BLOCK_SIZE];
	}
	
	for(; left <= right ; left++){
		sum += Arr[left];
	}

	return sum;
}


int main(){
	build();

	printf("Summation of numbers from index %d to %d is: %d\n", 1, 9, query(1, 9));
	printf("Summation of numbers from index %d to %d is: %d\n", 3, 5, query(3, 5));
	printf("Summation of numbers from index %d to %d is: %d\n", 2, 7, query(2, 7));
	printf("Summation of numbers from index %d to %d is: %d\n", 5, 5, query(5, 5));
	update(0, 9);
	printf("Summation of numbers from index %d to %d is: %d\n", 0, 9, query(0, 9));
	update(3, 10);
	printf("Summation of numbers from index %d to %d is: %d\n", 1, 8, query(1, 8));
	return 0;
}