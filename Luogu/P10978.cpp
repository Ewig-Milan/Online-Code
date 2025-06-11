#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 16100, M = 110;

int n, m;
int f[M][N];
int q[N], l, r;

struct Node {int s, l, p;} w[M];
bool cmp(Node a, Node b) {return a.s < b.s;}

signed main()
{
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= m; i++) scanf("%lld%lld%lld", &w[i].l, &w[i].p, &w[i].s);
    sort(w + 1, w + 1 + m, cmp);
    for(int i = 1; i <= m; i++) {
        l = 1, r = 0;
        for(int j = 1; j <= n; j++) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if(j <= w[i].s) {
                while(l <= r && f[i - 1][j - 1] - j * w[i].p >= f[i - 1][q[r] - 1] - q[r] * w[i].p) r--;
                q[++r] = j;
            }
            if(j < w[i].s || j >= w[i].s + w[i].l) continue;
            while(l <= r && q[l] <= j - w[i].l) l++;
            f[i][j] = max(f[i][j], f[i - 1][q[l] - 1] +(j - q[l] + 1) * w[i].p);
        }
    }
    printf("%lld", f[m][n]);
    return 0;
}