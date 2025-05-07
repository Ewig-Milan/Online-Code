#include <bits/stdc++.h>
#define PI pair<int, int>
#define fi first
#define se second
#define db double

using namespace std;

const int N = 1100;

int n, m, ans;
pair<int, int> a[N], b[N];
vector<int> mp[N];
int mt[N], vis[N], tim;

db dist(const PI& p1, const PI& p2) {
    db dx = p1.fi - p2.fi, dy = p1.se - p2.se;
    return sqrt(dx * dx + dy * dy);
}

bool match(int x) {
    for(int v : mp[x]) {
        if(vis[v] == tim) continue;
        vis[v] = tim;
        if(mt[v] == 0 || match(mt[v])) {
            mt[v] = x;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].fi, &a[i].se);
    for(int i = 1; i <= m; i++) scanf("%d%d", &b[i].fi, &b[i].se);

    for(int i = 1; i < n; i++)
    for(int j = 1; j <= m; j++) {
        db d1 = dist(a[i], b[j]), d2 = dist(b[j], a[i+1]);
        db d = dist(a[i], a[i+1]);
        if(d1 + d2 <= 2 * d + 1e-8) mp[i].push_back(j);
    }

    for(int i = 1; i < n; i++) {
        tim++;
        if(match(i)) ans++;
    }
    vector<PI> res;
    for(int i = 1; i < n; i++) {
        res.push_back(a[i]);
        bool flag = false;
        for(int j = 1; j <= m; j++) if(mt[j] == i) {
            res.push_back(b[j]);
            flag = true;
            break;
        }
    }
    res.push_back(a[n]);
    printf("%d\n", (int)res.size());
    for(auto p : res) printf("%d %d ", p.fi, p.se);
    return 0;
}