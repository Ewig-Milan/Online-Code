#include <bits/stdc++.h>
using namespace std;
int T, n, rd[26], cd[26], fa[26], cnt, cnt_c, cnt_r;
int find(int x) {
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int main() {
	scanf("%d", &T);
	while(T--) {
		memset(fa, -1, sizeof fa);
		memset(rd, -1, sizeof rd);
		memset(cd, -1, sizeof cd);
		cnt = cnt_r = cnt_c = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			char c[1100]; scanf("%s", c + 1);
			int t = strlen(c + 1), a = c[1] - 'a', b = c[t] - 'a';
			if(fa[a] == -1) fa[a] = a; if(fa[b] == -1) fa[b] = b;
			cd[a]++, rd[b]++, a = find(a), b = find(b);
			if(a != b) fa[a] = b;
		}
		for(int i = 0; i < 26; i++) {
			cnt += fa[i] == i;
			cnt_r += max(0, rd[i] - cd[i]);
			cnt_c += max(0, cd[i] - rd[i]);
		}
printf("%s\n",(cnt>1||cnt_r!=cnt_c||cnt_r>1)?"The door cannot be opened.":"Ordering is possible.");
	}
	return 0;
}