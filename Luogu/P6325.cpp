#include <bits/stdc++.h>
using namespace std;

const int N = 200100, sqrtN = 450;

int n, cnt;

struct Ques {int op, a;} Q[N]; // 0修 1查

struct Stu {int id, A, B;} s[N];
bool CMPab(const Stu &a, const Stu & b) {return a.B == b.B ? a.A < b.A : a.B < b.B;}
bool CMPid(const Stu &a, const Stu & b) {return a.id < b.id;}

int bl_id[N];
vector<int> bl[sqrtN + 100];
int Ama[sqrtN + 100];

bool cmp1(int x, int y) {return s[x].A >= s[y].A && s[x].B >= s[y].B;}
bool cmp2(int x, int y) {return s[x].B == s[y].B ? s[x].A > s[y].A : s[x].B > s[y].B;}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        char c[10]; scanf("%s", c);
        if(c[0] == 'D') {
            int a, b; scanf("%d%d", &a, &b);
            Q[i] = {0, ++cnt}, s[cnt] = {cnt, a, b};
        } else {
            int a; scanf("%d", &a);
            Q[i] = {1, a};
        }
    }
    sort(s + 1, s + cnt + 1, CMPab);
    for(int i = 1, x = 1; x <= cnt; i++)
    for(int j = 1; j <= sqrtN; j++, x++)
        bl_id[s[x].id] = i;
    sort(s + 1, s + cnt + 1, CMPid);
    for(int i = 1; i <= n; i++) {
        if(Q[i].op) {
            int p = bl_id[Q[i].a], ans = 0;
            for(int x : bl[p])
            if(x != Q[i].a && cmp1(x, Q[i].a) && (!ans || cmp2(ans, x)))
                ans = x;
            if(ans) {printf("%d\n", ans); continue;}
            p++;
            while(Ama[p] < s[Q[i].a].A && p <= 452) p++;
            if(p >= 452) {puts("NE"); continue;}
            for(int x : bl[p])
            if(cmp1(x, Q[i].a) && (!ans || cmp2(ans, x)))
                ans = x;
            printf("%d\n", ans);
        } else {
            bl[bl_id[Q[i].a]].push_back(Q[i].a);
            Ama[bl_id[Q[i].a]] = max(Ama[bl_id[Q[i].a]], s[Q[i].a].A);
        }
    }
    return 0;
}