#include <bits/stdc++.h>
using namespace std;

int w, l;
int f[310][610][30];
char word[610][30], txt[310];
int last[130];

int main() {
    scanf("%d%d", &w, &l);
    scanf("%s", txt + 1);
    for(int i = 1; i <= w; i++) scanf("%s", word[i] + 1);
    int ma = 0;
    for(int i = 1; i <= l; i++) {
        for(int j = 1; j <= w; j++) {
            int n = strlen(word[j] + 1);
            for(int k = 1; k <= n; k++) if(word[j][k] == txt[i]) {
                if(k == 1) f[i][j][k] = ma + 1;
                else if(f[last[word[j][k - 1]]][j][k - 1])
                    f[i][j][k] = f[last[word[j][k - 1]]][j][k - 1] + 1;
            }
        }
        for(int j = 1; j <= w; j++) {
            int n = strlen(word[j] + 1);
            ma = max(ma, f[i][j][n]);
        }
        last[txt[i]] = i;
    }
    printf("%d", l - ma);
    return 0;
}