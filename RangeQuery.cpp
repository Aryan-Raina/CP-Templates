template<class T, int SZ> struct RangeQuery {
	int n; 
	T stor[SZ][31-__builtin_clz(SZ)];
	vector<T> a;
	T comb(T a, T b) { 
		return a+b; 
	}
	void fill(int l, int r, int ind) {
		if (ind < 0) return;
		int m = (l + r) >> 1;
		T pre = stor[m-1][ind] = a[m-1]; 
		for (int i = m-2; i >= l; i--) stor[i][ind] = pre = comb(a[i], pre);
		pre = stor[m][ind] = a[m]; 
		for (int i = m+1; i < r; i++) stor[i][ind] = pre = comb(pre, a[i]);
		fill(l, m, ind-1); fill(m, r, ind-1);
	}	
	void init() {
		n = 1; while ((1<<n) < a.size()) n++;
		a.resize(1<<n); fill(0, 1<<n, n-1);
	}
	T query(int l, int r) {
		if (l == r) return a[l];
		int t = 31-__builtin_clz(r^l);
		return comb(stor[l][t], stor[r][t]);
	}
};
