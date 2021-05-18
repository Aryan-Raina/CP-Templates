struct TarjanSCC {
    int N, timer = 0; vector<vector<int>> adj;
    vector<int> disc, st, comp;

    TarjanSCC(int n) : N(n), disc(N, 0), comp(N, -1), adj(N) {}

    void add_edge(int a, int b) { adj[a].push_back(b); }

    int dfsSCC(int u) {
        int low = disc[u] = ++timer; st.push_back(u);
        for (int v : adj[u]) if (comp[v] == -1) 
            low = min(low, disc[v] ? : dfsSCC(v));

        if (low == disc[u]) {
            for (int v = -1; v != u; ) 
                comp[v = st.back()] = u, st.pop_back();
        }

       return low;
    }

    void gen() { for (int i = 0; i < N; i++) if (!disc[i]) dfsSCC(i); }
};
