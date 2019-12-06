extern "C"
{
    #include "modpersonal.h"
}
#include <kandinsky.h>
#include "port.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ion.h>

#include "utils_3D/vectors.h"
#include "utils_3D/Mesh_3D.h"
#include "utils_3D/camera.h"

#include "utils_2D/image_data_example.h"

#define PI 3.14159265358979f
#define MIN_ANIMATION_SPEED (1500 / 10)
#define MAX_ANIMATION_SPEED (400  / 10)
// biggest knwon allocation possible : 32768 bytes

#define RAND_RANGE(type, a, b) \
  ((type) (yasmarang() / (float) 4294967295U * ((b) - (a)) + (a))) // UINT_MAX didn't compile so 4294967295U was the only option

// copied from /python/src/extmod/modurandom.c
// Yasmarang random number generator
// by Ilya Levin
// http://www.literatecode.com/yasmarang
// Public Domain

STATIC uint32_t yasmarang_pad = 0xeda4baba, yasmarang_n = 69, yasmarang_d = 233;
STATIC uint8_t yasmarang_dat = 0;

STATIC uint32_t yasmarang(void)
{
   yasmarang_pad += yasmarang_dat + yasmarang_d * yasmarang_n;
   yasmarang_pad = (yasmarang_pad<<3) + (yasmarang_pad>>29);
   yasmarang_n = yasmarang_pad | 2;
   yasmarang_d ^= (yasmarang_pad<<31) + (yasmarang_pad>>1);
   yasmarang_dat ^= (char) yasmarang_pad ^ (yasmarang_d>>8) ^ 1;

   return (yasmarang_pad^(yasmarang_d<<5)^(yasmarang_pad>>18)^(yasmarang_dat<<1));
}  /* yasmarang */

// not from yasmarang but related to
STATIC void seed(uint64_t s) {
  yasmarang_pad = *(1 + (uint32_t *)&s); // truncating s and ignoring the big, pseudo-constant part of s, mostly a "time" value
}

// End of Yasmarang

static void clearScreen() {
  KDIonContext::sharedContext()->fillRect(
  { 0, 0, Ion::Display::Width, Ion::Display::Height }, KDColor::RGB888(255, 255, 255)
  );
}

mp_obj_t modpersonal_hello_world()
{
  // init
  MicroPython::ExecutionEnvironment *ee = MicroPython::ExecutionEnvironment::currentExecutionEnvironment();
  KDIonContext* ctx = KDIonContext::sharedContext();
  KDCoordinate speed = 2;
  KDRect r0{ 0, 0, Sprites::img_sample_width, Sprites::img_sample_height }, r1{ 100, 0, Sprites::anim_sample_width, Sprites::anim_sample_height };
  KDPoint left = { -speed, 0 }, up = { 0, -speed }, right = { speed, 0 }, down = { 0, speed };
  uint16_t animFrame = 0, millisecondsPerFrame = 400;
  uint64_t timeLastUpdated = -1;
  Ion::Keyboard::State keys;
  ee->displaySandbox();

  // main loop
  while (!(keys = Ion::Keyboard::scan()).keyDown(Ion::Keyboard::Key::OnOff)) {
    // inputs
    if      (keys.keyDown(Ion::Keyboard::Key::Left )) r0 = r0.translatedBy(left );
    else if (keys.keyDown(Ion::Keyboard::Key::Right)) r0 = r0.translatedBy(right);
    if      (keys.keyDown(Ion::Keyboard::Key::Up   )) r0 = r0.translatedBy(up   );
    else if (keys.keyDown(Ion::Keyboard::Key::Down )) r0 = r0.translatedBy(down );

    if      (keys.keyDown(Ion::Keyboard::Key::Four )) r1 = r1.translatedBy(left );
    else if (keys.keyDown(Ion::Keyboard::Key::Six  )) r1 = r1.translatedBy(right);
    if      (keys.keyDown(Ion::Keyboard::Key::Eight)) r1 = r1.translatedBy(up   );
    else if (keys.keyDown(Ion::Keyboard::Key::Two  )) r1 = r1.translatedBy(down );

    // display
    Ion::Display::waitForVBlank();
    clearScreen();
    // not using "kandinsky/image.h", "src/context_image.cpp", "src/image.cpp" yet
    ctx->fillRectWithPixels(r0, Sprites::img_sample, NULL);
    ctx->fillRectWithPixels(r1, Sprites::anim_sample[animFrame], NULL);
    // update animation if necessary
    if (Ion::Timing::millis() - timeLastUpdated > millisecondsPerFrame) {
      animFrame = (animFrame + 1) % Sprites::anim_sample_length;
      timeLastUpdated = Ion::Timing::millis();
    }
  }

  return mp_const_none;
}

static inline void toggleKeyCheck(Ion::Keyboard::Key key, bool& flag, Ion::Keyboard::State const& keys, Ion::Keyboard::State& toggles) {
  if (keys.keyDown(key)) {
    if (toggles.keyDown(key)) {
      flag ^= 1;
      toggles.clearKey(key);
    }
  } else toggles.setKey(key);
}

