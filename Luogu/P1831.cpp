#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll f[20][20][400];
vector<int> num;
int P, len;

ll dfs(int i, int k, bool lim) {
    if(k < 0 || k > 324) return 0;
    if(!lim && f[P][i][k] != -1) return f[P][i][k];
    if(!i) return k == 0;
    int tmp = lim ? num[i] : 9;
    ll ans = 0;
    for(int a = 0; a <= tmp; a++) ans += dfs(i - 1, k + (i - P) * a, lim && a == tmp);
    return lim ? ans : f[P][i][k] = ans;
}
ll work(ll x) {
    num.resize(1, 0), len = 0;
    while(x) num.push_back(x % 10), x /= 10, len++;
    ll ans = 0;
    for(P = 1; P <= len; P++) {
        ans += dfs(len, 0, 1);
        ans--;
    }
    return ans;
}

int main() {
    memset(f, -1, sizeof f);
    ll l, r; scanf("%lld%lld", &l, &r);
    printf("%lld", work(r) - work(l - 1));
    return 0;
}