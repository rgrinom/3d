#include "../Headers/Camera.h"

Camera::Camera(MyDouble width, MyDouble height, MyDouble depth,
               MyDouble x, MyDouble y, MyDouble z,
               MyDouble left_right_angle, MyDouble up_down_angle, MyDouble rotation_angle)
    : width_(width), height_(height),
      screen_({Point(depth, width / 2, height / 2), Point(depth, -width / 2, height / 2),
               Point(depth, -width / 2, -height / 2), Point(depth, width / 2, -height / 2)}),
      display_(height_.value + 1, std::vector<bool>(width_.value + 1)),
      viewer_(0, 0, 0), left_right_axis_(0, 0, 1), up_down_axis_(0, 1, 0), rotation_axis_(1, 0, 0) {
  Point pos(x, y, z);
  viewer_ += pos;
  screen_ += pos;
  
  RotateLeftRight(left_right_angle);
  RotateUpDown(up_down_angle);
  RotateRotate(rotation_angle);
}

void Camera::Rotate(const Line& axis, const MyDouble& angle) {
  screen_.Rotate(axis, angle);
  left_right_axis_.Rotate(axis, angle);
  up_down_axis_.Rotate(axis, angle);
  rotation_axis_.Rotate(axis, angle);
}

void Camera::RotateLeftRight(const MyDouble& angle) {
  Line left_right(viewer_, viewer_ + left_right_axis_);
  Rotate(left_right, angle);
}

void Camera::RotateUpDown(const MyDouble& angle) {
  Line up_down(viewer_, viewer_ + up_down_axis_);
  Rotate(up_down, angle);
}

void Camera::RotateRotate(const MyDouble& angle) {
  Line rotation(viewer_, viewer_ + rotation_axis_);
  Rotate(rotation, angle);
}

void Camera::Draw(const std::vector<Shape>& objects) {
  Point height_e = (screen_[2] - screen_[1]) / height_;
  Point width_e = (screen_[1] - screen_[0]) / width_;
  Point start_p = screen_[0];
  Plane screen_plane(screen_[0], screen_[1], screen_[2]);
  MyDouble dist_to_viewer = screen_plane.SignedDistance(viewer_);
  for (MyDouble i = 0; i <= height_; i += 1) {
    for (MyDouble j = 0; j <= width_; j += 1) {
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
        display_[i.value][j.value] = true;
      } else {
        display_[i.value][j.value] = false;
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
  image.create(width_.value, height_.value, sf::Color(0, 0, 0));
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