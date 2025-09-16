#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int N = 1048600;
const ull sy = 11451;

int T, n;
char S[N];

bool exist[27];
int num;
int suf[N], pre[N], c[N][27];

ull po[N], ha[N];
ull get(int l, int r) {return ha[r] - ha[l - 1] * po[r - l + 1];}

int main() {
    po[0] = 1;
    for(int i = 1; i < N; i++) po[i] = po[i - 1] * sy;

    scanf("%d", &T);

    while(T--) {
        scanf("%s", S + 1);
        n = strlen(S + 1), num = 0;
        memset(exist, 0, sizeof exist);
        for(int i = n; i >= 1; i--) {
            int ch = S[i] - 'a';
            exist[ch] ^= 1;
            if(exist[ch]) num++;
            else num--;
            suf[i] = num;
        }
        memset(exist, 0, sizeof exist);
        num = 0;
        for(int i = 1; i <= n; i++) {
            int ch = S[i] - 'a';
            exist[ch] ^= 1;
            if(exist[ch]) num++;
            else num--;
            pre[i] = num;
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= 26; j++) c[i][j] = c[i - 1][j];
            for(int j = pre[i]; j <= 26; j++) c[i][j]++;
        }
        for(int i = 1; i <= n; i++) ha[i] = ha[i - 1] * sy + (S[i] - 'a');

        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            ull tmp = get(1, i);
            for(int l = 1, r = i; r + 1 <= n; l += i, r += i) {
                if(tmp != get(l, r)) break;
                ans += c[i - 1][suf[r + 1]];
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}