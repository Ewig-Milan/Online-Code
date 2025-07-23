#include <bits/stdc++.h>
using namespace std;

const int N = 1100, INF = 1e9;

int n, ans;
bool ans_choice;
int fact[N][N][2], f[N][N], N0x;
bool back[N][N][2]; // 0R 1D

void print(int x, int y) {
    if(x == 1 && y == 1) return;
    if(back[x][y][ans_choice]) print(x - 1, y);
    else print(x, y - 1);
    printf("%c", back[x][y][ans_choice] ? 'D' : 'R');
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) 
    for(int j = 1; j <= n; j++) {
        int a; scanf("%d", &a);
        if(!a) N0x = i, fact[i][j][0] = fact[i][j][1] = INF;
        else {
            while(a % 5 == 0) fact[i][j][0]++, a /= 5;
            while(a % 2 == 0) fact[i][j][1]++, a >>= 1;
        }
    }
    memset(f, 63, sizeof f);
    f[0][1] = f[1][0] = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        if(f[i - 1][j] > f[i][j - 1]) {
            f[i][j] = f[i][j - 1] + fact[i][j][0];
            back[i][j][0] = 0;
        } else {
            f[i][j] = f[i - 1][j] + fact[i][j][0];
            back[i][j][0] = 1;
        }
    ans = f[n][n];
    memset(f, 63, sizeof f);
    f[0][1] = f[1][0] = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        if(f[i - 1][j] > f[i][j - 1]) {
            f[i][j] = f[i][j - 1] + fact[i][j][1];
            back[i][j][1] = 0;
        } else {
            f[i][j] = f[i - 1][j] + fact[i][j][1];
            back[i][j][1] = 1;
        }
    if(ans > f[n][n]) ans = f[n][n], ans_choice = 1;
    else ans_choice = 0;
    if(N0x && ans) {
        puts("1");
        for(int i = 1; i < N0x; i++) printf("D");
        for(int i = 1; i < n; i++) printf("R");
        for(int i = N0x; i < n; i++) printf("D");
    } else {
        printf("%d\n", ans);
        print(n, n);
    }
    return 0;
}