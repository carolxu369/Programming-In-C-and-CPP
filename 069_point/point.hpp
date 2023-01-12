/* write your class interface in this file
   write function definitions only if they are very short
 */
class Point {
 private:
  double x;
  double y;

 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};
