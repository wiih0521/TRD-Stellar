// Twice the signed area: positive for CCW, negative for CW.
template<class T>
T polygonArea2(const vector<Point<T>>& polygon) {
    if (polygon.empty()) return 0;
    T area = polygon.back().cross(polygon[0]);
    for (int i = 0; i + 1 < (int)polygon.size(); ++i)
        area += polygon[i].cross(polygon[i + 1]);
    return area;
}
