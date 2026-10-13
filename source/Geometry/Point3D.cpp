template<class T>
struct Point3D {
    using P = Point3D;
    T x, y, z;
    explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(P p) const { return tie(x, y, z) < tie(p.x, p.y, p.z); }
    bool operator==(P p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }
    P operator+(P p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(P p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(P p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(P p) const {
        return P(y * p.z - z * p.y,
                 z * p.x - x * p.z,
                 x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    double phi() const { return atan2(y, x); }
    double theta() const { return atan2(hypot((double)x, (double)y), z); }
    P unit() const { return *this / dist(); }
    P normal(P p) const { return cross(p).unit(); }
    P rotate(double angle, P axis) const {
        double sine = sin(angle), cosine = cos(angle);
        P unitAxis = axis.unit();
        return unitAxis * dot(unitAxis) * (1 - cosine) +
               (*this) * cosine - cross(unitAxis) * sine;
    }
};
