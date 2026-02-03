#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1100, M = 16, mod = 1e9 + 7;

int n, k;
char s[N];
int f[2][1 << M][3]; // 012 - NOI
map<vector<int>, int> mp;
int idx, ne[1 << M][3];
vector<int> sta[1 << M];
int py[3][3] = {{1, 1, 1}, {0, 2, 0}, {0, 0, -1}};
int ans[N];

int D(char c) {return c == 'N' ? 0 : (c == 'O' ? 1 : 2);}

int dfs(vector<int> &v) {
    if(mp[v]) return mp[v];
    else idx++, mp[v] = idx, sta[idx] = v;
    vector<int> tmp;
    for(int i = 0; i < 3; i++) {
        tmp = v;
        for(int j = 1; j <= k; j++) tmp[j] = max(max(tmp[j], tmp[j - 1]), v[j - 1] + (D(s[j]) == i));
        ne[mp[v]][i] = dfs(tmp);
    }
    return mp[v];
}

signed main() {
    scanf("%lld%lld", &n, &k);
    scanf("%s", s + 1);
    for(int i = 0; i < (1 << M); i++) sta[i].resize(k + 1);
    dfs(sta[0]);
    f[0][1][0] = 1;
    for(int i = 1, now = 1, pre = 0; i <= n; i++, swap(now, pre)) {
        for(int j = 1; j <= idx; j++) {
            for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++) {
                if(py[x][y] == -1) continue;
                f[now][ne[j][x]][py[x][y]] += f[pre][j][y];
                f[now][ne[j][x]][py[x][y]] %= mod;
            }
        }
        memset(f[pre], 0, sizeof f[pre]);
    }
    for(int i = 1; i <= idx; i++) {
        ans[sta[i][k]] += (f[n & 1][i][0] + f[n & 1][i][1] + f[n & 1][i][2]) % mod;
        ans[sta[i][k]] %= mod;
    }
    for(int i = 0; i <= k; i++) printf("%lld\n", ans[i]);
    return 0;
}