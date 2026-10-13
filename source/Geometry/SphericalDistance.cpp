// Angles are radians: longitude phi and zenith angle theta (0=north pole).
double sphericalDistance(double phi1, double theta1,
                         double phi2, double theta2, double radius) {
    double dx = sin(theta2) * cos(phi2) - sin(theta1) * cos(phi1);
    double dy = sin(theta2) * sin(phi2) - sin(theta1) * sin(phi1);
    double dz = cos(theta2) - cos(theta1);
    double chord = sqrt(dx * dx + dy * dy + dz * dz);
    return radius * 2 * asin(clamp(chord / 2, 0.0, 1.0));
}
