#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Polygon.h"
#include "Figures.h"

class Camera {
 public:
  Camera(const MyDouble& width, const MyDouble& height, const MyDouble& depth,
         const Point& position = Point(0, 0, 0),
         const Point& rotation = Point(0, 0, 0));

  Camera& operator+=(const Point& p);
  Camera& operator-=(const Point& p);
  Camera& MoveForward(const MyDouble& distance);
  Camera& MoveLeft(const MyDouble& distance);
  Camera& MoveUp(const MyDouble& distance);

  Camera& Rotate(const Line& axis, const MyDouble& deg);
  Camera& Rotate(const Point& p, const MyDouble& deg);
  Camera& RotateAroundForwardAxis(const MyDouble& deg);
  Camera& RotateAroundLeftAxis(const MyDouble& deg);
  Camera& RotateAroundUpAxis(const MyDouble& deg);

  Line GetForwardAxis();
  Line GetLeftAxis();
  Line GetUpAxis();

  void Draw(const std::vector<Shape>& objects);
  void Display(std::ostream& out);
  void Display(sf::RenderWindow& window);


 private:
  MyDouble width_, height_;
  Polygon screen_;
  std::vector<std::vector<bool>> display_;
  Point viewer_;
  Point forward_, left_, up_;
};