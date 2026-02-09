#include <bits/stdc++.h>
using namespace std;

const int N = 50100;

int n, m;
int use[N];
vector<pair<int, int>> ans;

struct CFS {
    int h[N], e[N], v[N], ne[N], idx, rd[N];
    int f[2][N]; // 0最短路 1最长路
    void add(int a, int b, int c) {
        e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++, rd[b]++;
    }
    void DP(int s) {
        memset(f[0], 63, sizeof f[0]);
        memset(f[1], 0, sizeof f[1]);
        memset(use, 0, sizeof use);
        queue<int> q;
        q.push(s), f[0][s] = f[1][s] = 0;
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(int i = h[x]; ~i; i = ne[i]) {
                int j = e[i];
                f[0][j] = min(f[0][j], f[0][x] + v[i]);
                f[1][j] = max(f[1][j], f[1][x] + v[i]);
                if((++use[j]) == rd[j]) q.push(j);
            }
        }
    }
    void cl() {
        memset(h, -1, sizeof h), idx = 0;
        memset(rd, 0, sizeof rd);
    }
}mp, r_mp;

void bfs() {
    memset(use, 0, sizeof use);
    int tmp = mp.f[1][n];
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = mp.h[x]; ~i; i = mp.ne[i]) {
            int j = mp.e[i];
            if(mp.f[0][x] == mp.f[1][x] && r_mp.f[0][j] == r_mp.f[1][j] && mp.v[i] < tmp - mp.f[0][x] - r_mp.f[0][j])
                ans.push_back({i + 1, tmp - mp.f[0][x] - r_mp.f[0][j] - mp.v[i]}), mp.v[i] = tmp - mp.f[0][x] - r_mp.f[0][j];
            else if((++use[j]) == mp.rd[j]) q.push(j);
        }
    }
}

int main() {
    for(int Case = 1; ~scanf("%d%d", &n, &m) && n && m; Case++) {
        mp.cl(), r_mp.cl(), ans.clear();
        for(int i = 1; i <= m; i++) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            mp.add(a, b, c), r_mp.add(b, a, c);
        }
        mp.DP(1), r_mp.DP(n);
        bfs(), mp.DP(1);
        printf("Case %d: ", Case);
        if(mp.f[0][n] != mp.f[1][n]) puts("No solution");
        else {
            printf("%d %d\n", ans.size(), mp.f[0][n]);
            for(auto x : ans) printf("%d %d\n", x.first, x.second);
        }
    }
    return 0;
}