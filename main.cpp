#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "Headers/MyDouble.h"
#include "Headers/SoLE.h"
#include "Headers/Point.h"
#include "Headers/Plane.h"
#include "Headers/Line.h"
#include "Headers/Polygon.h"
#include "Headers/Figures.h"
#include "Headers/Camera.h"

void demo() {
  std::ifstream in("Data/scene.txt");

  MyDouble cam_width, cam_height, cam_depth, cam_x, cam_y, cam_z, cam_rot1, cam_rot2, cam_rot3;
  in >> cam_width >> cam_height >> cam_depth >> cam_x >> cam_y >> cam_z >> cam_rot1 >> cam_rot2 >> cam_rot3;
  Camera cam(cam_width, cam_height, cam_depth, cam_x, cam_y, cam_z, cam_rot1, cam_rot2, cam_rot3);

  sf::RenderWindow window(sf::VideoMode(cam_width.value, cam_height.value), "Cube");

  std::vector<Shape> objects;
  size_t n;
  in >> n;
  for (size_t i = 0; i < n; ++i) {
    MyDouble x_size, y_size, z_size, x_pos, y_pos, z_pos, x_rot, y_rot, z_rot, center_x, center_y, center_z;
    in >> x_size >> y_size >> z_size >> x_pos >> y_pos >> z_pos >> x_rot >> y_rot >> z_rot >> center_x >> center_y >> center_z;
    objects.push_back(Cube(x_size, y_size, z_size, x_pos, y_pos, z_pos, x_rot, y_rot, z_rot, center_x, center_y, center_z));
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

    cam.RotateLeftRight(10);
    cam.Draw(objects);
    cam.Display(window);

    window.display();
  }
}

int main() {
  demo();
  return 0;
}