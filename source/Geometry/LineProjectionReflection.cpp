// Projection of p onto line ab; refl=true reflects p across the line.
// a == b is invalid. Use floating points for non-integral answers.
template<class P>
P lineProj(P a, P b, P p, bool refl = false) {
    P v = b - a;
    return p - v.perp() * (1 + refl) * v.cross(p - a) / v.dist2();
}
