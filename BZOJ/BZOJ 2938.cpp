#include <bits/stdc++.h>
using namespace std;

const int N = 30100;

int n, p_n;
char p[N];
int tr[N][2], ne[N], idx, col[N];
bool bar[N];

void insert(char s[]) {
	int s_n = strlen(s + 1), j = 0;
	for(int i = 1; i <= s_n; i++) {
		if(!tr[j][s[i] - '0']) tr[j][s[i] - '0'] = ++idx;
		j = tr[j][s[i] - '0'];
	}
	bar[j] = true;
}
void build() {
	queue<int> q;
	for(int i = 0; i < 2; i++)
		if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int j = q.front();
		q.pop();
		for(int i = 0; i < 2; i++) {
            int k = tr[j][i];
            if(k) ne[k] = tr[ne[j]][i], bar[k] |= bar[ne[k]], q.push(k);
            else tr[j][i] = tr[ne[j]][i];
        }
	}
}

bool check(int x) {
    if(col[x] || bar[x]) return col[x] == 1;
    bool jud = false;
    col[x] = 1, jud |= check(tr[x][0]) | check(tr[x][1]), col[x] = -1;
    return jud;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char c[N]; scanf("%s", c + 1);
		insert(c);
	}
	build();
	printf("%s", check(0) ? "TAK" : "NIE");
	return 0;
}