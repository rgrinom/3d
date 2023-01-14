#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Polygon.h"
#include "Figures.h"

class Camera {
 public:
  Camera(MyDouble width, MyDouble height, MyDouble depth,
         MyDouble x = 0, MyDouble y = 0, MyDouble z = 0,
         MyDouble left_right_angle = 0, MyDouble up_down_angle = 0, MyDouble rotation_angle = 0);
  void Rotate(const Line& axis, const MyDouble& angle);
  void RotateLeftRight(const MyDouble& angle);
  void RotateUpDown(const MyDouble& angle);
  void RotateRotate(const MyDouble& angle);

  void Draw(const std::vector<Shape>& objects);
  void Display(std::ostream& out);
  void Display(sf::RenderWindow& window);


 private:
  MyDouble width_, height_;
  Polygon screen_;
  std::vector<std::vector<bool>> display_;
  Point viewer_;
  Point left_right_axis_, up_down_axis_, rotation_axis_;

};