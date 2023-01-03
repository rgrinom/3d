#include "../Headers/Camera.h"

Camera::Camera(MyDouble width, MyDouble height, MyDouble depth,
               MyDouble x, MyDouble y, MyDouble z,
               MyDouble left_right_angle, MyDouble up_down_angle, MyDouble rotation_angle)
    : width_(width), height_(height),
      screen_({Point(depth, width / 2, height / 2), Point(depth, -width / 2, height / 2),
               Point(depth, -width / 2, -height / 2), Point(depth, width / 2, -height / 2)}),
      viewer_(0, 0, 0), left_right_axis_(0, 0, 1), up_down_axis_(0, 1, 0), rotation_axis_(1, 0, 0) {
  Point pos(x, y, z);
  viewer_ += pos;
  screen_ += pos;
  
  Line left_right(viewer_, viewer_ + left_right_axis_);
  screen_.Rotate(left_right, left_right_angle);
  up_down_axis_.Rotate(left_right, left_right_angle);
  rotation_axis_.Rotate(left_right, left_right_angle);

  Line up_down(viewer_, viewer_ + up_down_axis_);
  screen_.Rotate(up_down, up_down_angle);
  left_right_axis_.Rotate(up_down, up_down_angle);
  rotation_axis_.Rotate(up_down, up_down_angle);

  Line rotation(viewer_, viewer_ + rotation_axis_);
  screen_.Rotate(rotation, rotation_angle);
  left_right_axis_.Rotate(rotation, rotation_angle);
  up_down_axis_.Rotate(rotation, rotation_angle);
}

void Camera::Draw(const std::vector<Shape>& objects, std::ostream& out) {
  Point height_e = (screen_[2] - screen_[1]) / height_;
  Point width_e = (screen_[1] - screen_[0]) / width_;
  Point start_p = screen_[0];
  Plane screen_plane(screen_[0], screen_[1], screen_[2]);
  MyDouble dist_to_viewer = screen_plane.Distance(viewer_);
  for (MyDouble i = 0; i <= height_; i += 1) {
    for (MyDouble j = 0; j <= width_; j += 1) {
      Point pixel = start_p + (height_e * i) + (width_e * j);
      Line l(viewer_, pixel);
      Point intersection(constants::kInf, constants::kInf, constants::kInf);
      MyDouble dist_to_intersection = constants::kInf;
      for (size_t k = 0; k < objects.size(); ++k) {
        std::vector<Point> ret = objects[k].Intersection(l);
        for (size_t f = 0; f < ret.size(); ++f) {
          MyDouble dist_to_cur = screen_plane.Distance(ret[f]);
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
      if (intersection != Point(constants::kInf, constants::kInf, constants::kInf)) {
        out << "##";
      } else {
        out << "  ";
      }
    }
    out << "\n";
  }
}