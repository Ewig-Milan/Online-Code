#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 500100, M = 500100, P = 7, mod = 1e9 + 7;

int n, m, q;
int sum;

int rad[N];
int exi_rd[N], los_rd[N], exi[N], los[N];
int rd_sum, now_sum;

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++, exi_rd[b]++, exi[b] += rad[a];
}

signed main() {
    srand(time(0));
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; i++) rad[i] = (int)rand() * P % mod, sum += rad[i];
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        add(a, b);
    }
    for(int i = 1; i <= n; i++) rd_sum += exi_rd[i], now_sum += exi[i];
    scanf("%lld", &q);
    while(q--) {
        int mode; scanf("%lld", &mode);
        if(mode == 1) {
            int a, b; scanf("%lld%lld", &a, &b);
            exi_rd[b]--, los_rd[b]++, rd_sum--;
            exi[b] -= rad[a], los[b] += rad[a], now_sum -= rad[a];
            if(rd_sum == n && now_sum == sum) puts("YES");
            else puts("NO");
        } else if(mode == 2) {
            int a; scanf("%lld", &a);
            rd_sum -= exi_rd[a], los_rd[a] += exi_rd[a], exi_rd[a] = 0;
            now_sum -= exi[a], los[a] += exi[a], exi[a] = 0;
            if(rd_sum == n && now_sum == sum) puts("YES");
            else puts("NO");
        } else if(mode == 3) {
            int a, b; scanf("%lld%lld", &a, &b);
            exi_rd[b]++, los_rd[b]--, rd_sum++;
            exi[b] += rad[a], los[b] -= rad[a], now_sum += rad[a];
            if(rd_sum == n && now_sum == sum) puts("YES");
            else puts("NO");
        } else {
            int a; scanf("%lld", &a);
            rd_sum += los_rd[a], exi_rd[a] += los_rd[a], los_rd[a] = 0;
            now_sum += los[a], exi[a] += los[a], los[a] = 0;
            if(rd_sum == n && now_sum == sum) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}