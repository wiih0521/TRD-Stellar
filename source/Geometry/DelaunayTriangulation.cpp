// O(n^2) Delaunay via lifting to a 3D hull.
// Undefined for 3 collinear or 4 cocircular input points.
template<class P, class TriangleCallback>
void delaunay(vector<P>& points, TriangleCallback addTriangle) {
    if (points.size() < 3) return;
    if (points.size() == 3) {
        int reversed = points[0].cross(points[1], points[2]) < 0;
        addTriangle(0, 1 + reversed, 2 - reversed);
        return;
    }
    vector<P3> lifted;
    for (P point : points)
        lifted.emplace_back(point.x, point.y, point.dist2());
    for (auto face : hull3d(lifted)) {
        P3 normal = (lifted[face.b] - lifted[face.a]).cross(
                    lifted[face.c] - lifted[face.a]);
        if (normal.dot(P3(0, 0, 1)) < 0)
            addTriangle(face.a, face.c, face.b);
    }
}
