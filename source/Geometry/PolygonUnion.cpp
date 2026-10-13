// Area of the union of CCW simple polygons. O(N^2) total vertices.
using P = Point<double>;
double edgeRatio(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }

double polygonUnionArea(vector<vector<P>>& polygons) {
    double answer = 0;
    for (int i = 0; i < (int)polygons.size(); ++i) {
        for (int v = 0; v < (int)polygons[i].size(); ++v) {
            P A = polygons[i][v];
            P B = polygons[i][(v + 1) % polygons[i].size()];
            vector<pair<double, int>> events = {{0, 0}, {1, 0}};
            for (int j = 0; j < (int)polygons.size(); ++j) if (i != j) {
                for (int u = 0; u < (int)polygons[j].size(); ++u) {
                    P C = polygons[j][u];
                    P D = polygons[j][(u + 1) % polygons[j].size()];
                    int sideC = sideOf(A, B, C), sideD = sideOf(A, B, D);
                    if (sideC != sideD) {
                        double sideA = C.cross(D, A), sideB = C.cross(D, B);
                        if (min(sideC, sideD) < 0)
                            events.emplace_back(sideA / (sideA - sideB),
                                                sgn(sideC - sideD));
                    } else if (!sideC && !sideD && j < i &&
                               sgn((B - A).dot(D - C)) > 0) {
                        events.emplace_back(edgeRatio(C - A, B - A), 1);
                        events.emplace_back(edgeRatio(D - A, B - A), -1);
                    }
                }
            }
            sort(events.begin(), events.end());
            for (auto& event : events)
                event.first = clamp(event.first, 0.0, 1.0);
            double uncovered = 0;
            int cover = events[0].second;
            for (int j = 1; j < (int)events.size(); ++j) {
                if (!cover) uncovered += events[j].first - events[j - 1].first;
                cover += events[j].second;
            }
            answer += A.cross(B) * uncovered;
        }
    }
    return answer / 2;
}
