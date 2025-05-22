#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll>
#define x first
#define y second
using namespace std;

const int N = 3100;
const PLL O = {0, 0};

int n, m;
ll f[N][2], S[N];

vector<int> cvh;
int l, r = -1;

ll X(int id) {return S[id];}
ll Y(bool t, int id) {return f[id][t] + S[id] * S[id] * m;}
ll F(bool t, int i, int k) {return f[k][t] + S[i] * S[i] * m - S[i] * 
    S[k] * 2 * m + S[k] * S[k] * m - S[n] * S[i] * 2 + S[n] * S[k] * 2;}

PLL P(bool t, int id) {return {X(id), Y(t, id)};}

bool cmp_k(PLL a, PLL b, PLL c, PLL d) { // k(ab) >= k(cd)
	return (__int128)(b.y - a.y) * (d.x - c.x)
	>= (__int128)(b.x - a.x) * (d.y - c.y);
}

int get_ans(bool t, ll k) {
    while(l < r && cmp_k(O, {1, k}, P(t, cvh[l]), P(t, cvh[l + 1]))) l++;
    return cvh[l];
}
void add_back(bool t, int id) {
    while(l < r && cmp_k(P(t, cvh[r - 1]), P(t, id), P(t, cvh[r]), P(t, id))) r--;
    cvh.resize(++r), cvh.push_back(id);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld", &S[i]), S[i] += S[i - 1];
    memset(f, 127, sizeof f);
    f[0][0] = 0;
    for(int j = 1; j <= m; j++) {
        bool t = j & 1;
        for(int i = 0; i <= n; i++) f[i][t] = 1e18;
        f[0][t] = l = 0, r = -1;
        cvh.resize(0), add_back(t ^ 1, 0);
        for(int i = 1; i <= n; i++) {
            f[i][t] = F(t ^ 1, i, get_ans(t ^ 1, 2 * m * S[i] - 2 * S[n]));
            add_back(t ^ 1, i);
        }
    }
    printf("%lld", f[n][m & 1] - S[n] * S[n]);
    return 0;
}