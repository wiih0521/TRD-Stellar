// Maps p0->p1 to q0->q1 by translation, rotation and scaling, then maps r.
// Requires p0 != p1. Intended for Point<double>.
using P = Point<double>;
P linearTransformation(P p0, P p1, P q0, P q1, P r) {
    P dp = p1 - p0, dq = q1 - q0;
    P num(dp.cross(dq), dp.dot(dq));
    return q0 + P((r - p0).cross(num), (r - p0).dot(num)) / dp.dist2();
}
