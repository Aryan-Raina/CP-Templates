const int MXN = 2e5+9;
vector<int> sz(MXN), g[MXN], d(MXN);
bool dead[MXN];
void get_sz(int u, int pu) {
    sz[u] = 1;
    for (int v : g[u]) if (v != pu && !dead[v]) {
        get_sz(v, u); sz[u] += sz[v];
    }
}

int centroid(int u, int pu, int rt) {
    for (int v : g[u]) if (v != pu && !dead[v]) {
        if (sz[v] > sz[rt]/2) return centroid(v, u, rt);
    }
    return u;
}

void decompose(int rt) {
    get_sz(rt, rt); int cent = centroid(rt, rt, rt);
    // do stuff
    dead[cent] = 1;
    for (int v : g[cent]) if (!dead[v]) decompose(v);
    dead[cent] = 0;
}
