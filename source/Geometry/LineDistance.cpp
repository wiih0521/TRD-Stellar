// Signed distance from p to directed line a->b. Positive on the left.
// a == b is invalid. Products may overflow for large integer coordinates.
template<class P>
double lineDist(P a, P b, P p) {
    return (double)(b - a).cross(p - a) / (b - a).dist();
}
