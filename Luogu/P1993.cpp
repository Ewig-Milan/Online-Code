//
// SPFA 用 Stack 在判环的时候有很大的优化
//
#include <bits/stdc++.h>
using namespace std;

const int N = 10100;

int n, m;
bool solvable = true;
int h[N], e[N << 1], ne[N << 1], v[N << 1], idx;
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

int dis[N], cnt[N];
bool flag[N];
bool SPFA(int st) {
    stack<int> q;
    dis[st] = 0;
    q.push(st);
    flag[st] = true;
    while(!q.empty()) {
        int x = q.top();
        q.pop();
        flag[x] = false;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                cnt[j] = cnt[x] + 1;
                if(cnt[j] >= n) return false;
                if(!flag[j]) q.push(j), flag[j] = true;
            }
        }
    }
    return true;
}

int main() {
    memset(h, -1, sizeof h);
    for(int i = 0; i < N; i++) dis[i] = 1e9;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int mode; scanf("%d", &mode);
        if(mode == 3) {
            int a, b; scanf("%d%d", &a, &b);
            add(a, b, 0); add(b, a, 0);
        } else {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            if(mode == 1) add(a, b, -c);
            else add(b, a, c);
        }
    }
    for(int i = 1; i <= n; i++) if(dis[i] > 1e8)
        solvable &= SPFA(i);
    printf("%s", solvable ? "Yes" : "No");
    return 0;
}