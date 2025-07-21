#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll>
#define xx first
#define yy second

using namespace std;

std::vector<ll> travel(vector<ll> AA, vector<int> BB, vector<int> UU, vector<int> VV, vector<int> WW);

const ll N = 100100;
const PLL O = {0, 0};

ll n;
ll f[N];
ll A[N], B[N];
vector<ll> trans; // 可换乘的点
bool cmp(ll a, ll b) {return B[a] > B[b];}

ll h[N], e[N << 1], ne[N << 1], idx;
ll v[N << 1];
void add(ll a, ll b, ll c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

struct LCA_you_know {
    ll dis[N];
    ll fa[N][18], dep[N];
    void dfs_pre(ll x, ll l) {
        fa[x][0] = l, dep[x] = dep[l] + 1;
        for(ll i = 1; i < 18; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
        for(ll i = h[x]; ~i; i = ne[i]) {
            ll j = e[i];
            if(j == l) continue;
            dis[j] = dis[x] + v[i];
            dfs_pre(j, x);
        }
    }
    ll LCA(ll x, ll y) {
        if(dep[x] < dep[y]) swap(x, y);
        for(ll i = 17; i >= 0; i--)
            if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
        if(x == y) return y;
        for(ll i = 17; i >= 0; i--) if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
        return fa[y][0];
    }
    ll get_dis(ll x, ll y) {return dis[x] + dis[y] - (dis[LCA(x, y)] << 1);}
}LCA;

ll fa[N];
bool del[N];

ll get_tot(ll x, ll l) {
    if(del[x]) return 0;
    ll sum = 1;
    for(ll i = h[x]; ~i; i = ne[i]) {
        ll j = e[i];
        if(j == l) continue;
        sum += get_tot(j, x);
    }
    return sum;
}

ll get_wc(ll x, ll l, ll tot, ll &wc) {
    if(del[x]) return 0;
    ll ma = 0, sum = 1;
    for(ll i = h[x]; ~i; i = ne[i]) {
        ll j = e[i];
        if(j == l) continue;
        ll tmp = get_wc(j, x, tot, wc);
        sum += tmp, ma = max(ma, tmp);
    }
    ma = max(ma, tot - sum);
    if(ma <= (tot >> 1)) wc = x;
    return sum;
}

void calc(ll rt, ll l) {
    if(del[rt]) return;
    get_wc(rt, 0, get_tot(rt, 0), rt);
    fa[rt] = l, del[rt] = 1;
    for(ll i = h[rt]; ~i; i = ne[i]) calc(e[i], rt);
}

struct Convex_Hull {
    struct Point {ll xx, yy, id;};
    ll id;
    vector<Point> cvh;
    ll l, r = -1;

    ll X(ll j) {return -B[j];}
    ll Y(ll j) {return f[j] + A[j] + B[j] * LCA.get_dis(j, id);}
    ll F(ll i, ll j) {return j == -1 ? (ll)1e18 : Y(j) + B[j] * LCA.get_dis(i, id);}

    bool cmp_k(PLL a, PLL b, PLL c, PLL d) {
        return (__int128)(b.yy - a.yy) * (d.xx - c.xx)
        >= (__int128)(b.xx - a.xx) * (d.yy - c.yy);
    }
    PLL P(ll id) {return {X(id), Y(id)};}
    ll get_ans(ll x, ll k) {
        if(cvh.empty()) return -1;
        l = 0, r = cvh.size() - 1;
        while(l < r) {
            ll mid = l + r >> 1;
            if(cvh[mid].yy - k * cvh[mid].xx <=
                cvh[mid + 1].yy - k * cvh[mid + 1].xx) r = mid;
            else l = mid + 1;
        }
        ll tmp = cvh[l].id;
        l = 0, r = cvh.size() - 1;
        return tmp;
    }
    void add_back(ll x) {
        auto Px = P(x);
        while(l <= r && Px.xx == cvh[r].xx) {
            if(cvh[r].yy >= Px.yy) r--;
            else {
                cvh.resize(r + 1);
                return;
            }
        }
        while(l < r && cmp_k({cvh[r - 1].xx, cvh[r - 1].yy}, Px, {cvh[r].xx, cvh[r].yy}, Px)) r--;
        cvh.resize(++r), cvh.push_back({Px.xx, Px.yy, x});
    }
}cvh[N];

std::vector<ll> travel(vector<ll> AA, vector<int> BB, vector<int> UU, vector<int> VV, vector<int> WW) {
    memset(h, -1, sizeof h);
    n = (ll)AA.size();
    for(ll i = 1; i <= n; i++) A[i] = AA[i - 1];
    for(ll i = 1; i <= n; i++) {
        B[i] = BB[i - 1];
        if(i != 1 && B[i] < B[1]) trans.push_back(i);
    }
    for(ll i = 1; i < n; i++) {
        ll a = UU[i - 1], b = VV[i - 1], c = WW[i - 1];
        a++, b++;
        add(a, b, c);
    }
    sort(trans.begin(), trans.end(), cmp);
    LCA.dep[0] = -1;
    LCA.dfs_pre(1, 0), calc(1, 0);
    for(ll i = 1; i <= n; i++) cvh[i].id = i;
    memset(f, 127, sizeof f);
    f[1] = 0;
    ll tmp = 1;
    while(tmp) {
        cvh[tmp].add_back(1);
        tmp = fa[tmp];
    }
    for(ll x : trans) {
        ll tmp = x;
        while(tmp) {
            f[x] = min(f[x], cvh[tmp].F(x, cvh[tmp].get_ans(x, LCA.get_dis(x, tmp))));
            tmp = fa[tmp];
        }
        tmp = x;
        while(tmp) {
            cvh[tmp].add_back(x);
            tmp = fa[tmp];
        }
    }
    vector<ll> ans;
    for(ll x = 2; x <= n; x++) {
        ll tmp = x; ll res = 1e18;
        while(tmp) {
            res = min(res, cvh[tmp].F(x, cvh[tmp].get_ans(x, LCA.get_dis(x, tmp))));
            tmp = fa[tmp];
        }
        ans.push_back(res);
    }
    return ans;
}