// O(n log n) Delaunay triangulation for distinct integer points.
// Collinear sets return no triangles. Coordinates should fit __int128 products.
using DPoint = Point<ll>;
using WideInt = __int128_t;
struct DelaunayQuad;
using DQuad = DelaunayQuad*;

const DPoint DELAUNAY_NONE(LLONG_MAX, LLONG_MAX);
struct DelaunayQuad {
    DQuad rot, nextEdge;
    DPoint point = DELAUNAY_NONE;
    bool marked = false;
    DPoint& destination() { return reverse()->point; }
    DQuad& reverse() { return rot->rot; }
    DQuad previous() { return rot->nextEdge->rot; }
    DQuad next() { return reverse()->previous(); }
};

DQuad delaunayFreeList = nullptr;

bool inCircumcircle(DPoint p, DPoint a, DPoint b, DPoint c) {
    WideInt p2 = p.dist2();
    WideInt A = (WideInt)a.dist2() - p2;
    WideInt B = (WideInt)b.dist2() - p2;
    WideInt C = (WideInt)c.dist2() - p2;
    return (WideInt)p.cross(a, b) * C +
           (WideInt)p.cross(b, c) * A +
           (WideInt)p.cross(c, a) * B > 0;
}

DQuad makeDelaunayEdge(DPoint origin, DPoint destination) {
    DQuad edge;
    if (delaunayFreeList) {
        edge = delaunayFreeList;
        delaunayFreeList = edge->nextEdge;
    } else {
        DQuad q0 = new DelaunayQuad{};
        DQuad q1 = new DelaunayQuad{};
        DQuad q2 = new DelaunayQuad{};
        DQuad q3 = new DelaunayQuad{};
        q0->rot = q1; q1->rot = q2; q2->rot = q3; q3->rot = q0;
        edge = q0;
    }
    for (int i = 0; i < 4; ++i) {
        edge = edge->rot;
        edge->point = DELAUNAY_NONE;
        edge->marked = false;
        edge->nextEdge = (i & 1) ? edge : edge->reverse();
    }
    edge->point = origin;
    edge->destination() = destination;
    return edge;
}

void spliceDelaunay(DQuad a, DQuad b) {
    swap(a->nextEdge->rot->nextEdge, b->nextEdge->rot->nextEdge);
    swap(a->nextEdge, b->nextEdge);
}

DQuad connectDelaunay(DQuad a, DQuad b) {
    DQuad edge = makeDelaunayEdge(a->destination(), b->point);
    spliceDelaunay(edge, a->next());
    spliceDelaunay(edge->reverse(), b);
    return edge;
}

pair<DQuad, DQuad> delaunayRec(const vector<DPoint>& points) {
    int n = (int)points.size();
    if (n <= 3) {
        DQuad a = makeDelaunayEdge(points[0], points[1]);
        DQuad b = makeDelaunayEdge(points[1], points.back());
        if (n == 2) return {a, a->reverse()};
        spliceDelaunay(a->reverse(), b);
        auto side = points[0].cross(points[1], points[2]);
        DQuad c = side ? connectDelaunay(b, a) : nullptr;
        return {side < 0 ? c->reverse() : a,
                side < 0 ? c : b->reverse()};
    }

    int half = n / 2;
    DQuad leftInner, rightInner, leftOuter, rightOuter;
    tie(leftOuter, leftInner) = delaunayRec(
        vector<DPoint>(points.begin(), points.begin() + half));
    tie(rightInner, rightOuter) = delaunayRec(
        vector<DPoint>(points.begin() + half, points.end()));
    while ((rightInner->point.cross(leftInner->destination(), leftInner->point) < 0 &&
            (leftInner = leftInner->next())) ||
           (leftInner->point.cross(rightInner->destination(), rightInner->point) > 0 &&
            (rightInner = rightInner->reverse()->nextEdge))) {}

    DQuad base = connectDelaunay(rightInner->reverse(), leftInner);
    if (leftInner->point == leftOuter->point) leftOuter = base->reverse();
    if (rightInner->point == rightOuter->point) rightOuter = base;

    auto valid = [&](DQuad edge) {
        return edge->destination().cross(base->destination(), base->point) > 0;
    };
    auto removeBad = [&](DQuad initial, bool followNextEdge) {
        DQuad edge = followNextEdge ? initial->nextEdge : initial->previous();
        if (valid(edge)) {
            auto advance = [&](DQuad q) {
                return followNextEdge ? q->nextEdge : q->previous();
            };
            while (inCircumcircle(advance(edge)->destination(),
                                  base->destination(), base->point,
                                  edge->destination())) {
                DQuad next = advance(edge);
                spliceDelaunay(edge, edge->previous());
                spliceDelaunay(edge->reverse(), edge->reverse()->previous());
                edge->nextEdge = delaunayFreeList;
                delaunayFreeList = edge;
                edge = next;
            }
        }
        return edge;
    };

    while (true) {
        DQuad leftCandidate = removeBad(base->reverse(), true);
        DQuad rightCandidate = removeBad(base, false);
        if (!valid(leftCandidate) && !valid(rightCandidate)) break;
        if (!valid(leftCandidate) ||
            (valid(rightCandidate) &&
             inCircumcircle(rightCandidate->destination(), base->destination(),
                            base->point, leftCandidate->destination())))
            base = connectDelaunay(rightCandidate, base->reverse());
        else
            base = connectDelaunay(base->reverse(), leftCandidate->reverse());
    }
    return {leftOuter, rightOuter};
}

// Flat output: every consecutive triple is one CCW triangle.
vector<DPoint> fastDelaunay(vector<DPoint> points) {
    sort(points.begin(), points.end());
    assert(unique(points.begin(), points.end()) == points.end());
    if (points.size() < 2) return {};
    DQuad edge = delaunayRec(points).first;
    while (edge->nextEdge->destination().cross(edge->destination(), edge->point) < 0)
        edge = edge->nextEdge;

    vector<DQuad> queue;
    vector<DPoint> result;
    auto addFace = [&](DQuad start) {
        DQuad current = start;
        do {
            current->marked = true;
            result.push_back(current->point);
            queue.push_back(current->reverse());
            current = current->next();
        } while (current != start);
    };
    addFace(edge);
    result.clear(); // discard the outer face
    for (int i = 0; i < (int)queue.size(); ++i)
        if (!queue[i]->marked) addFace(queue[i]);
    return result;
}
