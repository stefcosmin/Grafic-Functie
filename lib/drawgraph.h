#pragma once
#include <conio.h>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <cctype>
#include <windows.h>
#include <fstream>
#include <commdlg.h>
#include "func.h"
#include "settings.h"

float inf = -5, sup = 5;
float lower = -100001, upper = 100001;
short culoare[] = {0, 1, 2, 4, 5, 14};
void PanZoom();

void toLow(char *buffer)
{
  for (int i = 0; i < strlen(buffer); i++)
  {
    if (isalpha(buffer[i]) && isupper(buffer[i]))
      buffer[i] = tolower(buffer[i]);
  }
}

void remove(int index)
{
  int i = index;
  while (strlen(func[i + 1]) != 0)
  {
    strcpy(func[i], func[i + 1]);
    i++;
  }
  strcpy(func[i], "");
}

void showFunc()
{
  int stg = 990, sus = 80, drp = 1260, jos = 420;
  setbkcolor(COLOR(22, 22, 22));
  setcolor(WHITE);
  settextstyle(font, HORIZ_DIR, 1);
  int i = 0;
  while (strlen(func[i]) != 0)
  {
    setfillstyle(SOLID_FILL, culoare[i]);
    bar(stg, sus + 50 * i, stg + 40, sus + 50 * i + 40);
    char buffer[256] = "";
    strcpy(buffer, func[i]);
    outtextxy(stg + 50, sus + 50 * i + textheight(buffer) / 2, buffer);
    readimagefile("img/pz/trash.jpg", drp - 40, sus + 50 * i, drp, sus + 50 * i + 40);
    i++;
  }
  settextstyle(font, HORIZ_DIR, 2);
}

void newFunc()
{
  int count = 0;
  do
  {
    count++;
  } while (strlen(func[count]) != 0);
  setfillstyle(SOLID_FILL, culoare[count]);
  bar(990, 80 + 50 * count, 1030, 80 + 50 * count + 40);
  setfillstyle(SOLID_FILL, COLOR(22, 22, 22));
  setcolor(WHITE);
  char buffer[256] = "";
  while (1) // citire
  {
    delay(10);
    if (kbhit())
    {
      char c = getch();
      if (c == 13)
      {
        strcpy(func[count], buffer);
        break;
      }
      else if (c == 8)
      {
        buffer[strlen(buffer) - 1] = '\0';
      }
      else
        buffer[strlen(buffer)] = c, buffer[strlen(buffer)] = '\0';
      toLow(buffer);
      bar(1040, 80 + 50 * count, 1220, 80 + 50 * count + 40);
      setbkcolor(COLOR(22, 22, 22));
      outtextxy(1040, 80 + 50 * count + textheight("x(^/") / 2, buffer);
    }
  }
  if (functie gresita)
  {
    remove(count);
  }
}

void drawPZ()
{
  short midx = getmaxx() - getmaxx() / 8;
  short midy = getmaxy() / 2;
  setfillstyle(SOLID_FILL, COLOR(22, 22, 22));
  bar(midx - (getmaxx() - midx), 0, getmaxx(), getmaxy());

  readimagefile("img/pz/up.jpg", midx - 65, midy + 130, midx - 15, midy + 180);
  readimagefile("img/pz/left.jpg", midx - 135, midy + 200, midx - 85, midy + 250);
  readimagefile("img/pz/right.jpg", midx + 5, midy + 200, midx + 55, midy + 250);
  readimagefile("img/pz/down.jpg", midx - 65, midy + 270, midx - 15, midy + 320);

  readimagefile("img/pz/plus.jpg", midx + 85, midy + 165, midx + 135, midy + 215);
  readimagefile("img/pz/minus.jpg", midx + 85, midy + 235, midx + 135, midy + 285);

  readimagefile("img/pz/prtsc.jpg", 1220, 10, 1270, 60);
  readimagefile("img/pz/add.jpg", 1040, midy + 85, 1200, midy + 125);
  setfillstyle(SOLID_FILL, LIGHTCYAN);
  // bar(980, 70, 1260, 430);
  setbkcolor(COLOR(22, 22, 22));

  showFunc();
}

void background()
{
  setfillstyle(SOLID_FILL, COLOR(190, 190, 190));
  bar(0, 0, getmaxx() - getmaxx() / 4, getmaxy());
}

void drawFun()
{
  drawPZ();
  background();
  desenare_axe(inf, sup);
  int i = 0;
  while (strlen(func[i]))
  {
    copieFun(func[i]);
    minim_si_maxim(inf, sup);
    GraphBorder(inf, sup);
    desenare_grafic_functie(inf, sup, culoare[i]);
    i++;
  }

  PanZoom();
}

