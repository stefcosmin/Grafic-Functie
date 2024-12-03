#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#define font 8
void init()
{
  setcolor(WHITE);
  char *text = "Introduceti o functie in consola pentru a incepe";
  settextstyle(font, HORIZ_DIR, 4);
  outtextxy(getmaxx() / 2 - textwidth(text) / 2, 50, text);
}

void introduInfSup(float &inf, float &sup, char *t)
{
  short midx = getmaxx() / 2;
  short midy = getmaxy() / 2;
  cleardevice();
  settextstyle(font, HORIZ_DIR, 4);
  outtextxy(midx - textwidth("Functia introdusa:") / 2, 20, "Functia introdusa:");
  outtextxy(midx - textwidth(t) / 2, 60, t);

  outtextxy(midx - textwidth("Introduceti limitele intervalului") / 2, 100, "Introduceti limitele intervalului");
  std::cin >> inf >> sup;
  char buffer[100];
  sprintf(buffer, "[%f,%f]", inf, sup);
  outtextxy(midx - textwidth(buffer) / 2, 160, buffer);
}

void menu(char *t)
{
  short midx = getmaxx() / 2;
  short midy = getmaxy() / 2;
  cleardevice();
  settextstyle(font, HORIZ_DIR, 4);
  outtextxy(midx - textwidth("Functia introdusa:") / 2, 20, "Functia introdusa:");
  outtextxy(midx - textwidth(t) / 2, 60, t);
  setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
  outtextxy(midx - textwidth("Doriti calcularea functiei pe un anumit interval?") / 2, 140, "Doriti calcularea functiei pe un anumit interval?");
  settextstyle(font, HORIZ_DIR, 6);

  bar(midx - textwidth("DA") - 25, midy - 60 - textheight("DA"), midx - 15, midy - 50);
  bar(midx + 15, midy - 60 - textheight("NU"), midx + textwidth("NU") + 25, midy - 50);

  outtextxy(midx - textwidth("DA") - 20, midy - 55 - textheight("DA"), "DA");
  outtextxy(midx + 20, midy - 55 - textheight("NU"), "NU");

  int x = 0, y = 0;
  while (!((x > (midx - textwidth("DA") - 25) && x < (midx - 15) && y > (midy - 60 - textheight("DA")) && y < (midy - 50)) || (x > (midx + 15) && x < (midx + textwidth("NU") + 25) && y > (midy - 60 - textheight("NU")) && y < (midy - 50))))
  {

    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }
  if (x > (midx - textwidth("DA") - 25) && x < (midx - 15) && y > (midy - 60 - textheight("DA")) && y < (midy - 50))
  {
    float inf, sup;

    introduInfSup(inf, sup, t);

    // deseneaza cu limite
  }
  else if (x > (midx + 15) && x < (midx + textwidth("NU") + 25) && y > (midy - 60 - textheight("NU")) && y < (midy - 50))
  {
    // deseneaza
  }
}