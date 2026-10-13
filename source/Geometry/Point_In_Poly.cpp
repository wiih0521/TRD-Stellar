/* 
 * Usage : 
 * Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary.
 * The algorithm uses products in intermediate steps so watch out for overflow.
 * Time complexity : O(n)
*/

template<class P>
bool inPolygon(const vector<P>& polygon, P point, bool strict = true) {
    int inside = 0, n = (int)polygon.size();
    for (int i = 0; i < n; ++i) {
        P next = polygon[(i + 1) % n];
        if (onSegment(polygon[i], next, point)) return !strict;
        inside ^= ((point.y < polygon[i].y) - (point.y < next.y)) *
                  point.cross(polygon[i], next) > 0;
    }
    return inside;
}
