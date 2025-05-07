#include <bits/stdc++.h>
using namespace std;

const int N = 25100, M = 50100;

int T, R, P, S;
int dis[N], dji_cnt;
bool flag[N];

int h[N], e[M << 1], v[M << 1], ne[M << 1], idx;
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

int bl_id[N], cnt;
vector<int> bl[N];

void dfs(int x, int id) {
    bl_id[x] = id;
    bl[id].push_back(x);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(bl_id[j]) continue;
        dfs(j, id);
    }
}

struct Flight {int st, to, v;};
vector<Flight> fli[N/*block_id*/];

struct Node {
    int p, dis;
    friend bool operator < (const Node & a, const Node & b) {return a.dis > b.dis;}
};
vector<Node> ent[N/*block_id*/]; //enter

int rd[N/*block_id*/];//存的是进去的航班个数
void fli_dfs(int id) {
	for(auto i : fli[id]) {
		rd[bl_id[i.to]]++;
		if(rd[bl_id[i.to]] <= 1) fli_dfs(bl_id[i.to]);
	}
}

void dji(int id) {
    dji_cnt = 0;
    int n = bl[id].size();
    priority_queue<Node> q;
    for(auto i : ent[id]) if(dis[i.p] > i.dis) {
		q.push(i);
   	    dis[i.p] = i.dis;
	}
    while(!q.empty()) {
        while(!q.empty() && flag[q.top().p]) q.pop();
        dji_cnt++;
        if(dji_cnt == n || q.empty()) break;
        int x = q.top().p;
        q.pop();
        flag[x] = true;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(flag[j]) continue;
            if(dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                q.push({j, dis[j]});
            }
        } 
    }
}

int main() {
    memset(h, -1, sizeof(h));
    memset(dis, 127, sizeof(dis));
    scanf("%d%d%d%d", &T, &R, &P, &S);
    for(int i = 1; i <= R; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }
    for(int i = 1; i <= T; i++) if(!bl_id[i]) dfs(i, ++cnt);
    
    for(int i = 1; i <= P; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        if(bl_id[b] == bl_id[S]) continue;
        fli[bl_id[a]].push_back({a, b, c});
    }
    fli_dfs(bl_id[S]);//get_rd
    
    queue<int> q;
    q.push(bl_id[S]);
    ent[bl_id[S]].push_back({S, 0});
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        dji(x);
        for(auto i : fli[x]) {
            ent[bl_id[i.to]].push_back({i.to, dis[i.st] + i.v});
            rd[bl_id[i.to]]--;
            if(!rd[bl_id[i.to]]) q.push(bl_id[i.to]);
        }
    }
    for(int i = 1; i <= T; i++) {
        if(dis[i] > 2e9) puts("NO PATH");
        else printf("%d\n", dis[i]);
    }
    return 0;
}