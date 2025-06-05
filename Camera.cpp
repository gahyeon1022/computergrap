#include "Camera.h"

// TODO: fill up the following function properly 
void Camera::set_rotation(const glm::quat& _q)
{
    up_dir_ = glm::normalize(_q * glm::vec3(0.0f, 1.0f, 0.0f));
    front_dir_ = glm::normalize(_q * glm::vec3(0.0f, 0.0f, -1.0f));
    right_dir_ = glm::normalize(glm::cross(front_dir_,up_dir_));  
}

// TODO: re-write the following function properly 
const glm::quat Camera::get_rotation() const
{
  glm::mat3 R(right_dir_, up_dir_, -front_dir_);
  return glm::quat_cast(R);
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::quat& _q, const glm::vec3& _t)
{
  set_rotation(_q);
  position_ = _t;
}

// TODO: fill up the following function properly 
void Camera::get_pose(glm::quat& _q, glm::vec3& _t) const
{
  _q = get_rotation();
  _t = position_;
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_pose() const
{
  glm::mat4 R = glm::mat4_cast(get_rotation());
  glm::mat4 T = glm::translate(glm::mat4(1.0f), position_);
  return T * R;
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::mat4& _frame)
{
  // +x_cam: right direction of the camera    (it should be a unit vector whose length is 1)
  // right_dir_ = ..... ; // +x
  // +y_cam: up direction of the camera       (it should be a unit vector whose length is 1)   
  // up_dir_    = ..... ;    // +y
  // -z_cam: front direction of the camera    (it should be a unit vector whose length is 1)
  // front_dir_ = ..... ;    // -z
  // pos_cam: position of the camera
  // position_  = ..... ;    // pos
  right_dir_  = glm::normalize(glm::vec3(_frame[0]));
  up_dir_     = glm::normalize(glm::vec3(_frame[1]));
  front_dir_  = -glm::normalize(glm::vec3(_frame[2]));
  position_   = glm::vec3(_frame[3]);
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::vec3& _pos, const glm::vec3& _at, const glm::vec3& _up_dir)
{
  // up_dir_    = ..... ;
  // front_dir_ = ..... ;    // -z_cam direction
  // right_dir_ = ..... ;    // +x_cam direction
  // up_dir_    = ..... ;    // +y_cam direction

  // position_  = ..... ;      // pos
  position_   = _pos;
  front_dir_  = glm::normalize(_at - _pos);
  right_dir_  = glm::normalize(glm::cross(front_dir_, _up_dir));
  up_dir_     = glm::normalize(glm::cross(right_dir_, front_dir_));
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_view_matrix() const
{
  return glm::lookAt(position_, position_ + front_dir_, up_dir_);
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_projection_matrix() const
{
  // TODO: Considering the followings,
  //       You must return a proper projection matrix
  //       i) camera mode: it can be either kOrtho or kPerspective
  //       ii) zoom-in/-out: if the camera mode is kOrtho, 
  //                         utilize ortho_scale_ for zoom-in/-out
  //                         if the camera mode is kPerspective,
  //                         utilize fovy_ for zoom-in/-out
  //       iii) aspect ratio: utilize aspect_ in the both camera modes
  //       iv) near/far clipping planes: utilize near_, far_

  if (mode_ == Camera::kPerspective)
  {
    return glm::perspective(glm::radians(fovy_), aspect_, near_, far_);
  }
  else // kOrtho
  {
    float scale = ortho_scale_;
    float right = scale * aspect_;
    float left = -right;
    float top = scale;
    float bottom = -top;
    return glm::ortho(left, right, bottom, top, near_, far_);
  }
}

// TODO: fill up the following functions properly 
void Camera::move_forward(float delta)
{
  position_ += front_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_backward(float delta)
{
  position_ -= front_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_left(float delta)
{
  position_ -= right_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_right(float delta)
{
  position_ += right_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_up(float delta)
{
  position_ += up_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_down(float delta)
{
  position_ -= up_dir_ * delta;
}
