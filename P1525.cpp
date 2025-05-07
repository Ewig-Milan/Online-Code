#include <bits/stdc++.h>
using namespace std;

const int N = 20100, M = 100100;

int n, m;

int h[N], e[M << 1], ne[M << 1], v[M << 1], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int col[N];

bool dfs(int x, int c, int w) {
    bool res = true;
    col[x] = c;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(v[i] <= w) continue;
        if(col[j]) {
            if(col[j] == c) return false;
            continue;
        }
        res &= dfs(j, 3 - c, w);
    }
    return res;
}

bool check(int x) {
    bool res = true;
    memset(col, 0, sizeof col);
    for(int i = 1; i <= n; i++) if(!col[i]) res &= dfs(i, 1, x);
    return res;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }
    int l = 0, r = 1e9;
    while(l < r) {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}