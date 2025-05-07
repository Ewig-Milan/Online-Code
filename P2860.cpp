#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 5100, M = 10100;

int n, m, ans;

vector<int> ebl[N];
int ebl_cnt, ebl_id[N], ebl_d[N];
int dfn[N], low[N], cnt;

vector<pair<int, int> > ecut;

int h[N], e[M << 1], ne[M << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

stack<int> S;
void tarjan(int x, int l, int fa) {
    S.push(x);
    dfn[x] = low[x] = ++cnt;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if((i ^ 1) == l) continue;
        if(!dfn[j]) tarjan(j, i, x), low[x] = min(low[x], low[j]);
        else low[x] = min(low[x], dfn[j]);
    }
    if(dfn[x] == low[x]) {
        ebl_id[x] = ++ebl_cnt;
        if(l >= 0) ecut.push_back({fa, x});
        ebl[ebl_cnt].push_back(x);
        while(S.top() != x) {
            ebl_id[S.top()] = ebl_cnt;
            ebl[ebl_cnt].push_back(S.top());
            S.pop();
        }
        S.pop();
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, -1, 0);
    for(auto i : ecut) ebl_d[ebl_id[i.fi]]++, ebl_d[ebl_id[i.se]]++;
    for(int i = 1; i <= ebl_cnt; i++) ans += ebl_d[i] == 1;
    printf("%d", (ans + 1) / 2);
    return 0;
}