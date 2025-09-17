#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2000100;

int n;
int dp[N], last[N];
char s[N];

signed main()
{
    scanf("%lld", &n);
    scanf("%s", s + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i - 1; j > 0; j = last[j] - 1) {
            if(s[i] == s[j]) {
                last[i] = j;
                break;
            }
        }
        if(last[i]) dp[i] = dp[last[i] - 1] + 1, ans += dp[i];
    }
    printf("%lld", ans);
    return 0;
}