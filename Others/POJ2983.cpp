#include <bits/stdc++.h>
using namespace std;

const int N = 1100, M = 100100;

int n, m;
bool solvable;

int h[N], e[M << 1], ne[M << 1], v[M << 1], idx;
void cl() {
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(v, 0, sizeof v);
    idx = 0;
}
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

bool flag[N];
int dis[N], cnt[N];
bool SPFA(int st) {
    stack<int> S;
    S.push(st);
    flag[st] = true;
    dis[st] = 0;
    while(!S.empty()) {
        int x = S.top();
        S.pop();
        flag[x] = false;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                cnt[j] = cnt[x] + 1;
                if(cnt[j] >= n) return false;
                if(!flag[j]) S.push(j), flag[j] = true;
            }
        }
    }
    return true;
}

int main() {
    while(~scanf("%d%d", &n, &m) && n && m) {
        cl(); solvable = true;
        for(int i = 0; i < N; i++) dis[i] = 1e9, flag[i] = cnt[i] = 0;
        for(int i = 1; i <= m; i++) {
            char mode[1]; int a, b; scanf("%s%d%d", mode, &a, &b);
            if(mode[0] == 'P') {
                int c; scanf("%d", &c);
                add(a, b, -c), add(b, a, c);
            } else add(a, b, 0);
        }
        for(int i = 1; i <= n; i++) if(dis[i] > 1e8)
            solvable &= SPFA(i);
        printf("%s\n", solvable ? "Reliable" : "Unreliable");
    }
    return 0;
}