#include <bits/stdc++.h>
#define PII pair<int, int>
#define fi first
#define se second
#define top(x) a[(x)][cnt[(x)]]
using namespace std;

const int N = 60, M = 500, limit = 820100;

int n, m;

int ans;
PII ANS[limit];

int a[N][M], cnt[N], tot[N], p[N];

void op(int x, int y) {
    ANS[++ans].fi = x, ANS[ans].se = y;
    a[y][++cnt[y]] = a[x][cnt[x]--];
}

int count(int x, int y) {
    int res = 0;
    for(int i = 1; i <= m; i++) res += a[x][i] == y;
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        cnt[i] = m;
        for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    }
    cnt[n + 1] = 0;
    for(int i = 1; i <= n + 1; i++) p[i] = i;
    for(int r = n; r >= 3; r--) {
        int tmp = count(p[1], r);
        for(int i = 1; i <= tmp; i++) op(p[r], p[r + 1]);
        for(int i = 1; i <= m; i++)
            if(top(p[1]) == r) op(p[1], p[r]);
            else op(p[1], p[r + 1]);

        for(int i = 1; i <= m - tmp; i++) op(p[r + 1], p[1]);

        for(int i = 1; i <= m; i++)
            if(top(p[2]) == r || cnt[p[1]] == m) op(p[2], p[r + 1]);
            else op(p[2], p[1]);

        swap(p[1], p[r]), swap(p[2], p[r + 1]);
        for(int k = 1; k < r; k++) {
            tmp = count(p[k], r);
            for(int i = 1; i <= tmp; i++) op(p[r], p[r + 1]);
            for(int i = 1; i <= m; i++)
                if(top(p[k]) == r) op(p[k], p[r]);
                else op(p[k], p[r + 1]);
            swap(p[k], p[r + 1]), swap(p[k], p[r]);
        }
        for(int i = 1; i < r; i++) while(top(p[i]) == r) op(p[i], p[r + 1]);
        for(int i = 1; i < r; i++) while(cnt[p[i]] < m) op(p[r], p[i]);
    }
    int tmp = count(p[1], 1);
    for(int i = 1; i <= tmp; i++) op(p[2], p[3]);

    for(int i = 1; i <= m; i++)
        if(top(p[1]) == 1) op(p[1], p[2]);
        else op(p[1], p[3]);

    for(int i = 1; i <= tmp; i++) op(p[2], p[1]);
    for(int i = 1; i <= m - tmp; i++) op(p[3], p[1]);

    while(cnt[p[3]]) op(p[3], p[2]);
    for(int i = 1; i <= m - tmp; i++) op(p[1], p[3]);

    for(int i = 1; i <= m; i++)
        if(top(p[2]) == 1) op(p[2], p[1]);
        else op(p[2], p[3]);

    printf("%d\n", ans);
    for(int i = 1; i <= ans; i++) printf("%d %d\n", ANS[i].fi, ANS[i].se);
    return 0;
}