#ifndef MODPERSONAL_UTILS_2D_SPRITES_DATA_H
#define MODPERSONAL_UTILS_2D_SPRITES_DATA_H

#include <kandinsky.h>

namespace Sprites {

constexpr KDColor test0[8 * 8] = {
  KDColorBlue , KDColorBlue , KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorBlue , KDColorBlue ,
  KDColorBlue , KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorBlue ,
  KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite,
  KDColorWhite, KDColorRed  , KDColorRed  , KDColorRed  , KDColorRed  , KDColorRed  , KDColorRed  , KDColorWhite,
  KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite,
  KDColorWhite, KDColorRed  , KDColorWhite, KDColorRed  , KDColorWhite, KDColorRed  , KDColorWhite, KDColorWhite,
  KDColorBlue , KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorBlue ,
  KDColorBlue , KDColorBlue , KDColorWhite, KDColorWhite, KDColorWhite, KDColorWhite, KDColorBlue , KDColorBlue ,
};
constexpr KDCoordinate test0_width = 8, test0_height = 8;

constexpr KDColor test1[16 * 12] = {
  KDColorGreen , KDColorWhite , KDColorGreen , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorGreen , KDColorYellow, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorYellow, KDColorWhite ,
  KDColorWhite , KDColorGreen , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorGreen , KDColorYellow, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorYellow, KDColorWhite , KDColorYellow,
  KDColorGreen , KDColorWhite , KDColorGreen , KDColorWhite , KDColorGreen , KDColorWhite , KDColorWhite , KDColorGreen , KDColorYellow, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorYellow, KDColorWhite ,
  KDColorWhite , KDColorWhite , KDColorWhite , KDColorGreen , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite ,
  KDColorWhite , KDColorWhite , KDColorGreen , KDColorWhite , KDColorWhite , KDColorWhite , KDColorGreen , KDColorGreen , KDColorYellow, KDColorYellow, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite ,
  KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite ,
  KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite ,
  KDColorWhite , KDColorWhite , KDColorBlue  , KDColorWhite , KDColorWhite , KDColorWhite , KDColorBlue  , KDColorBlue  , KDColorOrange, KDColorOrange, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite ,
  KDColorWhite , KDColorWhite , KDColorWhite , KDColorBlue  , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorOrange, KDColorWhite , KDColorWhite ,
  KDColorWhite , KDColorWhite , KDColorBlue  , KDColorWhite , KDColorBlue  , KDColorWhite , KDColorWhite , KDColorBlue  , KDColorOrange, KDColorWhite , KDColorWhite , KDColorWhite , KDColorOrange, KDColorWhite , KDColorWhite , KDColorOrange,
  KDColorBlue  , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorBlue  , KDColorOrange, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorOrange, KDColorWhite ,
  KDColorWhite , KDColorBlue  , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorBlue  , KDColorOrange, KDColorWhite , KDColorWhite , KDColorWhite , KDColorWhite , KDColorOrange, KDColorWhite , KDColorOrange,
};
constexpr KDCoordinate test1_width = 16, test1_height = 12;

constexpr KDColor anim0[5][4 * 6] = {
  {
    KDColorGreen , KDColorWhite , KDColorWhite , KDColorWhite ,
    KDColorGreen , KDColorWhite , KDColorWhite , KDColorYellow,
    KDColorGreen , KDColorWhite , KDColorWhite , KDColorYellow,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorWhite , KDColorBlue  , KDColorOrange, KDColorWhite ,
  },
  {
    KDColorWhite , KDColorGreen , KDColorWhite , KDColorWhite ,
    KDColorWhite , KDColorWhite , KDColorYellow, KDColorWhite ,
    KDColorWhite , KDColorWhite , KDColorWhite , KDColorYellow,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorWhite , KDColorBlue  , KDColorOrange, KDColorOrange,
  },
  {
    KDColorWhite , KDColorWhite , KDColorYellow, KDColorYellow,
    KDColorWhite , KDColorGreen , KDColorWhite , KDColorYellow,
    KDColorGreen , KDColorWhite , KDColorWhite , KDColorYellow,
    KDColorWhite , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorWhite , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorWhite , KDColorBlue  , KDColorOrange, KDColorWhite ,
  },
  {
    KDColorWhite , KDColorGreen , KDColorYellow, KDColorWhite ,
    KDColorGreen , KDColorWhite , KDColorWhite , KDColorYellow,
    KDColorGreen , KDColorWhite , KDColorWhite , KDColorYellow,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorWhite , KDColorBlue  , KDColorWhite , KDColorWhite ,
  },
  {
    KDColorWhite , KDColorWhite , KDColorWhite , KDColorYellow,
    KDColorWhite , KDColorGreen , KDColorYellow, KDColorWhite ,
    KDColorGreen , KDColorWhite , KDColorWhite , KDColorWhite ,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorWhite ,
    KDColorBlue  , KDColorWhite , KDColorWhite , KDColorOrange,
    KDColorBlue  , KDColorBlue  , KDColorOrange, KDColorOrange,
  },
};
constexpr KDCoordinate anim0_width = 4, anim0_height = 6;
constexpr uint16_t anim0_length = 5;

};

#endif
