#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll M = 998244353, sy = 27;
const int N = 300100;

int n, len[N];
ll P[N], ha[N];
unordered_map<ll, int> mp[N];
set<int> se;

void prep() {
    P[0] = 1;
    for(int i = 1; i < N; i++) P[i] = (P[i - 1] * sy) % M;
}

ll get_hash(char s[]) {
    int s_n = strlen(s + 1);
    ll res = 0;
    for(int i = 1; i <= s_n; i++) res = (res * sy + s[i] - 96) % M;
    return res;
}

void get_hash_array(char s[]) {
    int s_n = strlen(s + 1);
    ha[0] = 0;
    for(int i = 1; i <= s_n; i++) ha[i] = (ha[i - 1] * sy + s[i] - 96) % M;
}

ll get(int l, int r) {return (((ha[r] - ha[l - 1] * P[r - l + 1]) % M) + M) % M;}

ll query(char s[]) {
    int s_n = strlen(s + 1);
    ll res = 0;
    get_hash_array(s);
    for(auto i : se)
        for(int j = 1; j <= s_n - i + 1; j++)
            res += mp[i][get(j, j + i - 1)];
    return res;
}

int main() {
    prep();
    scanf("%d", &n);
    while(n--) {
        int mode; scanf("%d", &mode);
        char c[N]; scanf("%s", c + 1);
        if(mode == 1) {
            ll h = get_hash(c);
            int tmp = strlen(c + 1);
            if(!len[tmp]) se.insert(tmp);
            mp[tmp][h]++, len[tmp]++;
        } else if(mode == 2) {
            ll h = get_hash(c);
            int tmp = strlen(c + 1);
            len[tmp]--;
            if(!len[tmp]) se.erase(tmp);
            mp[tmp][h]--;
        } else printf("%lld\n", query(c)), fflush(stdout);
    }
    return 0;
}