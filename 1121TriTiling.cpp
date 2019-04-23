#include <iostream>
#include <string.h>
using namespace std;

const int maxn = 31;
int dp[maxn][3];

void init(){
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	dp[1][1] = 1;
	dp[0][2] = 1;
}

void solve(int m){
	for (int i = 1; i <= m; ++i){
		dp[i][0] = dp[i-2][0] + dp[i-1][1] + dp[i-2][2]; 
		dp[i][1] = dp[i-1][2];
		dp[i][2] = dp[i][0] + dp[i-1][1];
	}
}


int main()
{
	int n;
	while(scanf("%d", &n) && n != -1)
	{
		init();
		if(n == 0)
		{
			printf("1\n");	
		}
		else if(n % 2 != 0)
		{
			printf("0\n");	
		}
		else
		{
			solve(n);
			printf("%d\n", dp[n][0]);	
		}
	}
	return 0;	
}