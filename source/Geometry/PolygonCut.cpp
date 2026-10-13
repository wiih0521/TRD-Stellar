// Removes everything strictly left of directed line s->e.
// Boundary points are kept. Intended for Point<double>.
using P = Point<double>;
vector<P> polygonCut(const vector<P>& polygon, P s, P e) {
    vector<P> result;
    for (int i = 0; i < (int)polygon.size(); ++i) {
        P current = polygon[i];
        P previous = i ? polygon[i - 1] : polygon.back();
        double a = s.cross(e, current), b = s.cross(e, previous);
        if ((a < 0) != (b < 0))
            result.push_back(current + (previous - current) * (a / (a - b)));
        if (a < 0) result.push_back(current);
    }
    return result;
}
