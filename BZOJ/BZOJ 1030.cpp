#include <bits/stdc++.h>
using namespace std;

const int N = 6100, mod = 1e4 + 7;

int n, m, ans;
int tr[N][26], ne[N], idx;
bool bar[N];
int f[110][N];

void insert(char s[]) {
    int s_n = strlen(s + 1), j = 0;
    for(int i = 1; i <= s_n; i++) {
        if(!tr[j][s[i] - 'A']) tr[j][s[i] - 'A'] = ++idx;
        j = tr[j][s[i] - 'A'];
    }
    bar[j] = true;
}

void build() {
    queue<int> q;
    for(int i = 0; i < 26; i++)
        if(tr[0][i]) q.push(tr[0][i]);
    while(!q.empty()) {
        int j = q.front();
        q.pop();
        for(int i = 0; i < 26; i++) {
            int k = tr[j][i];
            if(k) ne[k] = tr[ne[j]][i], q.push(k), bar[k] |= bar[ne[k]];
            else tr[j][i] = tr[ne[j]][i];
        }
    }
}

int quick_p(int x, int a) {
    int res = 1;
    while(a) {
        if(a & 1) res *= x, res %= mod;
        x *= x, x %= mod, a >>= 1;
    }
    return res + mod;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        char c[N]; scanf("%s", c + 1);
        insert(c);
    }
    build();
    f[0][0] = 1;
    for(int i = 0; i <= m; i++)
    for(int k = 0; k <= idx; k++)
    for(int p = 0; p < 26; p++)
        if(!bar[k]) f[i + 1][tr[k][p]] += f[i][k], f[i + 1][tr[k][p]] %= mod;
    for(int i = 0; i <= idx; i++)
        if(!bar[i]) ans += f[m][i], ans %= mod;
    printf("%d", (quick_p(26, m) - ans) % mod);
    return 0;
}