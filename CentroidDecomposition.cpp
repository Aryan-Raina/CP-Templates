void OneCentroid(int rt, vector<vector<int>> &g, vector<int> &dead) {
	int n = g.size();
	vector<int> sz(n);
	function<void(int,int)> get_sz = [&](int u, int pu) {
		sz[v] = 1;
		for (int v : g[u]) if (v != pu && !dead[v]) {
			get_sz(v);
			sz[u] += sz[v];
		}
	};
	get_sz(rt, rt);
	function<int(int,int)> dfs = [&](int u, int pu) {
		for (int v : g[u]) if (v != pu && !dead[v]) {
			if (sz[v] > sz[rt]/2) return dfs(v, u);
		}
		return u;
	};
	return dfs(rt, rt);
}

int CentroidDecomposition(vector<vector<int>> &g) {
	int n = g.size();
	vector<bool> dead(n, false);
	int ans = 0;
	function<int(int,int)> decompose = [&](int start) {
		int cen = OneCentroid(start, g, dead);
		dead[cen] = true;
		// do stuff with subtree of centroid here
		for (int v : g[u]) if (!dead[v]) decompose(v);
		dead[cen] = false;
	};
	decompose(0);
	return ans;
}
