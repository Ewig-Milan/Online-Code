#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 200100;

int n, m;
int rd[N], t_rd[N];
double f[N];

int h[N], e[M], v[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

double DP(int st) {
    queue<int> q;
    q.push(st);
    f[st] = 0;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            f[j] += (f[x] + v[i]) / rd[j];
            if(!--t_rd[j]) q.push(j);
        }
    }
    return f[1];
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(b, a, c); rd[a]++, t_rd[a]++;
    }
    printf("%.2lf", DP(n));
    return 0;
}