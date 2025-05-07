#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n, q, m;

struct Ma {
    int x, y;
    ll m[110][110];
}f, e[40];

Ma operator ^ (const Ma & a, const Ma & b) {
    Ma ans;
    memset(ans.m, 0, sizeof(ans.m));
    ans.x = a.x, ans.y = b.y;
    for(int i = 1; i <= a.x; i++) 
        for(int j = 1; j <= b.y; j++)
            for(int k = 1; k <= a.y; k++)
                ans.m[i][j] ^= a.m[i][k] * b.m[k][j];
    return ans;
}

Ma quick_p(Ma x, ll a) {
    for(int i = 0; a; i++, a >>= 1)
        if(a & 1) x = x ^ e[i];
    return x;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    f.x = 1, f.y = n;
    for(int i = 1; i <= n; i++) scanf("%lld", &f.m[1][i]);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        e[0].m[a][b] = e[0].m[b][a] = 1;
    }
    e[0].x = e[0].y = n;
    for(int i = 1; i <= 32; i++) e[i] = e[i - 1] ^ e[i - 1];
    while(q--) {
        ll a; scanf("%lld", &a);
        printf("%lld\n", quick_p(f, a).m[1][1]);
    }
    return 0;
}