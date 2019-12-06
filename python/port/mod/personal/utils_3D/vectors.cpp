#ifndef MODPERSONAL_UTILS_3D_VECTORS_CPP
#define MODPERSONAL_UTILS_3D_VECTORS_CPP

#include "vectors.h"
#include <cmath> // we need sqrt(), sin() and cos()

Vec3_f Vec3_f::operator+(const Vec3_f& rhs) const {
  return { m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z };
}
Vec3_f Vec3_f::operator-(const Vec3_f& rhs) const {
  return { m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z };
}
Vec3_f Vec3_f::operator-() const {
  return { -m_x, -m_y, -m_z };
}
Vec3_f Vec3_f::operator*(const float& scalingFactor) const {
  return { m_x * scalingFactor, m_y * scalingFactor, m_z * scalingFactor };
}
Vec3_f Vec3_f::operator/(const float& divide) const {
  return { m_x / divide, m_y / divide, m_z / divide };
}

Vec3_f& Vec3_f::operator+=(const Vec3_f& rhs) {
  m_x += rhs.m_x;
  m_y += rhs.m_y;
  m_z += rhs.m_z;
  return *this;
}
Vec3_f& Vec3_f::operator-=(const Vec3_f& rhs) {
  m_x -= rhs.m_x;
  m_y -= rhs.m_y;
  m_z -= rhs.m_z;
  return *this;
}
Vec3_f& Vec3_f::operator*=(const float& scalingFactor) {
  m_x *= scalingFactor;
  m_y *= scalingFactor;
  m_z *= scalingFactor;
  return *this;
}
Vec3_f& Vec3_f::operator/=(const float& divide) {
  m_x /= divide;
  m_y /= divide;
  m_z /= divide;
  return *this;
}

float Vec3_f::dot(const Vec3_f& rhs) const {
  return m_x * rhs.m_x + m_y * rhs.m_y + m_z * rhs.m_z;
}

Vec3_f Vec3_f::cross(const Vec3_f& rhs) const {
  return {
    m_y * rhs.m_z - m_z * rhs.m_y,
    m_z * rhs.m_x - m_x * rhs.m_z,
    m_x * rhs.m_y - m_y * rhs.m_x
  };
}

float Vec3_f::get_length() const {
  return sqrt( m_x * m_x + m_y * m_y + m_z * m_z );
}

Vec3_f& Vec3_f::make_unit() {
  *this /= this->get_length();
  return *this;
}

// // arbitrary axis
// Vec3_f Vec3_f::rotate(const Vec3_f& axis, const float& angleInRadians) const {
//   float cosAngle = cos(angleInRadians);
//   return axis * (1 - cosAngle) * this->dot(axis) + *this * cosAngle + this->cross(axis) * sin(angleInRadians);
// }
//
// Vec3_f Vec3_f::rotate(const Vec3_f& axis, const float& cosAngle, const float& sinAngle) const {
//   return axis * (1 - cosAngle) * this->dot(axis) + *this * cosAngle + this->cross(axis) * sinAngle;
// }
//
// // if we know the axis is orthogonal to the vector, we can simplify :
// Vec3_f Vec3_f::rotate_ortho(const Vec3_f& axis, const float& angleInRadians) const {
//   return *this * cos(angleInRadians) + this->cross(axis) * sin(angleInRadians);
// }
//
// Vec3_f Vec3_f::rotate_ortho(const Vec3_f& axis, const float& cosAngle, const float& sinAngle) const {
//   return *this * cosAngle + this->cross(axis) * sinAngle;
// }

Vec3_f& Vec3_f::rotate_by(const Vec3_f& axis, const float& angleInRadians) {
  float cosAngle = cos(angleInRadians);
  *this = axis * (1 - cosAngle) * this->dot(axis) + *this * cosAngle + this->cross(axis) * sin(angleInRadians);
  return *this;
}

Vec3_f& Vec3_f::rotate_by(const Vec3_f& axis, const float& cosAngle, const float& sinAngle) {
  *this = axis * (1 - cosAngle) * this->dot(axis) + *this * cosAngle + this->cross(axis) * sinAngle;
  return *this;
}

Vec3_f& Vec3_f::rotate_ortho_by(const Vec3_f& axis, const float& angleInRadians) {
  *this = *this * cos(angleInRadians) + this->cross(axis) * sin(angleInRadians);
  return *this;
}

Vec3_f& Vec3_f::rotate_ortho_by(const Vec3_f& axis, const float& cosAngle, const float& sinAngle) {
  *this = *this * cosAngle + this->cross(axis) * sinAngle;
  return *this;
}

Vec3_f Vec3_f::change_coordinates_to(const Space3_f& new_space) const {
  Vec3_f delta = *this - new_space.m_position;
  return {
    delta.dot(new_space.m_xAxis),
    delta.dot(new_space.m_yAxis),
    delta.dot(new_space.m_zAxis)
  };
}

Vec2_f Vec3_f::project(const float& focalLength) const {
  return {
    m_x * focalLength / m_z,
    m_y * focalLength / m_z
  };
}

// Space3_f Space3_f::operator+(const Vec3_f& translate) const {
//   return {
//     this->m_position + translate,
//     this->m_xAxis,
//     this->m_yAxis,
//     this->m_zAxis
//   };
// }
// Space3_f Space3_f::operator-(const Vec3_f& translate) const {
//   return {
//     this->m_position - translate,
//     this->m_xAxis,
//     this->m_yAxis,
//     this->m_zAxis
//   };
// }

Space3_f& Space3_f::operator+=(const Vec3_f& translate) {
  m_position += translate;
  return *this;
}
Space3_f& Space3_f::operator-=(const Vec3_f& translate) {
  m_position -= translate;
  return *this;
}

// unswapped x & y axes. maybe this will help
Space3_f& Space3_f::rotate_by(const Vec3_f& axis, const float& angleInRadians) {
  float cosAngle = cos(angleInRadians), sinAngle = sin(angleInRadians);
  m_xAxis.rotate_by(axis, cosAngle, sinAngle);
  m_yAxis.rotate_by(axis, cosAngle, sinAngle);
  m_zAxis = m_xAxis.cross(m_yAxis); // small optimization, but does the same as .rotate_by(axis, cosAngle, sinAngle)
  return *this;
}

Space3_f& Space3_f::rotate_by(const Vec3_f& axis, const float& cosAngle, const float& sinAngle) {
  m_xAxis.rotate_by(axis, cosAngle, sinAngle);
  m_yAxis.rotate_by(axis, cosAngle, sinAngle);
  m_zAxis = m_xAxis.cross(m_yAxis);
  return *this;
}

Space3_f& Space3_f::rotate_around_by(const Vec3_f& center, const Vec3_f& axis, const float& angleInRadians) {
  float cosAngle = cos(angleInRadians), sinAngle = sin(angleInRadians);
  m_position = (m_position - center).rotate_by(axis, cosAngle, sinAngle) + center;
  m_xAxis.rotate_by(axis, cosAngle, sinAngle);
  m_yAxis.rotate_by(axis, cosAngle, sinAngle);
  m_zAxis = m_xAxis.cross(m_yAxis);
  return *this;
}

Space3_f& Space3_f::rotate_around_by(const Vec3_f& center, const Vec3_f& axis, const float& cosAngle, const float& sinAngle) {
  m_position = (m_position - center).rotate_by(axis, cosAngle, sinAngle) + center;
  m_xAxis.rotate_by(axis, cosAngle, sinAngle);
  m_yAxis.rotate_by(axis, cosAngle, sinAngle);
  m_zAxis = m_xAxis.cross(m_yAxis);
  return *this;
}

#endif
