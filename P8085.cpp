#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int N = 1000100;
const ull sy = 1000009;

int l_n, c_n;
int d_l[N], d_c[N], ne[N];
ull ha_l[N], ha_c, P[N];
ull nw;

map<string, int> mp_l, mp_c;

void tran(int d[]) {
    P[0] = 1;
    for(int i = 1; i <= l_n; i++)
        ha_l[i] = ha_l[i - 1] * sy + d[i], P[i] = P[i - 1] * sy;
}

ull trans(int d[]) {
    ull x = 0;
    for(int i = 1; i <= c_n; i++) x = x * sy + d[i];
    return x;
}

ull get(int l, int r) {return ha_l[r] - ha_l[l - 1] * P[r - l + 1];}

int main() {
    string s;
    while(cin >> s && s[0] != '$') {
        l_n++;
        if(mp_l[s]) ne[mp_l[s]] = l_n, d_l[l_n] = l_n - mp_l[s];
        mp_l[s] = l_n;
    }
    while(cin >> s && s[0] != '$') {
        c_n++;
        if(mp_c[s]) d_c[c_n] = c_n - mp_c[s];
        mp_c[s] = c_n;
    }
    tran(d_l);
    ha_c = trans(d_c);
    nw = get(0, c_n - 1);
    for(int l = 1, r = c_n; r <= l_n; l++, r++) {
        nw *= P[1];
        if(d_l[r] <= r - l) nw += d_l[r];
        if(ne[l - 1] <= r) nw -= P[r - ne[l - 1]] * d_l[ne[l - 1]];
        if(nw == ha_c) {
            printf("%d", l);
            break;
        }
    }
    return 0;
}