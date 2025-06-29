#include <bits/stdc++.h>
using namespace std;

const int N = 2000100;

int n, A[N], ans;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]), A[i + n] = A[i];
    deque<int> q;
    for(int i = 2; i <= n / 2; i++) {
        while(!q.empty() && A[q.back()] + q.back() <= A[i] + i) q.pop_back();
        q.push_back(i);
    }
    for(int i = 1; i <= n; i++) {
        while(!q.empty() && q.front() <= i) q.pop_front();
        ans = max(ans, A[q.front()] + q.front() - i + A[i]);
        while(!q.empty() && A[q.back()] + q.back() <= A[n / 2 + i] + n / 2 + i) q.pop_back();
        q.push_back(n / 2 + i);
    }
    printf("%d", ans);
    return 0;
}