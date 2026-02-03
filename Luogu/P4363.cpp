#include <bits/stdc++.h>
using namespace std;

const int N = 15, INF = 1e9, M = 1100000;

int n, m, s, t;
int A[N][N], B[N][N];
int f[M];

int trans(int state, int x) { // 第 x 行多一个
    int pos = 1;
    for(int cnt = 0; cnt <= x && pos <= n + m; pos++) {
        if((state >> (pos - 1)) & 1) cnt++;
        if(cnt == x) break;
    }
    if((state >> (pos - 2)) & 1 || pos == 1) return -1;
    return state - (1 << (pos - 2));
}

int g(int state, int x) {
    int pos = 1;
    for(int cnt = 0; cnt <= x; pos++) {
        if((state >> (pos - 1)) & 1) cnt++;
        if(cnt == x) break;
    }
    int cnt = 0;
    for(int i = n + m; i >= pos; i--) if(!((state >> (i - 1)) & 1)) cnt++;
    return cnt;
}

int dfs(int x, bool now) { // now 该谁放 1 - B   0 - W
    if(abs(f[x]) != INF) return f[x];
    if(now & 1) f[x] = -INF;
    else f[x] = INF;
    for(int i = 1; i <= n; i++) {
        int nxt = trans(x, i);
        if(nxt == -1) continue;
        if(now & 1) f[x] = max(f[x], dfs(nxt, now ^ 1) + A[i][g(nxt, i)]);
        else f[x] = min(f[x], dfs(nxt, now ^ 1) - B[i][g(nxt, i)]);
    }
    return f[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &A[i][j]);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &B[i][j]);
    for(int i = 0; i < M; i++) f[i] = INF;
    for(int i = 1; i <= n; i++) t <<= 1, t++, s <<= 1, s++;
    s <<= m, f[t] = 0;
    printf("%d", dfs(s, 1));
}