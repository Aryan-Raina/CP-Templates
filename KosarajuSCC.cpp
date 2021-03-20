struct KosarajuSCC {
    int N; vector<vector<int>> adj, radj;
    vector<int> todo, comp, comps;
    vector<bool> vis;

    void init(int n) { 
        N = n; adj.resize(N), radj.resize(N);
        comp.assign(N, -1), vis.resize(N); 
    }

    void add_edge(int a, int b) { adj[a].push_back(b); radj[b].push_back(a); }

    void dfs1(int u) {
        vis[u] = 1;
        for (int v : adj[u]) if (!vis[v]) dfs1(v);
        todo.push_back(u);
    }

    void dfs2(int u, int num) {
        comp[u] = num;
        for (int v : radj[u]) if (comp[v] == -1) dfs2(v, num);
    }

    void gen() {
        for (int i = 0; i < N; i++) if (!vis[i]) dfs1(i);
        reverse(todo.begin(), todo.end());
        for (int i : todo) if (comp[i] == -1) {
            dfs2(i, i); comps.push_back(i);
        }
    }
}; 
