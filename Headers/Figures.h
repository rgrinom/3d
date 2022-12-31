#pragma once

#include "Shape.h"

class Cube: Shape {
 public:
  Cube(MyDouble x = 0, MyDouble y = 0, MyDouble z = 0,
       MyDouble x_size = 1, MyDouble y_size = 1, MyDouble z_size = 1,
       MyDouble x_angle = 0, MyDouble y_angle = 0, MyDouble z_angle = 0,
       MyDouble center_x = 0, MyDouble center_y = 0, MyDouble center_z = 0);
};