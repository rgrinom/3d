#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "MyDouble.h"
#include "SoLE.h"
#include "Point.h"
#include "Plane.h"
#include "Line.h"
#include "Polygon.h"
#include "Figures.h"
#include "Camera.h"
#include "Player.h"

void demo() {
  std::ifstream in;
  in.open("../Data/scene.txt");

  MyDouble cam_width, cam_height, cam_depth, speed;
  Point size, position, rotation, center;
  in >> cam_width >> cam_height >> cam_depth >> size >> position >> rotation >> center >> speed;
  Player player(cam_width, cam_height, cam_depth, size, position, rotation, center, speed);

  sf::RenderWindow window(sf::VideoMode(cam_width.value, cam_height.value), "Cube");
  sf::Mouse::setPosition(sf::Vector2i((cam_width / 2).value, (cam_height / 2).value), window);
  window.setMouseCursorVisible(false);

  std::vector<Shape> objects;
  size_t n;
  in >> n;
  for (size_t i = 0; i < n; ++i) {
    Point size, position, rotation, center_position;
    in >> size >> position >> rotation >> center_position;
    objects.push_back(Cube(size, position, rotation, center_position));
  }
  in.close();

  size_t frame = 0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    std::cout << "Frame " << frame++ << "\n";

    window.clear();

    player.Move(window);
    player.DrawRayCasting(objects);
    player.Display(window);

    window.display();
  }
}

int main() {
  demo();
  return 0;
}