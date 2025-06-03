#include <bits/stdc++.h>
#define ld long double
#define F(i, j) f[j] + quick_p((ld)S[i] - S[j] + i - j - 1 - L, p)
using namespace std;

const int N = 100100;

int T, n, L, p, choice[N], S[N];
ld f[N];
char sen[N][31];

ld quick_p(ld x, int a) {
	x = max(x, -x);
	ld res = 1;
	while(a) {
		if(a & 1) res *= x;
		a >>= 1, x *= x;;
	}
	return res;
}

struct P {int l, r, p;};

bool work() {
	deque<P> q;
	q.push_back({1, n, 0});
	for(int i = 1; i <= n; i++) {
		while(q.front().r < i) q.pop_front();
		P fr = q.front();
		f[i] = F(i, fr.p), choice[i] = fr.p + 1;
		
		if(F(n, q.back().p) < F(n, i)) continue;
        // 首先看它能否至少更新一个 这里很容易忘

		while(q.back().l > i && F(q.back().l, i) <= F(q.back().l, q.back().p)) q.pop_back();
		P & bk = q.back();
		int l = bk.l, r = bk.r;
		while(l < r) {
			int mid = l + r + 1 >> 1;
			if(F(mid, bk.p) < F(mid, i)) l = mid;
			else r = mid - 1;
		}
		bk.r = l;
		q.push_back({l + 1, n, i});
	}
	return f[n] <= 1e18;
}

void print(int x) {
	if(!x) return;
	print(choice[x] - 1);
	for(int i = choice[x]; i <= x; i++) {
		printf("%s", sen[i]);
		if(i < x) putchar(' ');
	}
	putchar('\n');
}

int main() {
	scanf("%d", &T);
	while(T--) {
		memset(S, 0, sizeof S);
		memset(f, 0, sizeof f);
		memset(choice, 0, sizeof choice);
		scanf("%d%d%d", &n, &L, &p);
		for(int i = 1; i <= n; i++) {
			scanf("%s", sen[i]);
			S[i] = S[i - 1] + strlen(sen[i]); 
		}
		if(work()) {
			printf("%lld\n", (long long)f[n]);
			print(n);
		} else puts("Too hard to arrange");
		printf("--------------------");
		if(T) putchar('\n');
	}
	return 0;
}