#ifndef MODPERSONAL_UTILS_3D_MESH_3D_H
#define MODPERSONAL_UTILS_3D_MESH_3D_H

#include "vectors.h"
#include <cmath>
#include <kandinsky.h>
#define PI 3.14159265358979f

// struct Edge; // we want it to be separate from triangles so that edges aren't drawn multiple times

struct Triangle {
  unsigned char v0, v1, v2; // will be used as list indices
  KDColor color;
};

enum MeshDefault { cube, quad, };
enum Winding : bool { clockwise = true, counterClockwise = false };

struct Mesh {
  unsigned char m_allocatedVertices, m_allocatedFaces;
  Vec3_f* m_vertices;
  Triangle* m_triangles;
  unsigned char m_usedVertices = 0u, m_usedFaces = 0u;
  Vec3_f m_center = { 0.0f, 0.0f, 0.0f };
  Vec3_f m_rotationAxis = { 0.0f, 1.0f, 0.0f }; // -------
  float m_rotationSpeed = 0.0f;                 // we'll get rid of those later
  bool m_keepRotating = false;                  // -------
  Winding m_winding = counterClockwise;

  Mesh(unsigned char, unsigned char);
  Mesh(MeshDefault);
  Mesh(const Mesh&);
  ~Mesh();
  Mesh& operator=(const Mesh&);

  void appendVertex(Vec3_f);
  void appendFace(Triangle);
  void deleteVertex(unsigned char); // make sure to delete faces referring to it
  void deleteFace(unsigned char);
  void extendVertices(const Vec3_f*, unsigned char);
  void extendFaces(const Triangle*, unsigned char);
  void deleteVertices(unsigned char, unsigned char);
  void deleteFaces(unsigned char, unsigned char);

  Mesh& operator+=(const Vec3_f&);
  Mesh& operator-=(const Vec3_f&);
  Mesh& rotate_by(const Vec3_f&, const float&); // relative to its center
};

#endif
