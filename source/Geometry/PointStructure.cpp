template<class T>
struct Point {
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    
    bool operator<(Point p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(Point p) const { return tie(x, y) == tie(p.x, p.y); }
    
    Point operator+(Point p) const { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) const { return Point(x - p.x, y - p.y); }
    Point operator*(T d) const { return Point(x * d, y * d); }
    Point operator/(T d) const { return Point(x / d, y / d); }
    Point operator-() const { return Point(-x, -y); }
    
    T dot(Point p) const { return x * p.x + y * p.y; }
    T cross(Point p) const { return x * p.y - y * p.x; }
    T cross(Point a, Point b) const { return (a - *this).cross(b - *this); }
    
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    Point unit() const { return *this / dist(); }
    Point perp() const { return Point(-y, x); }
    double angle() const { return atan2(y, x); }
    
    friend istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }
    friend ostream& operator<<(ostream& os, const Point& p) { return os << p.x << " " << p.y; }
};