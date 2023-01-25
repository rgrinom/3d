#include "../Headers/Player.h"

Player::Player(const MyDouble& camera_width, const MyDouble& camera_height,
               const MyDouble& camera_depth, const Point& size,
               const Point& position, const Point& rotation,
               const Point& body_center, const MyDouble& speed)
    : camera_width_(camera_width), camera_height_(camera_height), camera_depth_(camera_depth),
      body_(size, position, rotation, body_center),
      camera_(camera_width, camera_height, camera_depth,
              position + Point(size.x - body_center.x, 0, size.z - body_center.z),
              rotation), speed_(speed) {}

void Player::Move(sf::RenderWindow& window) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    body_.MoveForward(speed_);
    camera_.MoveForward(speed_);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    body_.MoveForward(-speed_);
    camera_.MoveForward(-speed_);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    body_.MoveLeft(speed_);
    camera_.MoveLeft(speed_);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    body_.MoveLeft(-speed_);
    camera_.MoveLeft(-speed_);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
    body_.MoveUp(speed_);
    camera_.MoveUp(speed_);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
    body_.MoveUp(-speed_);
    camera_.MoveUp(-speed_);
  }

  MyDouble mouse_x = sf::Mouse::getPosition(window).x;
  MyDouble mouse_y = sf::Mouse::getPosition(window).y;
  MyDouble delta_x = mouse_x - camera_width_ / 2;
  MyDouble delta_y = mouse_y - camera_height_ / 2;
  MyDouble left_deg = -RadToDeg(std::asin((delta_x / camera_depth_).value));
  MyDouble up_deg = RadToDeg(std::asin((delta_y / camera_depth_).value));
  
  body_.RotateAroundUpAxis(left_deg);
  Line up_axis = body_.GetUpAxis();
  camera_.Rotate(up_axis, left_deg);
  camera_.RotateAroundLeftAxis(up_deg);

  sf::Mouse::setPosition(sf::Vector2i((camera_width_ / 2).value, (camera_height_ / 2).value), window);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    camera_.RotateAroundForwardAxis(-10);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    camera_.RotateAroundForwardAxis(10);
  }
}

void Player::Draw(const std::vector<Shape>& objects) {
  camera_.Draw(objects);
}

void Player::Display(std::ostream& out) {
  camera_.Display(out);
}

void Player::Display(sf::RenderWindow& window) {
  camera_.Display(window);
}