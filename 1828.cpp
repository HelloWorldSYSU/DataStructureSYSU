#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int maxn = 501;
const int inf = 1<<30;
int dp[maxn][maxn];
int a[maxn];
int b[maxn];

void init(){
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < maxn; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			dp[i][j] = inf;
		}
	}
	dp[1][1] = 0;
}

int solve(int n, int m){
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 2; j <= m; ++j)
		{
			dp[i][j] = min(dp[i - 1][j - 1] + abs(a[i] - b[j]), dp[i][j - 1]);
		}
	}
}



int main(){
	int T;
	cin >> T;
	while(T --){
		int N, M;
		cin >> N >> M;
		for (int i = 1; i <= N; ++i)
		{
			cin >> a[i];
		}
		for (int i = 1; i <= M; ++i)
		{
			cin >> b[i];
		}
		sort(a + 1, a + N + 1);
		sort(b + 1, b + M + 1);
		init();
		solve(N, M);
		cout << dp[N][M] << endl;
	}
}