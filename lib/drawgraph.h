#pragma once
#include <conio.h>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <cctype>

void drawPZ()
{
  short midx = getmaxx() - getmaxx() / 8;
  short midy = getmaxy() / 2;
  setfillstyle(SOLID_FILL, COLOR(22, 22, 22));
  bar(midx - (getmaxx() - midx), 0, getmaxx(), getmaxy());
  readimagefile("img/pz/right.jpg", midx + 50, midy, midx + 100, midy + 50);
  readimagefile("img/pz/down.jpg", midx - 20, midy + 70, midx + 30, midy + 120);
  readimagefile("img/pz/left.jpg", midx - 90, midy, midx - 40, midy + 50);
  readimagefile("img/pz/up.jpg", midx - 20, midy - 70, midx + 30, midy - 20);

  readimagefile("img/pz/plus.jpg", midx + 50, midy + 200, midx + 100, midy + 250);
  readimagefile("img/pz/minus.jpg", midx + 50, midy + 275, midx + 100, midy + 325);
  setfillstyle(SOLID_FILL, 0);
}