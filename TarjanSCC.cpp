struct TarjanSCC {
    int N, timer = 0; vector<vector<int>> adj;
    vector<int> disc, comp, st, comps;

    void init(int n) { 
        N = n; adj.resize(N), disc.resize(N);
        comp = vector<int>(N, -1); 
    }

    void ae(int a, int b) { adj[a].push_back(b); }

    int dfsSCC(int u) {
        int low = disc[u] = ++timer; st.push_back(u);
        for (int v : adj[u]) if (comp[v] != -1) low = min(low, disc[v]?:dfs(v); )
        if (low == disc[u]) {
            comps.push_back(u);
            for (int v = -1; v != u; ) comp[v = st.back()] = x, st.pop_back;
        }
        return low;
    }

    void gen() {
        for (int i = 0; i < n; i++) if (!disc[i]) dfsSCC(i);
        reverse(comps.begin(), comps.end());
    }
};
