#ifndef MODPERSONAL_UTILS_3D_VECTORS_H
#define MODPERSONAL_UTILS_3D_VECTORS_H

struct Vec2_f;
struct Vec3_f;
struct Space3_f;

struct Vec2_f {
  float m_x, m_y;
};

struct Vec3_f {
  float m_x, m_y, m_z;

  // translations
  Vec3_f operator+(const Vec3_f&) const;
  Vec3_f operator-(const Vec3_f&) const;
  // scaling
  Vec3_f operator*(const float&) const;
  Vec3_f operator/(const float&) const;
  Vec3_f operator-() const;

  // compound assignment
  Vec3_f& operator+=(const Vec3_f&);
  Vec3_f& operator-=(const Vec3_f&);
  Vec3_f& operator*=(const float&);
  Vec3_f& operator/=(const float&);

  float dot(const Vec3_f&) const;
  Vec3_f cross(const Vec3_f&) const;
  float get_length() const;
  Vec3_f& make_unit();

  // whenever possible (mostly when working with arrays), use the
  // cosAngle/sinAngle versions of rotation functions so that
  // as little as possible calls to trigonometric functions are done
  // inline Vec3_f rotate(const Vec3_f&, const float&) const; // relative to origin
  // inline Vec3_f rotate(const Vec3_f&, const float& cosAngle, const float& sinAngle) const;
  // inline Vec3_f rotate_ortho(const Vec3_f&, const float&) const;
  // inline Vec3_f rotate_ortho(const Vec3_f&, const float& cosAngle, const float& sinAngle) const;
  // inline Vec3_f rotate_around(const Vec3_f&, const Vec3_f&, const float&) const; // relative to any center
  // inline Vec3_f rotate_around(const Vec3_f&, const Vec3_f&, const float& cosAngle, const float& sinAngle) const;

  // whenever possible (mostly when working with arrays), use the
  // cosAngle/sinAngle versions of rotation functions so that
  // as little as possible calls to trigonometric functions are done
  // compound assignment
  Vec3_f& rotate_by(const Vec3_f&, const float&);
  Vec3_f& rotate_by(const Vec3_f&, const float& cosAngle, const float& sinAngle);
  Vec3_f& rotate_ortho_by(const Vec3_f&, const float&);
  Vec3_f& rotate_ortho_by(const Vec3_f&, const float& cosAngle, const float& sinAngle);

  Vec3_f change_coordinates_to(const Space3_f&) const;
  Vec2_f project(const float&) const;
};

struct Space3_f {
  Vec3_f m_position, m_xAxis, m_yAxis, m_zAxis;

  // // translations
  // Space3_f operator+(const Vec3_f&) const;
  // Space3_f operator-(const Vec3_f&) const;

  // compound assignment
  Space3_f& operator+=(const Vec3_f&);
  Space3_f& operator-=(const Vec3_f&);
  Space3_f& rotate_by(const Vec3_f&, const float&);
  Space3_f& rotate_by(const Vec3_f&, const float& cosAngle, const float& sinAngle);
  Space3_f& rotate_around_by(const Vec3_f&, const Vec3_f&, const float&);
  Space3_f& rotate_around_by(const Vec3_f&, const Vec3_f&, const float& cosAngle, const float& sinAngle);
};

#endif
