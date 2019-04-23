#include <iostream>
#include <string.h>
using namespace std;

const int maxn = 11;
const int maxm = 2001;
long long dp[maxn][maxm];

void init(){
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < maxm; ++i)
	{
		dp[1][i] = i; 
	}
	for (int i = 2; i < maxn; ++i)
	{
		dp[i][1] = 0;
	}
}

void solve(int n, int m){
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 2; j <= m; ++j)
		{
			dp[i][j] = dp[i][j - 1] + dp[i - 1][j / 2];
		}
	}
}

int main(){  
    int t, c = 1; 
    int n, m; 
    scanf ("%d", &t);  
    while (t--){  
        init();  
        scanf("%d %d", &n, &m);  
        solve(n, m);  
        printf("Case %d: n = %d, m = %d, # lists = %lld\n", c++, n, m, dp[n][m]);  
    }  
    return 0;  
}  