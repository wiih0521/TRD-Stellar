// Exact integer-angle ordering with an explicit number of full rotations.
struct Angle {
    int x, y, turns;
    Angle(int x, int y, int turns = 0) : x(x), y(y), turns(turns) {}
    Angle operator-(Angle b) const { return {x - b.x, y - b.y, turns}; }
    int half() const {
        assert(x || y);
        return y < 0 || (y == 0 && x < 0);
    }
    Angle t90() const { return {-y, x, turns + (half() && x >= 0)}; }
    Angle t180() const { return {-x, -y, turns + half()}; }
    Angle t360() const { return {x, y, turns + 1}; }
};

bool operator<(Angle a, Angle b) {
    return make_tuple(a.turns, a.half(), a.y * (ll)b.x) <
           make_tuple(b.turns, b.half(), a.x * (ll)b.y);
}

pair<Angle, Angle> segmentAngles(Angle a, Angle b) {
    if (b < a) swap(a, b);
    return b < a.t180() ? make_pair(a, b) : make_pair(b, a.t360());
}

Angle operator+(Angle a, Angle b) {
    Angle r(a.x + b.x, a.y + b.y, a.turns);
    if (a.t180() < r) --r.turns;
    return r.t180() < a ? r.t360() : r;
}

Angle angleDiff(Angle a, Angle b) {
    int turns = b.turns - a.turns;
    a.turns = b.turns;
    return {a.x * b.x + a.y * b.y,
            a.x * b.y - a.y * b.x,
            turns - (b < a)};
}
