struct CHT {
    deque<pair<int,int>> d;
    
    int get(int x) {
        while (d.size() >= 2) {
            int a = d[0].first * x + d[0].second;
            int b = d[1].first * x + d[1].second;
            if (a <= b) break;
            d.pop_front();
        }
        return d[0].first * x + d[0].second;
    }

    void add(int m, int c) {
        while (d.size() >= 2) {
            int m1 = end(d)[-1].first, c1 = end(d)[-1].second;
            int m2 = end(d)[-2].first, c2 = end(d)[-2].second;
            if ((c-c1)*(m2-m) >= (c-c2)*(m1-m)) break;
            d.pop_back();
        }
        d.push_back({m, c});
    }
};
