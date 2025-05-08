#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1600;
const ll mod = 1e9 + 7;

int m, n;
ll ans, f[N][N][2];
int tr[N][10], ne[N], idx;
bool bar[N];
char p[N];

void insert(char s[]) {
    int s_n = strlen(s + 1), j = 0;
    for(int i = 1; i <= s_n; i++) {
        if(!tr[j][s[i] - '0']) tr[j][s[i] - '0'] = ++idx;
        j = tr[j][s[i] - '0'];
    }
    bar[j] = true;
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
            if(k) q.push(k), ne[k] = tr[ne[j]][i], bar[k] |= bar[ne[k]];
            else tr[j][i] = tr[ne[j]][i];
        }
    }
}

int main() {
    scanf("%s", p + 1);
    n = strlen(p + 1);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        char c[N]; scanf("%s", c + 1);
        insert(c);
    }
    build();
    for(int i = 1; i < p[1] - '0'; i++) f[1][tr[0][i]][0]++;
    f[1][tr[0][p[1] - '0']][1]++;
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < 10; j++) f[i + 1][tr[0][j]][0]++;
        for(int j = 0; j <= idx; j++) {
            if(bar[j]) continue;
            if(f[i][j][0]) {
                for(int k = 0; k < 10; k++) {
                    f[i + 1][tr[j][k]][0] += f[i][j][0];
                    f[i + 1][tr[j][k]][0] %= mod;
                }
            }
            if(f[i][j][1]) {
                int x = p[i + 1] - '0';
                for(int k = 0; k < x; k++) {
                    f[i + 1][tr[j][k]][0] += f[i][j][1];
                    f[i + 1][tr[j][k]][0] %= mod;
                }
                f[i + 1][tr[j][x]][1] += f[i][j][1];
                f[i + 1][tr[j][x]][1] %= mod;
            }
        }
    }
    for(int i = 0; i <= idx; i++)
        if(!bar[i]) ans += f[n][i][0] + f[n][i][1], ans %= mod;
    printf("%lld", ans);
    return 0;
}