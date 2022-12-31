#include "../Headers/Figures.h"

Cube::Cube(MyDouble x, MyDouble y, MyDouble z,
           MyDouble x_size, MyDouble y_size, MyDouble z_size,
           MyDouble x_angle, MyDouble y_angle, MyDouble z_angle,
           MyDouble center_x, MyDouble center_y, MyDouble center_z)
      : Shape({Polygon({Point(0, 0, 0), Point(1, 0, 0), Point(1, 1, 0), Point(0, 1, 0)}),
               Polygon({Point(0, 0, 0), Point(1, 0, 0), Point(1, 0, 1), Point(0, 0, 1)}),
               Polygon({Point(0, 0, 0), Point(0, 1, 0), Point(0, 1, 1), Point(0, 0, 1)}),
               Polygon({Point(0, 0, 1), Point(1, 0, 1), Point(1, 1, 1), Point(0, 1, 1)}),
               Polygon({Point(0, 1, 0), Point(1, 1, 0), Point(1, 1, 1), Point(0, 1, 1)}),
               Polygon({Point(1, 0, 0), Point(1, 1, 0), Point(1, 1, 1), Point(1, 0, 1)})},
              x, y, z, x_size, y_size, z_size, x_angle, y_angle, z_angle, center_x, center_y, center_z) {
}