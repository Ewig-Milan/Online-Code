#include <bits/stdc++.h>
using namespace std;

const int N = 2100, M = 1000100;

int n, m, w[N], dis[N], ans;

int rd[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++, rd[b]++;}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        w[n + i] = 1;
        int a, j; scanf("%d%d", &a, &j);
        add(n + i, j);
        while(--a) {
            int t; scanf("%d", &t);
            add(n + i, t);
            while(++j < t) {
                add(j, n + i);
            }
        }
    }
    queue<int> q;
    for(int i = 1; i <= n + m; i++) if(!rd[i]) q.push(i), dis[i] = 1;
    while(!q.empty()) {
        int j = q.front();
        q.pop();
        ans = max(ans, dis[j]);
        for(int i = h[j]; ~i; i = ne[i]) {
            dis[e[i]] = max(dis[e[i]], dis[j] + w[e[i]]);
            if(!--rd[e[i]]) q.push(e[i]);
        }
    }
    printf("%d", ans);
    return 0;
}