#include "circle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Circle::Circle(Point center, double radius) : center(center), radius(radius) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double c1_r = radius;

  double c2_r = otherCircle.radius;

  double distance = center.distanceFrom(otherCircle.center);

  double r_diff;
  double small_r;
  if (c1_r >= c2_r) {
    r_diff = c1_r - c2_r;
    small_r = c2_r;
  }
  else {
    r_diff = c2_r - c1_r;
    small_r = c1_r;
  }

  if (distance >= (c1_r + c2_r)) {
    return 0.0;
  }

  else if (distance <= r_diff) {
    return M_PI * small_r * small_r;
  }

  else {
    double d1 =
        (std::pow(c1_r, 2) - std::pow(c2_r, 2) + std::pow(distance, 2)) / (2 * distance);
    double d2 = distance - d1;
    double result = (std::pow(c1_r, 2)) * (std::acos(d1 / c1_r)) -
                    d1 * std::sqrt(std::pow(c1_r, 2) - std::pow(d1, 2)) +
                    (std::pow(c2_r, 2)) * (std::acos(d2 / c2_r)) -
                    d2 * std::sqrt(std::pow(c2_r, 2) - std::pow(d2, 2));

    return result;
  }
}
