#pragma once

#include <iostream>
#include <fstream>

#include "Polygon.h"
#include "Figures.h"

class Camera {
 public:
  Camera(MyDouble width, MyDouble height, MyDouble depth,
         MyDouble x = 0, MyDouble y = 0, MyDouble z = 0,
         MyDouble left_right_angle = 0, MyDouble up_down_angle = 0, MyDouble rotation_angle = 0);
  
  void Draw(const std::vector<Shape>& objects, std::ostream& out);

 private:
  MyDouble width_, height_;
  Polygon screen_;
  Point viewer_;
  Point left_right_axis_, up_down_axis_, rotation_axis_;
};