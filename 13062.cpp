#include <iostream>
#include <string.h>
using namespace std;

const int maxn = 31;
long long dp[maxn][maxn];

void init(){
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < maxn; ++i)
	{
		dp[i][0] = 1;
	}
}

long long solve(int x){
	for (int i = 1; i <= x; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[x][x];
}

int main() {
	int m;
    while (cin >> m && m != 0) {
        init();
        cout << solve(m) << endl;
    }
 
    return 0;
}                                 
