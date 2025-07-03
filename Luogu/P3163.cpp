//
// 多（双）源汇限制源汇点（要求点对点地流）
// 那么 可以考虑做两遍 两个都正着流 和 一个正着流一个反着流
//
#include <bits/stdc++.h>
using namespace std;

const int N = 60, M = 5100, INF = 1e9;

int n, S, T, a1, a2, an, b1, b2, bn;

int h[N], e[M], ca[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], can[N];
bool bfs() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
    dep[S] = 0, q.push(S);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        can[x] = h[x];
        if(x == T) return true;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return false;
}

int dfs(int x, int lim) {
    if(x == T) return lim;
    int flow = 0;
    for(int &i = can[x]; ~i && flow < lim; i = ne[i]) {
        int j = e[i];
        if(dep[j] == dep[x] + 1 && ca[i]) {
            int tmp = dfs(j, min(ca[i], lim - flow));
            if(!tmp) dep[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp;
        }
    }
    return flow;
}

int dinic() {
    int mf = 0, tmp;
    while(bfs()) while(tmp = dfs(S, INF)) mf += tmp;
    return mf;
}

int main() {
    while(~scanf("%d", &n) && n) {
        memset(h, -1, sizeof h), idx = 0;
        S = 0, T = n + 1;
        scanf("%d%d%d", &a1, &a2, &an);
        scanf("%d%d%d", &b1, &b2, &bn);
        a1++, a2++, b1++, b2++;
        add(S, a1, an), add(a2, T, an);
        add(S, b1, bn), add(b2, T, bn);
        for(int i = 1; i <= n; i++) {
            char c[60]; scanf("%s", c + 1);
            for(int j = 1; j < i; j++) {
                if(c[j] == 'O') add(i, j, 1);
                if(c[j] == 'N') add(i, j, INF);
            }
        }
        if(dinic() == an + bn) {
            ca[0] = ca[1] = ca[2] = ca[3] = 0;
            for(int i = 4; i < idx; i += 2) ca[i] = ca[i] + ca[i ^ 1] >> 1, ca[i ^ 1] = ca[i];
            add(S, a2, an), add(a1, T, an);
            if(dinic() == an + bn) puts("Yes");
            else puts("No"); 
        } else puts("No");
    }
    return 0;
}