void PanZoom()
{
  int x = 0, y = 0;
  int midx = getmaxx() - getmaxx() / 8, midy = getmaxy() / 2;

  // var de calcul
  float center = (inf + sup) / 2;
  float dif = sup - inf;
  float half_width = dif / 2;

  while (!((x > (midx + 85) && x < (midx + 135) && y > (midy + 165) && y < (midy + 215)) ||   // plus
           ((x > (midx + 85) && x < (midx + 135)) && y > (midy + 235) && y < (midy + 285)) || // minus
           (x > (midx - 135) && x < (midx - 15) && y > (midy + 200) && y < (midy + 250)) ||   // stanga
           (x > (midx + 5) && x < (midx + 55) && y > (midy + 200) && y < (midy + 250)) ||     // dreapta
           (x > (midx - 65) && x < (midx - 15) && y > (midy + 270) && y < (midy + 320)) ||    // jos
           (x > (midx - 65) && x < (midx - 15) && y > (midy + 130) && y < (midy + 180)) ||    // sus
           (x > (1220) && x < (1270) && y > (10) && y < (60)) ||                              // prtsc
           (x > (1090) && x < (1140) && y < (10) && y > (60)) ||                              // load
           (x > (1040) && x < (1200) && y > (midy + 85) && y < (midy + 125)) ||               // add
           (x > (1220) && x < (1260) && y > (80) && y < (120)) ||                             // remove 0
           (x > (1220) && x < (1260) && y > (130) && y < (170)) ||                            // remove 1
           (x > (1220) && x < (1260) && y > (180) && y < (220)) ||                            // remove 2
           (x > (1220) && x < (1260) && y > (230) && y < (270)) ||                            // remove 3
           (x > (1220) && x < (1260) && y > (280) && y < (320)) ||                            // remove 4
           (x > (1220) && x < (1260) && y > (330) && y < (370))))                             // remove 5
  {

    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }
  if (x > (midx + 85) && x < (midx + 135) && y > (midy + 165) && y < (midy + 215)) // plus
  {
    if (((center - (0.5 * half_width)) > lower) && ((center + (0.5 * half_width)) < upper))
      inf = center - (0.5 * half_width), sup = center + (0.5 * half_width);
  }
  else if ((x > (midx + 85) && x < (midx + 135)) && y > (midy + 235) && y < (midy + 285)) // minus
  {
    if (((center - (2 * half_width)) > lower) && ((center + (2 * half_width)) < upper))
      if ((center + (2 * half_width) - (center - (2 * half_width))) < 500)
        inf = center - (2 * half_width), sup = center + (2 * half_width);
  }
  else if (x > (midx - 135) && x < (midx - 15) && y > (midy + 200) && y < (midy + 250)) // stanga
  {
    if ((inf - dif / 8 > lower) && (sup + dif / 8 < upper))
      inf -= dif / 8, sup -= dif / 8;
  }
  else if (x > (midx + 5) && x < (midx + 55) && y > (midy + 200) && y < (midy + 250)) // dreapta
  {
    if ((inf + dif / 8 > lower) && (sup - dif / 8 < upper))
      inf += dif / 8, sup += dif / 8;
  }
  else if (x > (midx - 65) && x < (midx - 15) && y > (midy + 270) && y < (midy + 320)) // jos
  {
    yoffset -= int(getmaxy() / unitate) / 4 * unitate;
  }
  else if (x > (midx - 65) && x < (midx - 15) && y > (midy + 130) && y < (midy + 180)) // sus
  {
    yoffset += int(getmaxy() / unitate) / 4 * unitate;
  }
  else if (x > (1220) && x < (1270) && y > (10) && y < (60)) // prtsc
  {
    writeimagefile(NULL, 0, 0, 960, 720);
    exit(0);
  }
  else if (x > (1040) && x < (1200) && y > (midy + 85) && y < (midy + 125)) // add
  {
    newFunc();
  }
  else if (x > (1220) && x < (1260) && y > (80) && y < (120)) // remove 0
  {

    remove(0);
  }
  else if (x > (1220) && x < (1260) && y > (130) && y < (170)) // remove 1
  {

    remove(1);
  }
  else if (x > (1220) && x < (1260) && y > (180) && y < (220)) // remove 2
  {

    remove(2);
  }
  else if (x > (1220) && x < (1260) && y > (230) && y < (270)) // remove 3
  {

    remove(3);
  }
  else if (x > (1220) && x < (1260) && y > (280) && y < (320)) // remove 4
  {

    remove(4);
  }
  else if (x > (1220) && x < (1260) && y > (330) && y < (370)) // remove 5
  {

    remove(5);
  }

  drawFun();
}

void graphMode()
{
  cleardevice();
  if (opt.lang == 0)
    outtextxy(getmaxx() / 2 - textwidth("Introduceti prima functie") / 2, 20, "Introduceti prima functie:");
  else
    outtextxy(getmaxx() / 2 - textwidth("Enter the first function") / 2, 20, "Enter the first function:");
  char buffer[256] = "";
  while (1) // citire
  {
    delay(10);
    if (kbhit())
    {
      char c = getch();
      if (c == 13)
      {
        break;
      }
      else if (c == 8)
      {
        buffer[strlen(buffer) - 1] = '\0';
      }
      else
        buffer[strlen(buffer)] = c, buffer[strlen(buffer)] = '\0';
      toLow(buffer);
      setfillstyle(SOLID_FILL, 0);
      bar(0, 70, 1280, 130);
      outtextxy(getmaxx() / 2 - textwidth(buffer) / 2, 80, buffer);
      setbkcolor(0);
    }
  }
  drawFun();
}