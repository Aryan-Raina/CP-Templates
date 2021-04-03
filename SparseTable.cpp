struct SparseTable {
    vector<vector<int>> table;

    SparseTable(vector<int> &a) : table(1, a) {
        for (int pw = 1, k = 1; pw*2 <= v.size(); pw *= 2, ++k) {
            table.emplace_back(v.size() - pw*2 + 1);
            for (int j = 0; j < table[k].size(); j++) 
                table[k][j] = min(table[k-1][j], table[k-1][j+pw]);
        }
    }

    int query(int l, int r) {
        int dep = 31 - __builtin_clz(r - l);
        return min(table[dep][l], table[dep][r - (1<<dep)]);
    }
};
