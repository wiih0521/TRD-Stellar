// Signed volume; triangular faces must point outwards.
template<class Points, class Faces>
double signedPolyVolume(const Points& points, const Faces& faces) {
    double volume = 0;
    for (auto face : faces) {
        auto normal = points[face.a].cross(points[face.b]);
        volume += normal.dot(points[face.c]);
    }
    return volume / 6;
}
