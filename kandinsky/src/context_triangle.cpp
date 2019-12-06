#include <kandinsky/context.h>

static inline void swap(KDPoint& a, KDPoint& b);

void KDContext::fillTriangle(KDPoint p0, KDPoint p1, KDPoint p2, KDColor c) {
  KDPoint top = p0, middle = p1, bottom = p2;
  // first we need to sort the points by ascending y-coordinate
  if (top.y() > middle.y()) {
    swap(top, middle);
  }
  if (middle.y() > bottom.y()) {
    swap(middle, bottom);
    if (top.y() > middle.y()) {
      swap(top, middle);
    }
  }

  // only draw what is necessary
  if (top.y() == middle.y()) { // flat top case
    if (top.x() > middle.x()) swap(top, middle);
    KDContext::fillFlatTopTriangle(bottom, top, middle, c);
    return;
  } else if (middle.y() == bottom.y()) { // flat bottom case
    if (middle.x() > bottom.x()) swap(middle, bottom);
    KDContext::fillFlatBottomTriangle(top, middle, bottom, c);
    return;
  } // arbitrary case
  double mIntermediate, pIntermediate;
  mIntermediate = ((double) top.x() - bottom.x()) / (top.y() - bottom.y());
  pIntermediate = top.x() - mIntermediate * top.y();
  KDPoint p3 = KDPoint(mIntermediate * middle.y() + pIntermediate, middle.y());
  if (p3.x() > middle.x()) swap(p3, middle);

  KDContext::fillFlatBottomTriangle(top, p3, middle, c);
  KDContext::fillFlatTopTriangle(bottom, p3, middle, c);
}

void KDContext::fillFlatBottomTriangle(KDPoint top, KDPoint bottomLeft, KDPoint bottomRight, KDColor c) {
  KDCoordinate scanLeft, scanRight;
  KDCoordinate xTop = top.x(), yTop = top.y(), xBottomLeft = bottomLeft.x(), yBottomLeft = bottomLeft.y(), xBottomRight = bottomRight.x(), yBottomRight = bottomRight.y();
  double mLeft, mRight, pLeft, pRight;
  mLeft = ((double) xTop - xBottomLeft) / (yTop - yBottomLeft);
  pLeft = xTop - mLeft * yTop;
  mRight = ((double) xTop - xBottomRight) / (yTop - yBottomRight);
  pRight = xTop - mRight * yTop;

  for (KDCoordinate y = yTop; y <= yBottomLeft; y++) {
    scanLeft = mLeft * y + pLeft;
    scanRight = mRight * y + pRight;
    KDContext::fillRect(KDRect(scanLeft, y, scanRight - scanLeft + 1, 1), c);
  }
}

void KDContext::fillFlatTopTriangle(KDPoint bottom, KDPoint topLeft, KDPoint topRight, KDColor c) {
  KDCoordinate xBottom = bottom.x(), yBottom = bottom.y(), xTopLeft = topLeft.x(), yTopLeft = topLeft.y(), xTopRight = topRight.x(), yTopRight = topRight.y();
  KDCoordinate scanLeft, scanRight;
  double mLeft, mRight, pLeft, pRight;
  mLeft = ((double) xBottom - xTopLeft) / (yBottom - yTopLeft);
  pLeft = xBottom - mLeft * yBottom;
  mRight = ((double) xBottom - xTopRight) / (yBottom - yTopRight);
  pRight = xBottom - mRight * yBottom;

  for (KDCoordinate y = yBottom; y >= yTopLeft; y--) {
    scanLeft = mLeft * y + pLeft;
    scanRight = mRight * y + pRight;
    KDContext::fillRect(KDRect(scanLeft, y, scanRight - scanLeft + 1, 1), c);
  }
}

static inline void swap(KDPoint& a, KDPoint& b) {
  KDPoint tmp = a;
  a = b;
  b = tmp;
}
