tuple<int64_t, int64_t, int64_t> extended_gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    int64_t gcd, x1, y1;
    tie(gcd, x1, y1) = extended_gcd(b, a % b);
    return {gcd, y1, x1 - (a / b) * y1};
}

pair<int64_t, int64_t> chinese_remainder_theorem(int64_t a1, int64_t m1, int64_t a2, int64_t m2) {
    int64_t gcd, x, y;
    std::tie(gcd, x, y) = extended_gcd(m1, m2);

    if ((a2 - a1) % gcd != 0) {
        return {0, -1};
    }

    int64_t lcm = (m1 / gcd) * m2;
    int64_t combined_solution = a1 + ((a2 - a1) / gcd * x % (m2 / gcd)) * m1;
    combined_solution = (combined_solution % lcm + lcm) % lcm;

    return {combined_solution, lcm};
}