int OneCentroid(int rt, vector<vector<ar<int,2>>> &g, vector<bool> &dead) {
	int n = g.size();
	vector<int> sz(n);
	function<void(int,int)> get_sz = [&](int u, int pu) {
		sz[u] = 1;
		for (auto v : g[u]) if (v[1] != pu && !dead[v[1]]) {
			get_sz(v[1], u);
			sz[u] += sz[v[1]];
		}
	};
	get_sz(rt, rt);
	function<int(int,int)> dfs = [&](int u, int pu) {
		for (auto v : g[u]) if (v[1] != pu && !dead[v[1]]) {
			if (sz[v[1]] > sz[rt]/2) return dfs(v[1], u);
		}
		return u;
	};
	return dfs(rt, rt);
}

int CentroidDecomposition(vector<vector<ar<int,2>>> &g, int k) {
	int n = g.size();
	vector<bool> dead(n, false);
	int ans = 0;
	function<void(int)> decompose = [&](int start) {
		int cen = OneCentroid(start, g, dead);
		dead[cen] = true;
		// do stuff with subtree of centroid here

		for (auto v : g[cen]) if (!dead[v[1]]) decompose(v[1]);
		dead[cen] = false;
	};
	decompose(0);
	return ans;
}
