#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int m1, m2, ans;
int st[N][35];
char s1[N], s2[N];
bool hav[27];

int main() {
    while(~scanf("%s%d%s%d", s1 + 1, &m1, s2 + 1, &m2)) {
        memset(st, 127, sizeof st);
        memset(hav, 0, sizeof hav);
        ans = 0;
        int s1_n = strlen(s1 + 1), s2_n = strlen(s2 + 1);
        for(int i = 1; i <= s2_n; i++) hav[s2[i] - 'a'] = true;
        for(int i = 1; i <= s1_n; i++) if(!hav[s1[i] - 'a']) hav[26] = true;
        if(hav[26]) {
            puts("0");
            continue;
        }
        for(int i = 1; i <= s2_n; i++) {
            int cnt = 1;
            for(int j = 1; j <= s1_n; j++, cnt++)
                while(s1[j] != s2[((i + cnt - 2) % s2_n) + 1]) cnt++;
            st[i][0] = cnt - 1;
        }
        for(int j = 1; j <= 31; j++)
        for(int i = 1; i <= s2_n; i++) {
            st[i][j] = min((long long)1e9, (long long)st[i][j - 1] + st[((i + st[i][j - 1] - 1) % s2_n) + 1][j - 1]);
        }
        m2 *= s2_n;
        for(int i = 31, id = 1; i >= 0; i--) if(st[id][i] <= m2)
            ans += (1 << i), m2 -= st[id][i], id += st[id][i], id = ((id - 1) % s2_n) + 1;
        printf("%d\n", ans / m1);
    }
    return 0;
}