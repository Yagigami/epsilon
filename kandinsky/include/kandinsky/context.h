#ifndef KANDINSKY_CONTEXT_H
#define KANDINSKY_CONTEXT_H

#include <kandinsky/color.h>
#include <kandinsky/rect.h>
#include <kandinsky/font.h>
#include <kandinsky/image.h>
#include <stdint.h>

class KDContext {
public:
  // getPixels's and fillRectWithPixels's "pixels" argument needs to be
  // a contiguous block of memory. it has the size of rectWidth*rectHeight
  // and stores pixels from left to right, top to bottom. try to keep your
  // rectangle always fully in bounds as that slows down both methods a lot.
  void setOrigin(KDPoint origin);
  void setClippingRect(KDRect clippingRect);

  // Pixel manipulation
  void setPixel(KDPoint p, KDColor c);
  KDColor getPixel(KDPoint p);
  void getPixels(KDRect r, KDColor * pixels);

  // Text
  KDPoint drawString(const char * text, KDPoint p, const KDFont * font = KDFont::LargeFont, KDColor textColor = KDColorBlack, KDColor backgroundColor = KDColorWhite, int maxLength = -1);
  // Check that a string is drawn.
  int checkDrawnString(const char * text, KDPoint p, const KDFont * font = KDFont::LargeFont, KDColor textColor = KDColorBlack, KDColor backgroundColor = KDColorWhite, int maxLength = -1);

  // Line. Not anti-aliased.
  void drawLine(KDPoint p1, KDPoint p2, KDColor c);
  void horizLine(KDPoint p0, KDPoint p1, KDColor c);
  void vertLine(KDPoint p0, KDPoint p1, KDColor c);

  // Triangle
  void fillTriangle(KDPoint p0, KDPoint p1, KDPoint p2, KDColor c, bool drawEdges, KDColor edgeColor);
  // those two need sorted KDPoint arguments, might be possible to optimize,
  // probably with integer-based arithmetic instead of casting doubles
  void fillFlatBottomTriangle(KDPoint top, KDPoint bottomLeft, KDPoint bottomRight, KDColor c);
  void fillFlatTopTriangle(KDPoint bottom, KDPoint topLeft, KDPoint topRight, KDColor c);

  // Triangle
  void fillTriangle(KDPoint p0, KDPoint p1, KDPoint p2, KDColor c);
  // those two need sorted KDPoint arguments, might be possible to optimize,
  // probably with integer-based arithmetic instead of casting doubles
  void fillFlatBottomTriangle(KDPoint top, KDPoint bottomLeft, KDPoint bottomRight, KDColor c);
  void fillFlatTopTriangle(KDPoint bottom, KDPoint topLeft, KDPoint topRight, KDColor c);

  // Sprite
  void updateImage(KDPoint p, KDPoint oldp, KDImage const *const spt, KDColor background);
  void updateAnim(KDPoint p, KDPoint oldp, KDAnimation const *const anim, KDColor background);

  // Rect
  void fillRect(KDRect rect, KDColor color);
  void fillRectWithPixels(KDRect rect, const KDColor * pixels, KDColor * workingBuffer);
  void blendRectWithMask(KDRect rect, KDColor color, const uint8_t * mask, KDColor * workingBuffer);
  void strokeRect(KDRect rect, KDColor color);
protected:
  KDContext(KDPoint origin, KDRect clippingRect);
  virtual void pushRect(KDRect, const KDColor * pixels) = 0;
  virtual void pushRectUniform(KDRect rect, KDColor color) = 0;
  virtual void pullRect(KDRect rect, KDColor * pixels) = 0;
private:
  KDRect absoluteFillRect(KDRect rect);
  KDPoint pushOrPullString(const char * text, KDPoint p, const KDFont * font, KDColor textColor, KDColor backgroundColor, int maxByteLength, bool push, int * result = nullptr);
  KDPoint m_origin;
  KDRect m_clippingRect;
};

#endif
