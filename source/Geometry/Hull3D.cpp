// O(n^2). Requires >=4 points and no four coplanar points.
using P3 = Point3D<double>;

struct HullEdge {
    int first = -1, second = -1;
    void insert(int x) { (first == -1 ? first : second) = x; }
    void remove(int x) { (first == x ? first : second) = -1; }
    int count() const { return (first != -1) + (second != -1); }
};

struct Face3D { P3 normal; int a, b, c; };

vector<Face3D> hull3d(const vector<P3>& points) {
    int n = (int)points.size();
    assert(n >= 4);
    vector<vector<HullEdge>> edges(n, vector<HullEdge>(n));
    vector<Face3D> faces;

    auto makeFace = [&](int i, int j, int k, int inside) {
        P3 normal = (points[j] - points[i]).cross(points[k] - points[i]);
        if (normal.dot(points[inside]) > normal.dot(points[i])) normal = normal * -1;
        Face3D face{normal, i, j, k};
        edges[i][j].insert(k); edges[i][k].insert(j); edges[j][k].insert(i);
        faces.push_back(face);
    };

    for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 4; ++j)
            for (int k = j + 1; k < 4; ++k)
                makeFace(i, j, k, 6 - i - j - k);

    for (int i = 4; i < n; ++i) {
        for (int j = 0; j < (int)faces.size(); ++j) {
            Face3D face = faces[j];
            if (face.normal.dot(points[i]) <= face.normal.dot(points[face.a])) continue;
            edges[face.a][face.b].remove(face.c);
            edges[face.a][face.c].remove(face.b);
            edges[face.b][face.c].remove(face.a);
            faces[j--] = faces.back();
            faces.pop_back();
        }
        int oldFaces = (int)faces.size();
        for (int j = 0; j < oldFaces; ++j) {
            Face3D face = faces[j];
            if (edges[face.a][face.b].count() != 2)
                makeFace(face.a, face.b, i, face.c);
            if (edges[face.a][face.c].count() != 2)
                makeFace(face.a, face.c, i, face.b);
            if (edges[face.b][face.c].count() != 2)
                makeFace(face.b, face.c, i, face.a);
        }
    }
    for (Face3D& face : faces) {
        P3 geometric = (points[face.b] - points[face.a]).cross(
                       points[face.c] - points[face.a]);
        if (geometric.dot(face.normal) <= 0) swap(face.b, face.c);
    }
    return faces;
}
