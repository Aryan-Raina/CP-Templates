template<class T> struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(const T &x, const T &y) : x(x), y(y) {}
    Point(T ang) : x(cos(ang)), y(sin(ang)) {}

    void swap(Point &other) { swap(x, other.x), swap(y, other.y); }

    bool operator<(Point p) { return tie(x, y) < tie(p.x, p.y); }
    bool operator>(Point p) { return tie(x, y) > tie(p.x, p.y); }
    bool operator<=(Point p) { return tie(x, y) <= tie(p.x, p.y); }
    bool operator>=(Point p) { return tie(x, y) >= tie(p.x, p.y); }
    bool operator==(Point p) { return tie(x, y) == tie(p.x, p.y); }
    bool operator!=(Point p) { return tie(x, y) != tie(p.x, p.y); }

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(T d) { return Point(d*x, d*y); }
    Point operator/(T d) { return Point(x/d, y/d); }

    T dot(Point p) { return x*p.x + y*p.y; }
    T cross(Point p) { return x*p.y - y*p.x; }
    T cross(Point a, Point b) { return (a - *this).cross(b - *this); }
    T norm() { return x*x + y*y; }
    T abs() { return sqrt((double)norm()); }
    T angle() { return atan2(y, x); }
    Point unit() { return *this/abs(); }
    Point perp() { return Point(-y, x); }
    Point conj() { return Point(x, -y); }
    Point rotate(double a) { return Point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a)); }

    friend ostream& operator<<(ostream &os, Point p) { 
        return os<<"("<<p.x<<" "<<p.y<<")"; 
    }
};