KDPoint inline normalizedToScreen(const Vec2_f& normalized) {
  return KDPoint((KDCoordinate) ((0.5f + normalized.m_x) * Ion::Display::Width),
   (KDCoordinate) ((0.5f * Ion::Display::Height - normalized.m_y * Ion::Display::Width))
 );
}

mp_obj_t modpersonal_mesh()
{
  // init
  Camera camera(
    {
      { 0.0f, 1.0f, -4.0f },
      { 1.0f, 0.0f, 0.0f },
      { 0.0f, 1.0f, 0.0f },
      { 0.0f, 0.0f, 1.0f }
    },
    PI * 2.0f / 3.0f, 3.0f, 1.5f, 1.0f
  );
  Mesh mesh(cube);
  mesh.m_keepRotating = true;
  mesh.m_rotationSpeed = 2.0f;
  Vec3_f vertex0, vertex1, vertex2;
  float normalFacingCam, delta_time;
  bool drawEdges = true;
  MicroPython::ExecutionEnvironment* ee = MicroPython::ExecutionEnvironment::currentExecutionEnvironment();
  Ion::Keyboard::State keys, toggles = Ion::Keyboard::State(0);
  KDIonContext* ctx = KDIonContext::sharedContext();
  if (mesh.m_keepRotating) toggles.setKey(Ion::Keyboard::Key::Dot);
  volatile uint64_t time = Ion::Timing::millis();
  ee->displaySandbox();

  // main loop
  while (!(keys = Ion::Keyboard::scan()).keyDown(Ion::Keyboard::Key::OnOff)) {
    delta_time = (Ion::Timing::millis() - time) / 1000.0f;
    time = Ion::Timing::millis();

    // inputs
    toggleKeyCheck(Ion::Keyboard::Key::Zero, mesh.m_keepRotating, keys, toggles);
    toggleKeyCheck(Ion::Keyboard::Key::Dot, drawEdges, keys, toggles);
    if      (keys.keyDown(Ion::Keyboard::Key::Four )) camera.move_to(left , delta_time);
    else if (keys.keyDown(Ion::Keyboard::Key::Six  )) camera.move_to(right, delta_time);
    if      (keys.keyDown(Ion::Keyboard::Key::Eight)) camera.move_to(up   , delta_time);
    else if (keys.keyDown(Ion::Keyboard::Key::Two  )) camera.move_to(down , delta_time);
    if      (keys.keyDown(Ion::Keyboard::Key::Nine )) camera.zoom_by( delta_time);
    else if (keys.keyDown(Ion::Keyboard::Key::Seven)) camera.zoom_by(-delta_time);
    if      (keys.keyDown(Ion::Keyboard::Key::Left )) camera.rotate_around_by(mesh.m_center, left , delta_time);
    else if (keys.keyDown(Ion::Keyboard::Key::Right)) camera.rotate_around_by(mesh.m_center, right, delta_time);
    if      (keys.keyDown(Ion::Keyboard::Key::Up   )) camera.rotate_around_by(mesh.m_center, up   , delta_time);
    else if (keys.keyDown(Ion::Keyboard::Key::Down )) camera.rotate_around_by(mesh.m_center, down , delta_time);

    if (mesh.m_keepRotating) {
      mesh.rotate_by(mesh.m_rotationAxis, mesh.m_rotationSpeed * delta_time);
    }

    Ion::Display::waitForVBlank();
    clearScreen();
    for (unsigned char i = 0u; i < mesh.m_usedFaces; i++) {
      vertex0 = (mesh.m_vertices[mesh.m_triangles[i].v0] + mesh.m_center).change_coordinates_to(camera.m_space);
      vertex1 = (mesh.m_vertices[mesh.m_triangles[i].v1] + mesh.m_center).change_coordinates_to(camera.m_space);
      vertex2 = (mesh.m_vertices[mesh.m_triangles[i].v2] + mesh.m_center).change_coordinates_to(camera.m_space);

      Vec3_f faceNormal = (vertex1 - vertex0).cross(vertex2 - vertex1);
      normalFacingCam = faceNormal.dot(vertex0);
      if (mesh.m_winding == clockwise) normalFacingCam *= -1.0f;
      if (normalFacingCam < 0.0f) { // cull backfaces
        if (true) { // we'll need clipping later on (preferrably in 3D space)
          Vec2_f projected0 = vertex0.project(camera.m_focalLength);
          Vec2_f projected1 = vertex1.project(camera.m_focalLength);
          Vec2_f projected2 = vertex2.project(camera.m_focalLength);

          KDPoint screen0 = normalizedToScreen(projected0);
          KDPoint screen1 = normalizedToScreen(projected1);
          KDPoint screen2 = normalizedToScreen(projected2);

          ctx->fillTriangle(screen0, screen1, screen2, mesh.m_triangles[i].color);
          if (drawEdges) {
            ctx->drawLine(screen0, screen1, KDColor::RGB888(0, 0, 0));
            ctx->drawLine(screen1, screen2, KDColor::RGB888(0, 0, 0));
            ctx->drawLine(screen2, screen0, KDColor::RGB888(0, 0, 0));
          }
        }
      }
    }
  }

  ctx->drawString("Done !", KDPoint(0, 0), KDFont::LargeFont, KDColorBlue, KDColorWhite);
  return mp_const_none;
}
