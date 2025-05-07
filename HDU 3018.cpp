#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 200100;

int n, m, d[N], ans[N];
int fa[N], siz[N];
int find(int x) {
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int a, int b) {
    a = find(a), b = find(b);
    siz[a]++;
    if(a == b) return;
    fa[b] = a;
    siz[a] += siz[b];
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        memset(d, 0, sizeof(d));
        memset(ans, 0, sizeof(ans));
        memset(siz, 0, sizeof(siz));
        for(int i = 0; i <= n; i++) fa[i] = i;
        for(int i = 1; i <= m; i++) {
            int a, b; scanf("%d%d", &a, &b);
            d[a]++; d[b]++;
            merge(a, b);
        }
        for(int i = 1; i <= n; i++) {
            int fi = find(i);
            ans[fi] += d[i] & 1;
        }
        int res = 0;
        for(int i = 1; i <= n; i++) {
            if(fa[i] != i) continue;
            ans[i] >>= 1;
            if(!ans[i]) ans[i] = 1;
            if(!siz[i]) ans[i] = 0;
            res += ans[i];
        }
        printf("%d\n", res);
    }
    return 0;
}