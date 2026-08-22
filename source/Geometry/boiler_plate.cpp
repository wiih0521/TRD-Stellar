
/*
	Just some good old boiler plate code
*/

struct PointRect{
    double x, y;
    PointRect(){}
    PointRect(double _x, double _y){
        x = _x, y = _y;
    }
};

struct PointPolar{
    double theta, len;
    PointPolar(){}
    PointPolar(double _theta, double _len){
        theta = _theta; len = _len;
    }
};

const double PI = acos(0) * 2;

PointPolar toPolar(PointRect p){
    double x = p.x, y = p.y;
    double len = sqrt(p.x * p.x + p.y * p.y);
    if (x== 0){
        if (y>= 0) return PointPolar(PI / 2, sqrt(p.x * p.x + p.y * p.y));
        return PointPolar(PI * 3 / 2, sqrt(p.x * p.x + p.y * p.y));
    }
    if (y == 0){
        if (x > 0) return PointPolar(0, sqrt(p.x * p.x + p.y * p.y));
        return PointPolar(PI,sqrt(p.x * p.x + p.y * p.y));
    }

    double more = 0;
    while(x < 0 || y < 0){
        more += PI / 2;
        swap(x, y);
        y = -y;
    }
    return PointPolar(more + atan(y / x), len);
}

PointRect toRect(PointPolar p){
    double theta = p.theta, len = p.len;
    int cnt = 0;
    while(theta >= PI / 2) {
        theta -= PI / 2; cnt++;
    }
    PointRect v = PointRect(cos(theta) * len, sin(theta) * len);
    while(cnt--){
        v.y = -v.y;
        swap(v.x, v.y);
    }
    return v;
}

double getArea(PointRect a, PointRect b, PointRect c){
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}


array<double, 3> getFunction(pair<PointRect, PointRect> x){
    array<double, 3> ans;
    ans[0] = x.first.y - x.second.y;
    ans[1] = x.second.x - x.first.x;
    ans[2] = -(ans[0] * x.first.x + ans[1] * x.first.y);
    return ans;
}

PointRect getIntersection(pair<PointRect, PointRect> line1, pair<PointRect, PointRect> line2){
    array<double, 3> slope1 = getFunction(line1), slope2 =getFunction(line2);
    double delta = (slope1[1] * slope2[0] - slope2[1] * slope1[0]);
    if (abs(delta) <= EPS) return PointRect(INF * 2, INF * 2);
    double y = -(slope1[2] * slope2[0] - slope2[2] * slope1[0]) / delta;
    double x = (slope1[2] * slope2[1] - slope2[2] * slope1[1]) / delta;
    return PointRect(x, y);
}

void find_convex_hull(vector<PointRect> &a){
    if (a.size() <= 2) return;
    sort(ALL(a), [] (PointRect x, PointRect y){
        if (x.x != y.x) return x.x < y.x;
        return x.y < y.y;
    });
 
    PointRect l = a[0], r = a.back();
    vector<PointRect> up, down;
    up.push_back(l); down.push_back(l);
    for(long i = 1; i<a.size(); ++i){
        if (getArea(l, r, a[i]) >= 0){
            while(up.size() > 1 && getArea(up[up.size() - 2], up[up.size() - 1], a[i]) > 0) up.pop_back();
            up.push_back(a[i]);
        }
        if (getArea(l, r, a[i]) <= 0){
            while(down.size() > 1 && getArea(down[down.size() - 2], down[down.size() - 1], a[i]) < 0) down.pop_back();
            down.push_back(a[i]);
        }
    }
    a = up;
    for(long i = down.size() - 2; i>=1; --i) a.push_back(down[i]);
}

