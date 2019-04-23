#include <iostream>
#include <string.h>
using namespace std;

const int maxn = 1001;
int val[maxn];
int dp[maxn][maxn];

void init(){
	memset(val, -1, sizeof(val));
	memset(dp, -1, sizeof(dp));
}

int solve(int l, int r){
	int lmax, rmax;
	if(r - l == 1){
		return val[l] > val[r] ? val[l] : val[r];
	}
	if(dp[l][r] != -1){
		return dp[l][r];
	}
	if(dp[l][r] == -1){
		if(val[l + 1] >= val[r]){
			lmax = val[l] + solve(l + 2, r);
		}
		else{
			lmax = val[l] + solve(l + 1, r - 1);
		}
		if(val[l] >= val[r - 1]){
			rmax = val[r] + solve(l + 1, r - 1);
		}
		else{
			rmax = val[r] + solve(l, r - 2);
		}
	}
	dp[l][r] = (lmax > rmax ? lmax : rmax);
	return dp[l][r];
}

int main(){
	int n, sum = 0, index = 0;
	while(cin >> n && n != 0){
		init();
		index ++;
		for (int i = 0; i < n; ++i)
		{
			cin >> val[i];
			sum += val[i];
		}
		int player1 = solve(0, n - 1);
		int player2 = sum - player1;
		cout << "In game " << index << ", the greedy strategy might lose by as many as " << player1 - player2 << " points." << endl;
		sum = 0;
	}
	return 0;
}