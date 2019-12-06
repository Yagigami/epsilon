#include <kandinsky/image.h>
#include <stdint.h>

KDImage::KDImage(const KDColor *const img, KDCoordinate width, KDCoordinate height)
  : m_img(img), m_width(width), m_height(height)
  {
  }

KDImage::KDImage(const KDColor *const img, KDSize size)
  : m_img(img), m_size(size)
  {
  }

KDAnimation::KDAnimation(const KDColor *const anim, KDCoordinate width, KDCoordinate height,
   uint16_t length, uint16_t currentFrame /* = 0 */,
   uint16_t millisecondPerFrame /* = 67 */)
   : m_anim(anim), m_width(width), m_height(height),
   m_length(length), m_millisecondPerFrame(millisecondPerFrame),
   m_currentFrame(currentFrame), m_timeLastUpdated(-1)
   {
   }

KDAnimation::KDAnimation(const KDColor *const anim, KDSize size,
  uint16_t length, uint16_t currentFrame /* = 0 */,
  uint16_t millisecondPerFrame /* = 67 */)
  : m_anim(anim), m_size(size),
  m_length(length), m_millisecondPerFrame(millisecondPerFrame),
  m_currentFrame(currentFrame), m_timeLastUpdated(-1)
  {
  }

void KDAnimation::update(uint64_t timeInMilliseconds) {
  if (timeInMilliseconds - m_timeLastUpdated > m_millisecondPerFrame) {
    nextFrame();
    m_timeLastUpdated = timeInMilliseconds;
  }
}

void KDAnimation::nextFrame() {
  m_currentFrame = (m_currentFrame + 1) % m_length;
}

void KDAnimation::firstFrame() {
  m_currentFrame = 0;
}
