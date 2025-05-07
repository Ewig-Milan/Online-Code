//先建树

#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 200100;

int n, q, w[N], d[N];

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int fa[N][20], sum[N][20];
void dfs(int x, int l) {
    fa[x][0] = l, sum[x][0] = w[x];
    for(int i = 1; i <= 19; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        sum[x][i] = sum[x][i - 1] + sum[fa[x][i - 1]][i - 1];
    }
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs(j, x);
    }
}

int query(int st, int c) {
    for(int i = 19; i >= 0; i--)
        if(c - sum[st][i] > 0)
            c -= sum[st][i], st = fa[st][i];
    return st;
}

int main() {
    memset(h, -1, sizeof(h));
    scanf("%d%d", &n, &q);
    deque<int> qu;
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &d[i], &w[i]);
        while(!qu.empty() && d[qu.back()] < d[i]) {
            add(qu.back(), i); add(i, qu.back());
            qu.pop_back();
        }
        qu.push_back(i);
    }
    while(!qu.empty()) {
        add(qu.back(), 0); add(0, qu.back());
        qu.pop_back();
    }
    dfs(0, 0);
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        printf("%d\n", query(a, b));
    }
    return 0;
}