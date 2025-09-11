#include <bits/stdc++.h>
using namespace std;

const int N = 500100;

int nothing, n, m, q;
int X[N], Y[N];
queue<pair<int, int> > op1, op2;

int A_pre_ma[N], A_pre_mi[N], B_pre_ma[N], B_pre_mi[N];
int A_suf_ma[N], A_suf_mi[N], B_suf_ma[N], B_suf_mi[N];
bool pre_dfs(int x, int y, int (&A)[N], int (&B)[N]) {
    if(x == 1 || y == 1) return true;
    int x_ = A_pre_ma[x - 1], y_ = B_pre_mi[y - 1];
    if(A[x_] > B[B_pre_ma[y - 1]] && B[y_] < A[A_pre_mi[x - 1]]) return pre_dfs(x_, y_, A, B);
    else if(A[x_] > B[B_pre_ma[y - 1]]) return pre_dfs(x_, y, A, B);
    else if(B[y_] < A[A_pre_mi[x - 1]]) return pre_dfs(x, y_, A, B);
    return false;
}
bool suf_dfs(int x, int y, int (&A)[N], int (&B)[N], int a_n, int b_n) {
    if(x == a_n || y == b_n) return true;
    int x_ = A_suf_ma[x + 1], y_ = B_suf_mi[y + 1];
    if(A[x_] > B[B_suf_ma[y + 1]] && B[y_] < A[A_suf_mi[x + 1]]) return suf_dfs(x_, y_, A, B, a_n, b_n);
    else if(A[x_] > B[B_suf_ma[y + 1]]) return suf_dfs(x_, y, A, B, a_n, b_n);
    else if(B[y_] < A[A_suf_mi[x + 1]]) return suf_dfs(x, y_, A, B, a_n, b_n);
    return false;
}
bool work(int (&A)[N], int (&B)[N], int a_n, int b_n) { // A > B
    if(A[1] <= B[1]) return false;
    for(int i = 1; i <= a_n; i++) {
        if(i == 1 || A[i] > A[A_pre_ma[i - 1]]) A_pre_ma[i] = i;
        else A_pre_ma[i] = A_pre_ma[i - 1];
        if(i == 1 || A[i] < A[A_pre_mi[i - 1]]) A_pre_mi[i] = i;
        else A_pre_mi[i] = A_pre_mi[i - 1];
    }
    for(int i = 1; i <= b_n; i++) {
        if(i == 1 || B[i] > B[B_pre_ma[i - 1]]) B_pre_ma[i] = i;
        else B_pre_ma[i] = B_pre_ma[i - 1];
        if(i == 1 || B[i] < B[B_pre_mi[i - 1]]) B_pre_mi[i] = i;
        else B_pre_mi[i] = B_pre_mi[i - 1];
    }
    for(int i = a_n; i >= 1; i--) {
        if(i == a_n || A[i] > A[A_suf_ma[i + 1]]) A_suf_ma[i] = i;
        else A_suf_ma[i] = A_suf_ma[i + 1];
        if(i == a_n || A[i] < A[A_suf_mi[i + 1]]) A_suf_mi[i] = i;
        else A_suf_mi[i] = A_suf_mi[i + 1];
    }
    for(int i = b_n; i >= 1; i--) {
        if(i == b_n || B[i] > B[B_suf_ma[i + 1]]) B_suf_ma[i] = i;
        else B_suf_ma[i] = B_suf_ma[i + 1];
        if(i == b_n || B[i] < B[B_suf_mi[i + 1]]) B_suf_mi[i] = i;
        else B_suf_mi[i] = B_suf_mi[i + 1];
    }
    int x = A_pre_ma[a_n], y = B_pre_mi[b_n];
    if(A[x] <= B[B_pre_ma[b_n]]) return false;
    if(B[y] >= A[A_pre_mi[a_n]]) return false;
    return pre_dfs(x, y, A, B) & suf_dfs(x, y, A, B, a_n, b_n);
}

int main() {
    scanf("%d", &nothing);
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &X[i]);
    for(int i = 1; i <= m; i++) scanf("%d", &Y[i]);
    string ans = "";
    ans += (work(X, Y, n, m) | work(Y, X, m, n)) ? "1" : "0";
    while(q--) {
        int kx, ky; scanf("%d%d", &kx, &ky);
        while(kx--) {int a, b; scanf("%d%d", &a, &b); op1.push({a, X[a]}), X[a] = b;}
        while(ky--) {int a, b; scanf("%d%d", &a, &b); op2.push({a, Y[a]}), Y[a] = b;}
        ans += (work(X, Y, n, m) | work(Y, X, m, n)) ? "1" : "0";
        while(!op1.empty()) X[op1.front().first] = op1.front().second, op1.pop();
        while(!op2.empty()) Y[op2.front().first] = op2.front().second, op2.pop();
    }
    cout << ans;
    return 0;
}