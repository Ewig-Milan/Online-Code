#include <bits/stdc++.h>
#define db double
using namespace std;

const int N = 100100;
const db eps = 1e-9;

int n;
struct Node {db x, y;} P[N];
db ans;

db dis(const Node &a, const Node &b) {return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}
db K(const Node &a, const Node &b) {
    if(a.x == b.x) return a.y > b.y ? -1e15 : 1e15;
    return (a.y - b.y) / (a.x - b.x);
}
bool cmp_up(const Node &a, const Node &b, const Node &c) {return K(a, b) - K(a, c) > eps;}
bool cmp_down(const Node &a, const Node &b, const Node &c) {return K(a, b) - K(a, c) < eps;}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lf%lf", &P[i].x, &P[i].y);
    sort(P + 1, P + n + 1, [](const Node &a, const Node &b){return a.x == b.x ? a.y < b.y : a.x < b.x;});
    deque<int> q;
    for(int i = 1; i <= n; i++) {
        if(!q.empty() && P[i].x == P[q.back()].x && P[i].y == P[q.back()].y) continue;
        while(q.size() > 1 && cmp_up(P[q[q.size() - 2]], P[i], P[q.back()])) q.pop_back();
        q.push_back(i);
    }
    for(int i = 1; i < q.size(); i++) ans += dis(P[q[i]], P[q[i - 1]]);
    q.clear();
    for(int i = 1; i <= n; i++) {
        if(!q.empty() && P[i].x == P[q.back()].x && P[i].y == P[q.back()].y) continue;
        while(q.size() > 1 && cmp_down(P[q[q.size() - 2]], P[i], P[q.back()])) q.pop_back();
        q.push_back(i);
    }
    for(int i = 1; i < q.size(); i++) ans += dis(P[q[i]], P[q[i - 1]]);
    printf("%.2lf", ans);
    return 0;
}