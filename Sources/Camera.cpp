#include "../Headers/Camera.h"

Camera::Camera(const MyDouble& width, const MyDouble& height, const MyDouble& depth,
               const Point& position, const Point& rotatrion)
    : width_(width), height_(height),
      screen_({Point(depth, width / 2, height / 2), Point(depth, -width / 2, height / 2),
               Point(depth, -width / 2, -height / 2), Point(depth, width / 2, -height / 2)}),
      display_(static_cast<size_t>(height_.value) + 1, std::vector<bool>(static_cast<size_t>(width_.value) + 1)),
      viewer_(0, 0, 0), forward_(1, 0, 0), left_(0, 1, 0), up_(0, 0, 1) {
  *this += position;
  
  RotateAroundForwardAxis(rotatrion.x);
  RotateAroundLeftAxis(rotatrion.y);
  RotateAroundUpAxis(rotatrion.z);
}

Camera& Camera::operator+=(const Point& p) {
  viewer_ += p;
  screen_ += p;
  return *this;
}

Camera& Camera::operator-=(const Point& p) {
  return (*this += -p);
}

Camera& Camera::MoveForward(const MyDouble& distance) {
  return (*this += forward_ * distance);
}

Camera& Camera::MoveLeft(const MyDouble& distance) {
  return (*this += left_ * distance);
}

Camera& Camera::MoveUp(const MyDouble& distance) {
  return (*this += up_ * distance);
}

Camera& Camera::Rotate(const Line& axis, const MyDouble& deg) {
  screen_.Rotate(axis, deg);

  forward_ += viewer_;
  left_ += viewer_;
  up_ += viewer_;

  viewer_.Rotate(axis, deg);
  forward_.Rotate(axis, deg);
  left_.Rotate(axis, deg);
  up_.Rotate(axis, deg);

  forward_ -= viewer_;
  left_ -= viewer_;
  up_ -= viewer_;

  return *this;
}

Camera& Camera::Rotate(const Point& p, const MyDouble& deg) {
  Line axis(viewer_, viewer_ + p);
  return Rotate(axis, deg);
}

Camera& Camera::RotateAroundForwardAxis(const MyDouble& deg) {
  return Rotate(forward_, deg);
}

Camera& Camera::RotateAroundLeftAxis(const MyDouble& deg) {
  return Rotate(left_, deg);
}

Camera& Camera::RotateAroundUpAxis(const MyDouble& deg) {
  return Rotate(up_, deg);
}

Line Camera::GetForwardAxis() {
  return Line(viewer_, viewer_ + forward_);
}

Line Camera::GetLeftAxis() {
  return Line(viewer_, viewer_ + left_);
}

Line Camera::GetUpAxis() {
  return Line(viewer_, viewer_ + up_);
}

void Camera::Draw(const std::vector<Shape>& objects) {
  Point height_e = (screen_[2] - screen_[1]) / height_;
  Point width_e = (screen_[1] - screen_[0]) / width_;
  Point start_p = screen_[0];
  Plane screen_plane(screen_[0], screen_[1], screen_[2]);
  MyDouble dist_to_viewer = screen_plane.SignedDistance(viewer_);
  for (size_t i = 0; i <= static_cast<size_t>(height_.value); ++i) {
    for (size_t j = 0; j <= static_cast<size_t>(width_.value); ++j) {
      Point pixel = start_p + (height_e * i) + (width_e * j);
      Line l(viewer_, pixel);
      Point intersection(constants::kInf, constants::kInf, constants::kInf);
      MyDouble dist_to_intersection = constants::kInf;
      for (size_t k = 0; k < objects.size(); ++k) {
        std::vector<Point> ret = objects[k].Intersection(l);
        for (size_t f = 0; f < ret.size(); ++f) {
          MyDouble dist_to_cur = screen_plane.SignedDistance(ret[f]);
          if ((dist_to_viewer > 0 && dist_to_cur > 0) ||
              (dist_to_viewer < 0 && dist_to_cur < 0)) {
            continue;
          }
          if (dist_to_cur < 0) {
            dist_to_cur *= -1;
          }
          if (dist_to_cur < dist_to_intersection) {
            dist_to_intersection = dist_to_cur;
            intersection = ret[f];
          }
        }
      }

      if (intersection != constants::kNotAPoint) {
        display_[i][j] = true;
      } else {
        display_[i][j] = false;
      }
    }
  }
}

void Camera::Display(std::ostream& out) {
  for (size_t i = 0; i < display_.size(); ++i) {
    for (size_t j = 0; j < display_[i].size(); ++j) {
      if (display_[i][j]) {
        out << "##";
      } else {
        out << "  ";
      }
    }
    out << "\n";
  }
}

void Camera::Display(sf::RenderWindow& window) {
  sf::Image image;
  image.create(display_.size(), display_[0].size(), sf::Color(0, 0, 0));
  for (size_t i = 0; i < display_.size(); ++i) {
    for (size_t j = 0; j < display_[i].size(); ++j) {
      if (display_[i][j]) {
        image.setPixel(j, i, sf::Color(255, 255, 255));
      }
    }
  }
  sf::Texture texture;
  texture.loadFromImage(image);
  sf::Sprite sprite;
  sprite.setTexture(texture);
  window.draw(sprite);
}