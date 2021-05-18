template<class T> struct HeavyLight {
    int n, timer = 0; vector<vector<int>> adj;
    vector<int> par, root, depth, sz, pos; 
    SegmentTree<T> st;

    HeavyLight(int n) : n(n), adj(n), par(n), root(n), depth(n), sz(n), pos(n), st(n) {}

    void add_edge(int a, int b) { adj[a].push_back(b); adj[b].push_back(a); }

    void dfsSz(int u) {
        sz[u] = 1;
        for (int &v : adj[u]) if (v != par[u]) {
            par[v] = u; depth[v] = depth[u] + 1;
            dfsSz(v); sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
        }
    }

    void dfsHld(int u) {
        pos[u] = timer++;
        for (int v : adj[u]) if (v != par[u]) {
            root[v] = (v == adj[u][0] ? root[u] : v);
            dfsHld(v);
        }
    }

    void gen(int rt = 0) {
        par[rt] = depth[rt] = timer = 0;
        dfsSz(rt); root[rt] = rt; dfsHld(rt);
    }

    template<class BinaryOp> 
    void processPath(int u, int v, BinaryOp op) {
        for (; root[u] != root[v]; v = par[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(pos[root[v]], pos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u], pos[v]);
    }

    void modifyPath(int u, int v, T val) {
        processPath(u, v, [this, &val](int l, int r) { st.modify(l, r+1, val); });
    }
    T queryPath(int u, int v) {
        T res = 0;
        processPath(u, v, [this, &res](int l, int r) { res = max(res, st.calc(l, r+1)); }); 
        return res;
    }

    void modifyNode(int u, T val) {
        st.modify(pos[u], val);
    }

    void modifySubtree(int u, T val) {
        st.modify(pos[u], pos[u] + sz[u], val);
    }
};
