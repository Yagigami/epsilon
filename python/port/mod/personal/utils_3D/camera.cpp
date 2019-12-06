#ifndef MODPERSONAL_UTILS_3D_CAMERA_CPP
#define MODPERSONAL_UTILS_3D_CAMERA_CPP

#include "camera.h"
#include <cmath>
#define PI 3.14159265358979f
#define FOV_EPSILON 0.1f

Camera::Camera(Space3_f space, float fieldOfView, float moveSpeed, float rotationSpeed, float zoomSpeed)
  : m_space(space), m_fieldOfView(fieldOfView), m_moveSpeed(moveSpeed),
    m_rotationSpeed(rotationSpeed), m_zoomSpeed(zoomSpeed)
{
  m_focalLength = cos(fieldOfView / 2) / sin(fieldOfView / 2) / 2;
}

Camera& Camera::operator+=(Vec3_f const& rhs) {
  m_space += rhs;
  return *this;
}

Camera& Camera::operator-=(Vec3_f const& rhs) {
  m_space -= rhs;
  return *this;
}

Camera& Camera::rotate_by(Vec3_f const& axis, float const& delta_time) {
  m_space.rotate_by(axis, m_rotationSpeed * delta_time);
  return *this;
}

// since we know "dir" is orthogonal to 2 axes (the other is left unchanged)
// we could optimize this
Camera& Camera::rotate_by(CameraDirection dir, float const& delta_time) {
  switch (dir) {
    case left:
      m_space.rotate_by(m_space.m_yAxis, m_rotationSpeed * delta_time);
      break;
    case right:
      m_space.rotate_by(m_space.m_yAxis, m_rotationSpeed * -delta_time);
      break;
    case up:
      m_space.rotate_by(m_space.m_xAxis, m_rotationSpeed * delta_time);
      break;
    case down:
      m_space.rotate_by(m_space.m_xAxis, m_rotationSpeed * -delta_time);
      break;
    case forwards:
      m_space.rotate_by(m_space.m_zAxis, m_rotationSpeed * delta_time);
      break;
    case backwards:
      m_space.rotate_by(m_space.m_zAxis, m_rotationSpeed * -delta_time);
      break;
  }
  return *this;
}

Camera& Camera::rotate_around_by(const Vec3_f& center, const Vec3_f& axis, const float& delta_time) {
  m_space.rotate_around_by(center, axis, m_rotationSpeed * delta_time);
  return *this;
}

Camera& Camera::rotate_around_by(const Vec3_f& center, CameraDirection dir, const float& delta_time) {
  switch (dir) {
    case left:
      m_space.rotate_around_by(center, m_space.m_yAxis, m_rotationSpeed * -delta_time);
      break;
    case right:
      m_space.rotate_around_by(center, m_space.m_yAxis, m_rotationSpeed * delta_time);
      break;
    case up:
      m_space.rotate_around_by(center, m_space.m_xAxis, m_rotationSpeed * -delta_time);
      break;
    case down:
      m_space.rotate_around_by(center, m_space.m_xAxis, m_rotationSpeed * delta_time);
      break;
    case forwards:
      m_space.rotate_around_by(center, m_space.m_zAxis, m_rotationSpeed * delta_time);
      break;
    case backwards:
      m_space.rotate_around_by(center, m_space.m_zAxis, m_rotationSpeed * -delta_time);
      break;
  }
  return *this;
}

Camera& Camera::zoom_by(float const& delta_time) {
  float tmp = m_fieldOfView - m_zoomSpeed * delta_time;
  if (tmp > 0) {
    if (tmp < PI) {
      m_fieldOfView = tmp;
    } else m_fieldOfView = PI - FOV_EPSILON;
  } else m_fieldOfView = FOV_EPSILON;
  m_focalLength = cos(m_fieldOfView / 2) / sin(m_fieldOfView / 2) / 2;
  return *this;
}

Camera& Camera::move_to(CameraDirection dir, float const& delta_time) {
  switch (dir) {
    case left:
      m_space += m_space.m_xAxis * m_moveSpeed * -delta_time;
      break;
    case right:
      m_space += m_space.m_xAxis * m_moveSpeed * delta_time;
      break;
    case up:
      m_space += m_space.m_yAxis * m_moveSpeed * delta_time;
      break;
    case down:
      m_space += m_space.m_yAxis * m_moveSpeed * -delta_time;
      break;
    case forwards:
      m_space += m_space.m_zAxis * m_moveSpeed * -delta_time;
      break;
    case backwards:
      m_space += m_space.m_zAxis * m_moveSpeed * delta_time;
      break;
  }
  return *this;
}

#endif
