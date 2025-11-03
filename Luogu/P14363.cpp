#include <bits/stdc++.h>
using namespace std;

const int N = 12000000, M = 5000100;

int n, q;

int tr[N][30], idx, ne[N];
int sum[N];
void insert(char s[]) {
    int s_n = strlen(s + 1), j = 0;
    for(int i = 1; i <= s_n; i++) {
        if(!tr[j][s[i] - '_']) tr[j][s[i] - '_'] = ++idx;
        j = tr[j][s[i] - '_'];
    }
    sum[j]++;
}

void build() {
    queue<int> q;
    for(int i = 0; i < 30; i++) if(tr[0][i]) q.push(tr[0][i]);

    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = 0; i < 30; i++) {
            int k = tr[x][i];
            if(k) ne[k] = tr[ne[x]][i], sum[k] += sum[ne[k]], q.push(k);
            else tr[x][i] = tr[ne[x]][i];
        }
    }
}

char s1[M], s2[M], fus[N];
void fusion() {
    int s_n = strlen(s1 + 1), i = 1, tmp = 1, r = s_n;
    while(r >= 1 && s1[r] == s2[r]) r--;

    while(i <= s_n && s1[i] == s2[i]) fus[tmp++] = s1[i++];
    fus[tmp++] = '_';
    for(int j = i; j <= r; j++) fus[tmp++] = s1[j];
    for(int j = i; j <= r; j++) fus[tmp++] = s2[j];
    fus[tmp++] = '_';
    while(r < s_n) fus[tmp++] = s1[++r];
    fus[tmp] = 0;
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%s", s1 + 1); scanf("%s", s2 + 1);
        fusion();
        insert(fus + 1);
    }
    build();
    while(q--) {
        scanf("%s", s1 + 1); scanf("%s", s2 + 1);
        if(strlen(s1 + 1) != strlen(s2 + 1)) {puts("0"); continue;}
        fusion();
        int s_n = strlen(fus + 1), ans = 0;
        for(int i = 1, j = 0; i <= s_n; i++) {
            j = tr[j][fus[i] - '_'];
            ans += sum[j];
        }
        printf("%d\n", ans);
    }
    return 0;
}