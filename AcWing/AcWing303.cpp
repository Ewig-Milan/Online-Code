#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100100;
ll INF = 1e18;

int n, m, p;
ll d[N], a[N], s[N], f[2][N];

int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 2; i <= n; i++) {
        scanf("%lld", &d[i]);
        d[i] += d[i - 1];
    }
    for (int i = 1; i <= m; i++) {
        int h, t; scanf("%d%d", &h, &t);
        a[i] = t - d[h];
    }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) s[i] = s[i - 1] + a[i];

    for (int i = 0; i <= m; i++) f[0][i] = INF;
    f[0][0] = 0;

    for (int j = 1; j <= p; j++) {
        int cur = j % 2, pre = 1 - cur;
        for (int i = 0; i <= m; i++) f[cur][i] = INF;
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i <= m; i++) {
            while (q.size() >= 2 &&
                   (f[pre][q[1]] + s[q[1]] - f[pre][q[0]] - s[q[0]]) <= a[i] * (q[1] - q[0]))
                q.pop_front();
            int k = q.front();
            f[cur][i] = f[pre][k] - a[i] * k + s[k] + a[i] * i - s[i];
            while (q.size() >= 2 &&
                   (f[pre][q[q.size() - 1]] + s[q[q.size() - 1]] - f[pre][q[q.size() - 2]] - s[q[q.size() - 2]]) * (i - q.back()) >=
                   (f[pre][i] + s[i] - f[pre][q.back()] - s[q.back()]) * (q.back() - q[q.size() - 2]))
                q.pop_back();
            q.push_back(i);
        }
    }
    printf("%lld\n", f[p % 2][m]);
    return 0;
}