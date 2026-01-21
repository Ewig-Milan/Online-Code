#include <bits/stdc++.h>
using namespace std;

const int N = 3000100;

int n, m;
vector<int> txt[N];
int ans[N];
char c1[N], c2[N];

int h[N], e[N], ne[N], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

int tr[5][N], tot;
int nxt[N], id[N];

int D(char c) {return c == '@' ? 0 : (c == 'A' ? 1 : (c == 'U' ? 2 : (c == 'G' ? 3 : 4)));}

int insert(char s[]) {
    int s_n = strlen(s + 1);
    int j = 0;
    for(int i = 1; i <= s_n; i++) {
        if(!tr[D(s[i])][j]) tr[D(s[i])][j] = ++tot;
        j = tr[D(s[i])][j];
    }
    return j;
}

void build() {
    queue<int> q;
    for(int i = 0; i < 5; i++) if(tr[i][0]) q.push(tr[i][0]), add(0, tr[i][0]);
    while(!q.empty()) {
        int j = q.front();
        q.pop();
        for(int i = 0; i < 5; i++) {
            int k = tr[i][j];
            if(k) nxt[k] = tr[i][nxt[j]], q.push(k), add(nxt[k], k);
            else tr[i][j] = tr[i][nxt[j]];
        }
    }
}

void dfs(int x) {for(int i = h[x]; ~i; i = ne[i]) dfs(e[i]), ans[x] += ans[e[i]];}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%s", c1 + 1);
        int c_n = strlen(c1 + 1);
        for(int j = 1; j <= c_n; j++) txt[i].push_back(D(c1[j]));
        txt[i].push_back(0);
        for(int j = 1; j <= c_n; j++) txt[i].push_back(D(c1[j]));
    }
    for(int i = 1; i <= m; i++) {
        scanf("%s%s", c2 + 1, c1 + 1);
        int c_n = strlen(c2 + 1), tmp = strlen(c1 + 1);
        c1[tmp + 1] = '@';
        for(int j = 1; j <= c_n; j++) c1[tmp + j + 1] = c2[j];
        c1[tmp + c_n + 2] = 0;
        id[i] = insert(c1);
    }
    build();
    for(int i = 1; i <= n; i++) {
        int j = 0;
        for(int x : txt[i]) j = tr[x][j], ans[j]++;
    }
    dfs(0);
    for(int i = 1; i <= m; i++) printf("%d\n", ans[id[i]]);
    return 0;
}