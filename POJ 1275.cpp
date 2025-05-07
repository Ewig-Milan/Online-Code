#include <bits/stdc++.h>
using namespace std;

const int N = 25;

int n, need[N], can[N], T;
bool solvable;

int h[N], e[N << 2], v[N << 2], ne[N << 2], idx;
void cl() {
    idx = 0;
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(v, 0, sizeof v);
}
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

int dis[N], cnt[N];
bool flag[N];
bool SPFA(int st) {
    for(int i = 0; i < N; i++) dis[i] = 1e9, flag[i] = cnt[i] = 0;
    stack<int> S;
    S.push(st);
    flag[st] = true, dis[st] = 0;
    while(!S.empty()) {
        int x = S.top();
        S.pop();
        flag[x] = false;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                cnt[j] = cnt[x] + 1;
                if(cnt[j] >= 25) return false;
                if(!flag[j]) S.push(j), flag[j] = true;
            }
        }
    }
    return true;
}

void link(int x) {
    for(int i = 1; i <= 24; i++) add(i, i - 1, 0), add(i - 1, i, can[i]);
    for(int i = 8; i <= 24; i++) add(i, i - 8, -need[i]);
    for(int i = 1; i <= 7; i++) add(i, i + 16, x - need[i]);
    add(24, 0, -x);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        memset(can, 0, sizeof can); solvable = false;
        for(int i = 1; i <= 24; i++) scanf("%d", &need[i]);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            int a; scanf("%d", &a);
            can[a + 1]++;   
        }
        for(int res = 0; res <= n; res++) {
            cl(); link(res);
            if(SPFA(0)) {
                printf("%d\n", res);
                solvable = true;
                break;
            }
        }
        if(!solvable) puts("No Solution");
    }
    return 0;
}