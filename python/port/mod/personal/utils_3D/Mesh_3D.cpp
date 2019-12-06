
// #ifndef MODPERSONAL_UTILS_3D_MESH_3D_CPP
// #define MODPERSONAL_UTILS_3D_MESH_3D_CPP

#include "Mesh_3D.h"
#include "vectors.h"
#include <cmath>
#include <kandinsky.h>
#include <string.h>
#include <stdlib.h>
#define REALLOC_BUFFER_SIZE 4

static const Vec3_f s_cubeVertices[] = {
      { -1.0f, -1.0f, -1.0f }, { 1.0f, -1.0f, -1.0f }, { 1.0f, -1.0f, 1.0f }, { -1.0f, -1.0f, 1.0f },
      { -1.0f,  1.0f, -1.0f }, { 1.0f,  1.0f, -1.0f }, { 1.0f,  1.0f, 1.0f }, { -1.0f,  1.0f, 1.0f }
};
static const Triangle s_cubeTriangles[] = {
    { 0, 1, 5, KDColor::RGB888(192,   0,   0) }, { 0, 5, 4, KDColor::RGB888(160,   0,   0) },
    { 1, 2, 6, KDColor::RGB888(192, 192,   0) }, { 1, 6, 5, KDColor::RGB888(160, 160,   0) },
    { 2, 3, 7, KDColor::RGB888(  0, 192,   0) }, { 2, 7, 6, KDColor::RGB888(  0, 160,   0) },
    { 3, 0, 4, KDColor::RGB888(  0, 192, 192) }, { 3, 4, 7, KDColor::RGB888(  0, 160, 160) },
    { 4, 5, 6, KDColor::RGB888(  0,   0, 192) }, { 4, 6, 7, KDColor::RGB888(  0,   0, 160) },
    { 1, 0, 3, KDColor::RGB888(192,   0, 192) }, { 1, 3, 2, KDColor::RGB888(160,   0, 160) }
};
static const Winding s_cubeWinding = clockwise;

static const Vec3_f s_quadVertices[] = {
    { -1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 1.0f }
};
static const Triangle s_quadTriangles[] = {
    { 0, 1, 2, KDColor::RGB888(192, 192, 192) }, { 0, 2, 3, KDColor::RGB888(160, 160, 160) }
};
static const Winding s_quadWinding = clockwise;

Mesh::Mesh(MeshDefault name) {
  switch (name) {
    case cube:
      m_allocatedVertices = sizeof s_cubeVertices / sizeof s_cubeVertices[0];
      m_allocatedFaces = sizeof s_cubeTriangles / sizeof s_cubeTriangles[0];
      m_vertices = (Vec3_f*) malloc(sizeof(Vec3_f) * m_allocatedVertices);
      m_triangles = (Triangle*) malloc(sizeof(Triangle) * m_allocatedFaces);
      this->extendVertices(s_cubeVertices, m_allocatedVertices);
      this->extendFaces(s_cubeTriangles, m_allocatedFaces);
      m_winding = s_cubeWinding;
      break;
    case quad:
      m_allocatedVertices = sizeof s_quadVertices / sizeof s_quadVertices[0];
      m_allocatedFaces = sizeof s_quadTriangles / sizeof s_quadTriangles[0];
      m_vertices = (Vec3_f*) malloc(sizeof(Vec3_f) * m_allocatedVertices);
      m_triangles = (Triangle*) malloc(sizeof(Triangle) * m_allocatedFaces);
      this->extendVertices(s_quadVertices, m_allocatedVertices);
      this->extendFaces(s_quadTriangles, m_allocatedFaces);
      m_winding = s_quadWinding;
      break;
    default:
      m_allocatedVertices = 0u;
      m_allocatedFaces = 0u;
      m_vertices = nullptr;
      m_triangles = nullptr;
  }
}

Mesh::Mesh(unsigned char allocatedVertices, unsigned char allocatedFaces)
  : m_allocatedVertices(allocatedVertices), m_allocatedFaces(allocatedFaces)
{
  m_vertices = (Vec3_f*) malloc(sizeof(Vec3_f) * allocatedVertices);
  m_triangles = (Triangle*) malloc(sizeof(Triangle) * allocatedFaces);
}

Mesh::Mesh(const Mesh& rhs)
  : m_allocatedVertices(rhs.m_allocatedVertices), m_allocatedFaces(rhs.m_allocatedFaces),
    m_usedVertices(rhs.m_usedVertices), m_usedFaces(rhs.m_usedFaces),
    m_center(rhs.m_center), m_rotationAxis(rhs.m_rotationAxis),
    m_rotationSpeed(rhs.m_rotationSpeed), m_keepRotating(rhs.m_keepRotating),
    m_winding(rhs.m_winding)
{
  m_vertices = (Vec3_f*) malloc(sizeof(Vec3_f) * m_allocatedVertices);
  m_triangles = (Triangle*) malloc(sizeof(Triangle) * m_allocatedFaces);
  if (m_vertices) memcpy(m_vertices, rhs.m_vertices, sizeof(Vec3_f) * m_allocatedVertices);
  if (m_triangles) memcpy(m_triangles, rhs.m_triangles, sizeof(Triangle) * m_allocatedFaces);
}

Mesh::~Mesh() {
  free(m_vertices);
  free(m_triangles);
}

