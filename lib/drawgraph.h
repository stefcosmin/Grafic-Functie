#pragma once
#include <conio.h>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <cctype>
#include "func.h"

float inf = -5, sup = 5;
float lower = 100001, upper = 100001;
void PanZoom();

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

void drawFun()
{
  cleardevice();
  drawPZ();
  setfillstyle(SOLID_FILL, COLOR(190, 190, 190));
  bar(0, 0, DRP, JOS);
  if (lower == 100001 && upper == 100001)
  {
    desenare_axe(inf, sup);
    desenare_grafic_functie(inf, sup, opt.color, 4);
  }
  else
  {
    desenare_axe(lower, upper);
    desenare_grafic_functie(lower, upper, opt.color, 4);
  }

  PanZoom();
}

void PanZoom()
{
  int x = 0, y = 0;
  int midx = getmaxx() - getmaxx() / 8, midy = getmaxy() / 2;

  float center = (inf + sup) / 2; // var de calcul
  float dif = sup - inf;
  float half_width = dif / 2;

  while (!((x > (midx + 50) && x < (midx + 100) && y > (midy + 200) && y < (midy + 250)) ||   // plus
           ((x > (midx + 50) && x < (midx + 100)) && y > (midy + 275) && y < (midy + 325)) || // minus
           (x > (midx - 90) && x < (midx - 40) && y > (midy) && y < (midy + 50)) ||           // stanga
           (x > (midx + 50) && x < (midx + 100) && y > (midy) && y < (midy + 50))))           // dreapta
  {

    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }

  if (x > (midx + 50) && x < (midx + 100) && y > (midy + 200) && y < (midy + 250)) // minus
  {
    inf = center - (0.5 * half_width);
    sup = center + (0.5 * half_width);
  }
  else if (x > (midx + 50) && x < (midx + 100) && y > (midy + 275) && y < (midy + 325)) // plus
  {

    inf = center - (2 * half_width);
    sup = center + (2 * half_width);
  }
  else if (x > (midx - 90) && x < (midx - 40) && y > (midy) && y < (midy + 50)) // stanga
  {
    inf -= dif / 8;
    sup -= dif / 8;
  }
  else if (x > (midx + 50) && x < (midx + 100) && y > (midy) && y < (midy + 50)) // dreapta
  {
    inf += dif / 8;
    sup += dif / 8;
  }

  drawFun();
}
