// Convex polygon must be CCW with no collinear consecutive vertices.
// Returns crossed side indices; {-1,-1} means disjoint. O(log n).
template<class P>
int extremeVertex(const vector<P>& polygon, P direction) {
    int n = (int)polygon.size();
    auto compare = [&](int i, int j) {
        return sgn(direction.perp().cross(
            polygon[i % n] - polygon[j % n]));
    };
    auto extreme = [&](int i) {
        return compare(i + 1, i) >= 0 && compare(i, (i - 1 + n) % n) < 0;
    };
    int low = 0, high = n;
    if (extreme(0)) return 0;
    while (low + 1 < high) {
        int middle = (low + high) / 2;
        if (extreme(middle)) return middle;
        int leftSlope = compare(low + 1, low);
        int middleSlope = compare(middle + 1, middle);
        if (leftSlope < middleSlope ||
            (leftSlope == middleSlope && leftSlope == compare(low, middle)))
            high = middle;
        else
            low = middle;
    }
    return low;
}

template<class P>
array<int, 2> lineHull(P a, P b, const vector<P>& polygon) {
    int n = (int)polygon.size();
    assert(n >= 3 && a != b);
    auto compareLine = [&](int i) { return sgn(a.cross(polygon[i], b)); };
    int endA = extremeVertex(polygon, (a - b).perp());
    int endB = extremeVertex(polygon, (b - a).perp());
    if (compareLine(endA) < 0 || compareLine(endB) > 0) return {-1, -1};
    array<int, 2> result;
    for (int pass = 0; pass < 2; ++pass) {
        int low = endB, high = endA;
        while ((low + 1) % n != high) {
            int middle = ((low + high + (low < high ? 0 : n)) / 2) % n;
            if (compareLine(middle) == compareLine(endB)) low = middle;
            else high = middle;
        }
        result[pass] = (low + !compareLine(high)) % n;
        swap(endA, endB);
    }
    if (result[0] == result[1]) return {result[0], -1};
    if (!compareLine(result[0]) && !compareLine(result[1])) {
        switch ((result[0] - result[1] + n + 1) % n) {
            case 0: return {result[0], result[0]};
            case 2: return {result[1], result[1]};
        }
    }
    return result;
}
