#include <bits/stdc++.h>
using namespace std;

const int N = 100100;
const int Tr = N - 1, Fa = N - 2, Un = N - 3;

int nothing, T;

int n, m, ans;
int real_[N], val[N];

int h[N], e[N << 1], v[N << 1], ne[N << 1], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

bool vis[N], sum[N];
int siz;
bool dfs(int x, int l, bool pre) {
    if(vis[x]) return !(sum[x] ^ pre);
    bool solvable = x != Un;
    vis[x] = 1, sum[x] = pre;
    if(x != Un && x != Tr && x != Fa) siz++;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        solvable &= dfs(j, x, pre ^ v[i]);
    }
    return solvable;
}

int main() {
    scanf("%d%d", &nothing, &T);
    while(T--) {
        idx = ans = 0;
        for(int i = 0; i < N; i++) real_[i] = i, vis[i] = sum[i] = val[i] = 0, h[i] = -1;

        scanf("%d%d", &n, &m);
        while(m--) {
            char mode[3]; scanf("%s", mode);
            if(mode[0] == '+' || mode[0] == '-') {
                int a, b; scanf("%d%d", &a, &b);
                real_[a] = real_[b];
                val[a] = val[b] ^ (mode[0] == '-');
            } else {
                int a; scanf("%d", &a);
                if(mode[0] == 'T') real_[a] = Tr, val[a] = 0;
                if(mode[0] == 'F') real_[a] = Fa, val[a] = 0;
                if(mode[0] == 'U') real_[a] = Un, val[a] = 0;
            }
        }
        for(int i = 1; i <= n; i++) add(real_[i], i, val[i]);
        for(int i = 1; i <= n; i++) {
            if(vis[i]) continue;
            siz = 0;
            if(!dfs(i, 0, 0)) ans += siz;
        }
        printf("%d\n", ans);
    }
    return 0;
}