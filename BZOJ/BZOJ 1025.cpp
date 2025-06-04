#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1100;

int n;
ll f[N][N], ans;

bool flag[N];
int pr[N][20], pr_cnt;
void euler(int x) {
    flag[1] = true;
    for(int i = 2; i <= x; i++) {
        if(!flag[i]) pr[++pr_cnt][1] = i;
        for(int j = 1; j <= pr_cnt && i * pr[j][1] <= x; j++) {
            flag[i * pr[j][1]] = true;
            if(i % pr[j][1] == 0) break;
        }
    }
    for(int i = 1; i <= pr_cnt; i++)
    for(int k = 2; pr[i][k - 1] <= n; k++)
        pr[i][k] = pr[i][k - 1] * pr[i][1];
}

int main() {
    scanf("%d", &n);
    euler(n);
    f[0][0] = 1;
    for(int j = 1; j <= pr_cnt; j++) {
        for(int i = 0; i <= n; i++) f[j][i] = f[j - 1][i];
        for(int k = 1; pr[j][k] <= n; k++) for(int i = 1; i <= n; i++)
            f[j][i] += (i >= pr[j][k] ? f[j - 1][i - pr[j][k]] : 0);
    }
    for(int i = 0; i <= n; i++) ans += f[pr_cnt][i];
    printf("%lld", ans);
    return 0;
}