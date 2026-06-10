#include <bits/stdc++.h>
using namespace std;

const int N = 250100;

int n, ans;
int A[N], B[N];
priority_queue<pair<int, int>> q;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &B[i]);
    long long rem = 0;
    for(int i = 1; i <= n; i++) {
        rem += A[i];
        if(rem >= B[i]) ans++, rem -= B[i], q.push({B[i], i});
        else if(!q.empty() && q.top() > make_pair(B[i], i)) rem += q.top().first - B[i], q.pop(), q.push({B[i], i});
    }
    printf("%d\n", ans);
    while(!q.empty()) printf("%d ", q.top().second), q.pop();
    return 0;
}