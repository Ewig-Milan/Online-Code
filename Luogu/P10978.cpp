#include <bits/stdc++.h>
using namespace std;

const int N = 16100, K = 110;

int k, n;
int f[K][N];
struct Node {int s, l, p;} Q[K];
bool cmp(const Node & a, const Node & b) {return a.s < b.s;}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= k; i++) scanf("%d%d%d", &Q[i].l, &Q[i].p, &Q[i].s);
	sort(Q + 1, Q + k + 1, cmp);
    for(int i = 1; i <= k; i++) {
        for(int j = Q[i].s + Q[i].l - 1, ma = -2e9; j >= Q[i].s; j--) {
            if(j >= Q[i].l) ma = max(ma, f[i - 1][j - Q[i].l] - Q[i].p * (j - Q[i].l));
            if(j <= n) f[i][j] = Q[i].p * j + ma;
        }
        for(int j = 1; j <= n; j++) f[i][j] = max(f[i][j], max(f[i][j - 1], f[i - 1][j]));
	}
    printf("%d", f[k][n]);
    return 0;
}