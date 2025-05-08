#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, q;
int last[N]/*下标质数值存上一个的id*/, ne[N][26];

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 0; i <= 25; i++) 
        for(int j = 1; j <= n + 1; j++) ne[j][i] = n + 1;
    for(int i = 1; i <= n; i++) {
        int tmp;
        scanf("%d", &tmp);
        for(int j = 2; j * j <= tmp; j++) {
            if(tmp % j == 0) ne[last[j]][0] = min(ne[last[j]][0], i), last[j] = i;
            while(tmp % j == 0) tmp /= j;
        }
        if(tmp > 1) ne[last[tmp]][0] = min(ne[last[tmp]][0], i), last[tmp] = i;
    }
    for(int i = n - 1; i > 0; i--) ne[i][0] = min(ne[i][0], ne[i + 1][0]);
    for(int i = 1; i <= 25; i++)
        for(int j = 1; j <= n; j++)
            ne[j][i] = ne[ne[j][i - 1]][i - 1];
    while(q--) {
        int l, r, ans = 0; scanf("%d%d", &l, &r);
        for(int i = 25; i >= 0; i--)
            if(ne[l][i] <= r) l = ne[l][i], ans += 1 << i;
        printf("%d\n", ans + 1);
    }
    return 0;
}
