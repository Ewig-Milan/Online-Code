//
// Tarjan 写法  时间线性
//
// 赠上一则(我调的时候)Hack: 5   2 3 1 5 4
#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, ans = 1e9;

int h[N], e[N], ne[N], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

stack<int> S;
int res, dfn[N], low[N], cnt;
bool flag[N];
int tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    S.push(x);
    flag[x] = true;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(!dfn[j]) {
            tarjan(j);
            low[x] = min(low[x], low[j]);
        } else if(flag[j]) low[x] = min(low[x], low[j]);
    }
    if(low[x] == dfn[x]) {
        if(S.top() != x) res = 1;
        while(S.top() != x) {
            flag[S.top()] = false;
            S.pop();
            res++;
        }
        S.pop();
    }
    return res;
}

int main() {
    memset(h, -1, sizeof(h));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        add(i, a);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) ans = min(ans, tarjan(i));
    printf("%d", ans);
    return 0;
}