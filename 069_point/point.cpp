#include "point.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Point::Point() : x(0), y(0) {
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double result = std::sqrt(std::pow((x - p.x), 2) + std::pow((y - p.y), 2));
  return result;
}
