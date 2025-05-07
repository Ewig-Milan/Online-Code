#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100100;

int n, A[N], C[N];
ll ans;

bool flag;
vector<int> mp[N], cir[N];
int cnt, rd[N], bk[N], in_cir[N]/*0在 1不在 -1查过*/;

void find_cir() {
    queue<int> q;
    for(int i = 1; i <= n; i++) if (!rd[i])
        q.push(i), in_cir[i] = flag = 1;

    while(!q.empty()) {
        int t = q.front();
        if(!--rd[A[t]]) q.push(A[t]), in_cir[A[t]] = 1;
        q.pop();
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &A[i], &C[i]);
        mp[A[i]].push_back(i);
        rd[A[i]]++;
    }
    find_cir();

    for(int i = 1; i <= n; i++) {
        if(in_cir[i] == 1) {
            int ma = 0;
            for(int j = 0; j < mp[i].size(); j++) ma = max(ma, C[mp[i][j]]), ans += C[mp[i][j]];
            ans -= ma;
        } else {
            for(int j = 0; j < mp[i].size(); j++) if(in_cir[mp[i][j]] == 1)
                bk[i] = max(bk[i], C[mp[i][j]]), ans += C[mp[i][j]];

            if(!in_cir[i]) cnt++;
            int tmp = i;
            while(!in_cir[tmp]) {
                in_cir[tmp] = -1;
                cir[cnt].push_back(tmp);
                tmp = A[tmp];
            }
        }
    }
    if(flag || cnt > 1) {
        for(int i = 1; i <= cnt; i++) {
            int mi = 1e9;
            for(int j = 0; j < cir[i].size(); j++)
                mi = min(mi, C[cir[i][j]] - bk[A[cir[i][j]]]);

            if(mi >= 0) ans += mi;
            else for(int j = 0; j < cir[i].size(); j++)
                if(C[cir[i][j]] - bk[A[cir[i][j]]] < 0)
                    ans += C[cir[i][j]] - bk[A[cir[i][j]]];
        }
    }
    printf("%lld", ans);
    return 0;
}