#define pt pair<int,int>
#define X first
#define Y second

int dot(const pt &a, const pt &b) { return (a.X*b.X) + (a.Y*b.Y); }
int cross(const pt &a, const pt &b) { return (a.X*b.Y) - (b.X*a.Y); }
pt operator-(const pt &a, const pt &b) { return pt(a.X - b.X, a.Y - b.Y); }
int norm(const pt &a) { return (a.X*a.X) + (a.Y*a.Y); }

vector<int> ConvexHull(vector<pt> &v) {
    int ind = min_element(v.begin(), v.end()) - v.begin();
    vector<int> cand, hull = {ind};
    for (int i = 0; i < v.size(); i++) if (v[i] != v[ind]) cand.push_back(i);

    sort(cand.begin(), cand.end(), [&](int a, int b) {
        pt p1 = v[a] - v[ind], p2 = v[b] - v[ind];
        int t = cross(p1, p2);
        if (t == 0) return norm(p1) < norm(p2);
        return t > 0;
    });

    for (int i : cand) {
        while (hull.size() > 1 && cross(v[end(hull)[-1]] - v[end(hull)[-2]], v[i] - v[end(hull)[-2]]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(i);
    }

    return hull;
}
