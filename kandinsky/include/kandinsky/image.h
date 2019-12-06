#ifndef KANDINSKY_SPRITE_H
#define KANDINSKY_SPRITE_H

#include <stdint.h>
#include <kandinsky/color.h>
#include <kandinsky/coordinate.h>
#include <kandinsky/size.h>

struct KDImage {
  const KDColor *const m_img;
  const union {
    struct { KDCoordinate m_width, m_height; };
    KDSize m_size;
  };

  KDImage(const KDColor *const img, KDCoordinate width, KDCoordinate height);
  KDImage(const KDColor *const img, KDSize size);
};

struct KDAnimation {
  const KDColor *const m_anim; // it is more practical to shift this pointer than to index it
  const union {
    struct { KDCoordinate m_width, m_height; };
    KDSize m_size;
  };
  uint16_t m_length, m_millisecondPerFrame, m_currentFrame;
  uint64_t m_timeLastUpdated;

  KDAnimation(const KDColor *const anim, KDCoordinate width, KDCoordinate height,
     uint16_t length, uint16_t millisecondPerFrame = 400 / 5, 
     uint16_t currentFrame = 0);
  KDAnimation(const KDColor *const anim, KDSize size,
     uint16_t length, uint16_t millisecondPerFrame = 400 / 5,
     uint16_t currentFrame = 0);

  void update(uint64_t timeInMilliseconds);
  void nextFrame();
  void firstFrame();
};

#endif