Mesh& Mesh::operator=(const Mesh& rhs) {
  m_allocatedVertices = rhs.m_allocatedVertices;
  m_allocatedFaces = rhs.m_allocatedFaces;
  free(m_vertices);
  free(m_triangles);
  m_vertices = (Vec3_f*) malloc(sizeof(Vec3_f) * m_allocatedVertices);
  m_triangles = (Triangle*) malloc(sizeof(Triangle) * m_allocatedFaces);
  if (m_vertices) memcpy(m_vertices, rhs.m_vertices, sizeof(Vec3_f) * m_allocatedVertices);
  if (m_triangles) memcpy(m_triangles, rhs.m_triangles, sizeof(Triangle) * m_allocatedFaces);
  m_usedVertices = rhs.m_usedVertices;
  m_usedFaces = rhs.m_usedFaces;
  m_winding = rhs.m_winding;
  return *this;
}

void Mesh::appendVertex(Vec3_f item) {
  if (m_vertices) {
    if (m_usedVertices < m_allocatedVertices) {
      m_vertices[m_usedVertices++] = item;
      return;
    }
    Vec3_f* tmp = (Vec3_f*) realloc(m_vertices, sizeof(Vec3_f) * (m_allocatedVertices + REALLOC_BUFFER_SIZE));
    if (tmp) {
      m_allocatedVertices += REALLOC_BUFFER_SIZE;
      m_vertices = tmp;
      m_vertices[m_usedVertices++] = item;
    }
  }
}

void Mesh::appendFace(Triangle triangleItem) {
  if (m_triangles) {
    if (m_usedFaces < m_allocatedFaces) {
      m_triangles[m_usedFaces++] = triangleItem;
      return;
    }
    Triangle* tmp = (Triangle*) realloc(m_triangles, sizeof(Triangle) * (m_allocatedFaces + REALLOC_BUFFER_SIZE));
    if (tmp) {
      m_allocatedFaces += REALLOC_BUFFER_SIZE;
      m_triangles = tmp;
      m_triangles[m_usedFaces++] = triangleItem;
    }
  }
}

void Mesh::deleteVertex(unsigned char index) {
  if (index < m_usedVertices) {
    memcpy(m_vertices + index, m_vertices + index + 1, sizeof(Vec3_f) * (--m_usedVertices - index));
  }
}

void Mesh::deleteFace(unsigned char index) {
  if (index < m_usedFaces) {
    memcpy(m_triangles + index, m_triangles + index + 1, sizeof(Triangle) * (--m_usedFaces - index));
  }
}

void Mesh::extendVertices(const Vec3_f* source, unsigned char size) {
  if (m_vertices) {
    if (m_usedVertices + size <= m_allocatedVertices) {
      memcpy(m_vertices + m_usedVertices, source, sizeof(Vec3_f) * size);
      m_usedVertices += size;
    } else {
      unsigned char allocations = (size - m_allocatedVertices + m_usedVertices + REALLOC_BUFFER_SIZE - 1) / REALLOC_BUFFER_SIZE;
      Vec3_f* tmp = (Vec3_f*) realloc(m_vertices, sizeof(Vec3_f) * (m_allocatedVertices + allocations));
      if (tmp) {
        m_allocatedVertices += allocations * REALLOC_BUFFER_SIZE;
        m_vertices = tmp;
        memcpy(m_vertices + m_usedVertices, source, sizeof(Vec3_f) * size);
        m_usedVertices += size;
      }
    }
  }
}

void Mesh::extendFaces(const Triangle* sourceTriangles, unsigned char size) {
  if (m_triangles) {
    if (m_usedFaces + size <= m_allocatedFaces) {
      memcpy(m_triangles + m_usedFaces, sourceTriangles, sizeof(Triangle) * size);
      m_usedFaces += size;
    } else {
      unsigned char allocations = (size - m_allocatedFaces + m_usedFaces + REALLOC_BUFFER_SIZE - 1) / REALLOC_BUFFER_SIZE;
      Triangle* tmp = (Triangle*) realloc(m_triangles, sizeof(Triangle) * (m_allocatedFaces + allocations));
      if (tmp) {
        m_allocatedFaces += allocations * REALLOC_BUFFER_SIZE;
        m_triangles = tmp;
        memcpy(m_triangles + m_usedFaces, sourceTriangles, sizeof(Triangle) * size);
        m_usedFaces += size;
      }
    }
  }
}

void Mesh::deleteVertices(unsigned char index, unsigned char size) {
  if (m_vertices) {
    if (index < m_usedVertices && index + size < m_usedVertices) {
      if (index + 2 * size <= m_allocatedVertices) {
        memcpy(m_vertices + index, m_vertices + index + size, sizeof(Vec3_f) * size);
      } else {
        unsigned char itemsToMove = m_usedVertices - (index + size);
        memcpy(m_vertices + index, m_vertices + index + size, sizeof(Vec3_f) * itemsToMove);
      }
      m_usedVertices -= size;
    }
  }
}

void Mesh::deleteFaces(unsigned char index, unsigned char size) {
  if (m_triangles) {
    if (index < m_usedFaces && index + size < m_usedFaces) {
      if (index + 2 * size <= m_allocatedFaces) {
        memcpy(m_triangles + index, m_triangles + index + size, sizeof(Triangle) * size);
      } else {
        unsigned char itemsToMove = m_usedFaces - (index + size);
        memcpy(m_triangles + index, m_triangles + index + size, sizeof(Triangle) * itemsToMove);
      }
    }
  }
}

Mesh& Mesh::operator+=(const Vec3_f& rhs) {
  m_center += rhs;
  return *this;
}

Mesh& Mesh::operator-=(const Vec3_f& rhs) {
  m_center -= rhs;
  return *this;
}

Mesh& Mesh::rotate_by(const Vec3_f& axis, const float& angleInRadians) {
  float cosAngle = cos(angleInRadians), sinAngle(angleInRadians);
  for (unsigned char i = 0u; i < m_usedVertices; i++) {
    m_vertices[i].rotate_by(axis, cosAngle, sinAngle);
  }
  return *this;
}

// #endif
