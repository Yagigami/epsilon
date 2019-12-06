#ifndef MODPERSONAL_UTILS_3D_CAMERA_H
#define MODPERSONAL_UTILS_3D_CAMERA_H

#include "vectors.h"

enum CameraDirection { left, right, up, down, forwards, backwards };

struct Camera {
  Space3_f m_space;
  float m_fieldOfView, m_focalLength;
  // all speeds are in unit per second
  float m_moveSpeed, m_rotationSpeed, m_zoomSpeed;

  Camera(Space3_f, float, float, float, float);

  Camera& operator+=(const Vec3_f&);
  Camera& operator-=(const Vec3_f&);
  Camera& rotate_by(const Vec3_f&, const float&); // relative to its center
  Camera& rotate_by(CameraDirection, const float&);
  Camera& rotate_around_by(const Vec3_f&, const Vec3_f&, const float&); // relative to any center
  Camera& rotate_around_by(const Vec3_f&, CameraDirection, const float&);
  Camera& zoom_by(const float&);
  Camera& move_to(CameraDirection, const float&);
};

#endif
