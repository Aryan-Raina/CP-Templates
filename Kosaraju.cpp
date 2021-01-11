    vector<vector<int>> g(n), gr(n);
    vector<bool> vis(n, 0);
    vector<int> order, comp;

    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs(v);
        order.pb(u);
    };
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);
    dfs = [&](int u) {
        vis[u] = 1;
        comp.pb(u);
        for (int v : gr[u]) if (!vis[v]) dfs(v);
    };
    vis.assign(n, 0);
    for (int i = n-1; i>=0; i--) if (!vis[order[i]]) {
        dfs(order[i]);
        // do stuff
        comp.clear();
    }
