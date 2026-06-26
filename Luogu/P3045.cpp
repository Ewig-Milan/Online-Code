#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 50100;

int n, k, ans, t[N];
ll m, P[N], C[N];
bool used[N];
priority_queue<ll, vector<ll>, greater<ll>> X;
queue<int> Y, Z;
    
int main() {
    scanf("%d%d%lld", &n, &k, &m);
    for(int i = 1; i <= n; i++) scanf("%lld%lld", &C[i], &P[i]), t[i] = i;
    sort(t + 1, t + n + 1, [](const int a, const int b){return C[a] < C[b];});
    for(int i = 1; i <= n; i++) Y.push(t[i]);
    sort(t + 1, t + n + 1, [](const int a, const int b){return P[a] < P[b];});
    for(int i = 1; i <= n; i++) Z.push(t[i]);
    for(int i = 1; i <= k; i++) X.push(0);
    while(!Y.empty() && !Z.empty()) {
        int y = Y.front(), z = Z.front();
        if(C[y] <= P[z] + X.top()) m -= C[y], Y.pop(), used[y] = 1;
        else m -= P[z] + X.top(), Z.pop(), X.pop(), X.push(C[z] - P[z]), used[z] = 1;
        if(m < 0) break;
        ans++;
        while(!Y.empty() && used[Y.front()]) Y.pop();
        while(!Z.empty() && used[Z.front()]) Z.pop();
    }
    printf("%d", ans);
    return 0;
}