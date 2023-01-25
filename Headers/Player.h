#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "Figures.h"
#include "Camera.h"

class Player {
 public:
  Player(const MyDouble& camera_width, const MyDouble& camera_height,
         const MyDouble& camera_depth, const Point& size,
         const Point& position, const Point& rotation,
         const Point& body_center, const MyDouble& speed);

  void Move(sf::RenderWindow& window);
  void Draw(const std::vector<Shape>& objects);
  void Display(std::ostream& out);
  void Display(sf::RenderWindow& window);

 private:
  MyDouble camera_width_, camera_height_, camera_depth_;
  Cube body_;
  Camera camera_;
  MyDouble speed_;
};