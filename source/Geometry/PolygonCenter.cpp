// Center of mass of a non-degenerate polygon. Orientation may be CW or CCW.
using P = Point<double>;
P polygonCenter(const vector<P>& polygon) {
    P result(0, 0);
    double area2 = 0;
    for (int i = 0, j = (int)polygon.size() - 1;
         i < (int)polygon.size(); j = i++) {
        double cross = polygon[j].cross(polygon[i]);
        result = result + (polygon[i] + polygon[j]) * cross;
        area2 += cross;
    }
    assert(area2 != 0);
    return result / area2 / 3;
}
