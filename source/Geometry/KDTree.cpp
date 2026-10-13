// Static 2D KD-tree for nearest-neighbor queries on integer points.
using KDValue = long long;
using KDPoint = Point<KDValue>;

struct KDNode {
    KDPoint point;
    KDValue x0 = LLONG_MAX, x1 = LLONG_MIN;
    KDValue y0 = LLONG_MAX, y1 = LLONG_MIN;
    unique_ptr<KDNode> first, second;

    explicit KDNode(vector<KDPoint> points) : point(points[0]) {
        for (KDPoint p : points) {
            x0 = min(x0, p.x); x1 = max(x1, p.x);
            y0 = min(y0, p.y); y1 = max(y1, p.y);
        }
        if (points.size() <= 1) return;
        bool splitX = x1 - x0 >= y1 - y0;
        sort(points.begin(), points.end(), [&](KDPoint a, KDPoint b) {
            return splitX ? tie(a.x, a.y) < tie(b.x, b.y)
                          : tie(a.y, a.x) < tie(b.y, b.x);
        });
        int half = (int)points.size() / 2;
        first = make_unique<KDNode>(vector<KDPoint>(points.begin(), points.begin() + half));
        second = make_unique<KDNode>(vector<KDPoint>(points.begin() + half, points.end()));
    }

    KDValue boxDistance(KDPoint p) const {
        KDValue x = clamp(p.x, x0, x1), y = clamp(p.y, y0, y1);
        return (KDPoint(x, y) - p).dist2();
    }
};

struct KDTree {
    unique_ptr<KDNode> root;
    explicit KDTree(const vector<KDPoint>& points) {
        assert(!points.empty());
        root = make_unique<KDNode>(points);
    }

    pair<KDValue, KDPoint> search(const KDNode* node, KDPoint query) const {
        if (!node->first)
            return {(query - node->point).dist2(), node->point};
        const KDNode *first = node->first.get(), *second = node->second.get();
        KDValue firstBound = first->boxDistance(query);
        KDValue secondBound = second->boxDistance(query);
        if (firstBound > secondBound) {
            swap(firstBound, secondBound);
            swap(first, second);
        }
        auto best = search(first, query);
        if (secondBound < best.first) best = min(best, search(second, query));
        return best;
    }

    pair<KDValue, KDPoint> nearest(KDPoint query) const {
        return search(root.get(), query);
    }
};
