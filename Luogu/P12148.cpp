#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;

int n, ans;
pair<int, int> p[1000100];

map<int, map<int, int> > mp;

void work() {
    for(int i = 1; i <= n; i++) {
        int x = p[i].X, y = p[i].Y;
        if(mp[x][y]) ans++;
        if(mp[x + 1][y - 1]) mp[x + 1][y - 1] = 0;
        else if(mp[x + 1][y]) mp[x + 1][y] = 0;
        else if(mp[x + 1][y + 1]) mp[x + 1][y + 1] = 0;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].X, &p[i].Y);
        mp[p[i].X][p[i].Y] = 1;
    }
    sort(p + 1, p + n + 1);
    work();
    printf("%d", ans);
    return 0;
}