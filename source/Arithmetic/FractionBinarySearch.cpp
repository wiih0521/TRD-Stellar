struct Fraction { ll p, q; };

// Smallest p/q in [0,1] satisfying monotone predicate f, with p,q <= limit.
template<class F>
Fraction fractionBinarySearch(F f, ll limit) {
    bool direction = true, active = true, previousActive = true;
    Fraction low{0, 1}, high{1, 1};
    if (f(low)) return low;
    assert(f(high));
    while (active || previousActive) {
        ll advance = 0, step = 1;
        for (int stop = 0; step; (step *= 2) >>= stop) {
            advance += step;
            Fraction middle{
                low.p * advance + high.p,
                low.q * advance + high.q
            };
            if (abs(middle.p) > limit || middle.q > limit
                    || direction == !f(middle)) {
                advance -= step;
                stop = 2;
            }
        }
        high.p += low.p * advance;
        high.q += low.q * advance;
        direction = !direction;
        swap(low, high);
        active = previousActive;
        previousActive = (advance != 0);
    }
    return direction ? high : low;
}
