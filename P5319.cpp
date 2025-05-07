#include <bits/stdc++.h>
#define fi first
#define se second
#define db double
using namespace std;

const int N = 1600;

pair<int, int> back[N][N];
int n, m, ans[N];
db t[N], f[N][N];
int tr[N][10], ne[N], idx, cnt[N];
char p[N];

void insert(char s[], db w) {
    int s_n = strlen(s + 1), j = 0;
    for(int i = 1; i <= s_n; i++) {
        if(!tr[j][s[i] - '0']) tr[j][s[i] - '0'] = ++idx;
        j = tr[j][s[i] - '0'];
    }
    t[j] += w, cnt[j]++;
}

void build() {
    queue<int> q;
    for(int i = 0; i < 10; i++)
        if(tr[0][i]) q.push(tr[0][i]);
    while(!q.empty()) {
        int j = q.front();
        q.pop();
        for(int i = 0; i < 10; i++) {
            int k = tr[j][i];
            if(k) q.push(k), ne[k] = tr[ne[j]][i], t[k] += t[ne[k]], cnt[k] += cnt[ne[k]];
            else tr[j][i] = tr[ne[j]][i];
        }
    }
}

bool check(db x) {
    for(int i = 0; i <= idx; i++) t[i] -= cnt[i] * x;
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= idx; j++)
            f[i][j] = -1e9;
    f[0][0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= idx; j++) {
            if(f[i][j] <= -1e5) continue;
            if(p[i + 1] == '.') {
                for(int k = 0; k < 10; k++) {
                    int tt = tr[j][k];
                    if(f[i + 1][tt] < f[i][j] + t[tt]) {
                        f[i + 1][tt] = f[i][j] + t[tt];
                        back[i + 1][tt].fi = j;
                        back[i + 1][tt].se = k;
                    }
                }
            } else {
                int tt = tr[j][p[i + 1] - '0'];
                if(f[i + 1][tt] < f[i][j] + t[tt]) {
                    f[i + 1][tt] = f[i][j] + t[tt];
                    back[i + 1][tt].fi = j;
                    back[i + 1][tt].se = p[i + 1] - '0';
                }
            }
        }
    }
    for(int i = 0; i <= idx; i++) t[i] += cnt[i] * x;
    int res = 0;
    for(int i = 0; i <= idx; i++)
        if(f[n][i] > f[n][res]) res = i;
    return f[n][res] > 0;
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", p + 1);
    for(int i = 1; i <= m; i++) {
        char c[N]; scanf("%s", c + 1);
        db v; scanf("%lf", &v);
        insert(c, log(v));
    }
    build();
    db l = 0, r = log(1e9);
    while(r - l >= 1e-6) {
        db mid = (l + r) / 2.0;
        if(check(mid)) l = mid;
        else r = mid;
    }
    check(l);
    int tmp = 0;
    for(int i = 0; i <= idx; i++)
        if(f[n][i] > f[n][tmp]) tmp = i;
    for(int i = n; i; i--) ans[i] = back[i][tmp].se, tmp = back[i][tmp].fi;
    for(int i = 1; i <= n; i++) printf("%d", ans[i]);
    return 0;
}