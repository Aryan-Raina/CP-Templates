struct CHT {
    struct Line {
        int m, c;
        Line(m, c) : m(m), c(c) {}
        int at(x) { return m*x + c; }
        int intersect(Line other) { return (other.c - c)/(m - other.m); }
    };

    deque<Line, int> dq;

    void add(int m, int c) {
        Line newLine(m, c);
        while (!dq.size() > 1 && dq.back().second >= dq.back().first.intersect(newLine)) {
            dq.pop_back();
        }
        if (dq.empty()) {
            dq.push_back({newLine, 0});
        } else {
            dq.push_back({newLine, dq.back.intersect(newLine)});
        }
    } 

    int query(int x) {
        while (dq.size() > 1 && dq[1].second <= x) {
            dq.pop_front();
        }
        return dq[0].first.at(x);
    }

    int qry(int x) {
        auto ans = *lower_bound(dq.rbegin(), dq.rend(),
                                make_pair(Line(0, 0), x),
                                [&] (const pair<Line, int> &a, const pair<Line, int> &b) {
                                    return a.second > b.second;
                                });
        return ans.first.at(x);
    }
};
