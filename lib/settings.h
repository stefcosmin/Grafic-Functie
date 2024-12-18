#pragma once
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <fstream>
#define font 8
std::ifstream fin;
std::ofstream fout;

// 0 negru
// 1 albastru
// 2 verde
// 4 rosu
// 5 magenta
// 14 galben

struct settings
{
  bool lang = 0; // 0-Romana, 1-Engleza
  int color1 = 0, color2 = 0;
} opt;

void select(short colorLeft, short colorTop);

void save()
{
  fout.open("data/settings.dat", std::fstream::binary);
  fout.write((char *)&opt, sizeof(settings));
  fout.close();
}

void restore()
{
  fin.open("data/settings.dat", std::fstream::binary);
  fin.read((char *)&opt, sizeof(settings));
  fin.close();
}

void makeBuffer(char *buffer)
{
  switch (opt.lang)
  {
  case 0:
    strcpy(buffer, "Culoarea graficului principal: ");
    switch (opt.color1)
    {
    case 0:
      strcat(buffer, "negru");
      break;
    case 1:
      strcat(buffer, "albastru");
      break;
    case 2:
      strcat(buffer, "verde");
      break;
    case 4:
      strcat(buffer, "rosu");
      break;
    case 5:
      strcat(buffer, "magenta");
      break;
    case 14:
      strcat(buffer, "galben");
      break;
    }
    break;

  case 1:
    strcpy(buffer, "Primary graph's color: ");
    switch (opt.color1)
    {
    case 0:
      strcat(buffer, "black");
      break;
    case 1:
      strcat(buffer, "blue");
      break;
    case 2:
      strcat(buffer, "green");
      break;
    case 4:
      strcat(buffer, "red");
      break;
    case 5:
      strcat(buffer, "magenta");
      break;
    case 14:
      strcat(buffer, "yellow");
      break;
    }
    break;
  }
}

void makesecBuffer(char *buffer)
{
  switch (opt.lang)
  {
  case 0:
    strcpy(buffer, "Culoarea graficului secundar: ");
    switch (opt.color2)
    {
    case 0:
      strcat(buffer, "negru");
      break;
    case 1:
      strcat(buffer, "albastru");
      break;
    case 2:
      strcat(buffer, "verde");
      break;
    case 4:
      strcat(buffer, "rosu");
      break;
    case 5:
      strcat(buffer, "magenta");
      break;
    case 14:
      strcat(buffer, "galben");
      break;
    }
    break;

  case 1:
    strcpy(buffer, "Secondary graph's color: ");
    switch (opt.color2)
    {
    case 0:
      strcat(buffer, "black");
      break;
    case 1:
      strcat(buffer, "blue");
      break;
    case 2:
      strcat(buffer, "green");
      break;
    case 4:
      strcat(buffer, "red");
      break;
    case 5:
      strcat(buffer, "magenta");
      break;
    case 14:
      strcat(buffer, "yellow");
      break;
    }
    break;
  }
}

void drawSettings()
{
  restore();
  short midx = getmaxx() / 2, midy = getmaxy() / 2;
  char buffer[100];
  switch (opt.lang)
  {
  case 0:
    outtextxy(20, 20, "Optiuni curente:");
    outtextxy(50, 50, "Limba: Romana");
    makeBuffer(buffer);
    outtextxy(50, 70, buffer);
    makesecBuffer(buffer);
    outtextxy(50, 90, buffer);
    break;
  case 1:
    outtextxy(20, 20, "Current options:");
    outtextxy(50, 50, "Language: English");
    makeBuffer(buffer);
    outtextxy(50, 70, buffer);
    makesecBuffer(buffer);
    outtextxy(50, 90, buffer);
    break;
  }
}

void showNames(short left, short top)
{
  switch (opt.lang)
  {
  case 0:
    setbkcolor(0);
    outtextxy(left + 80 - textwidth("negru") / 2, top + 50 - textheight("negru") / 2, "negru");

    setbkcolor(1);
    outtextxy(left + 260 - textwidth("alabstru") / 2, top + 50 - textheight("alabstru") / 2, "alabstru");

    setbkcolor(2);
    outtextxy(left + 440 - textwidth("verde") / 2, top + 50 - textheight("verde") / 2, "verde");

    setbkcolor(4);
    outtextxy(left + 80 - textwidth("rosu") / 2, top + 170 - textheight("rosu") / 2, "rosu");

    setbkcolor(5);
    outtextxy(left + 260 - textwidth("magenta") / 2, top + 170 - textheight("magenta") / 2, "magenta");

    setbkcolor(14);
    setcolor(0);
    outtextxy(left + 440 - textwidth("galben") / 2, top + 170 - textheight("galben") / 2, "galben");

    break;
  case 1:
    setbkcolor(0);
    outtextxy(left + 80 - textwidth("black") / 2, top + 50 - textheight("black") / 2, "black");

    setbkcolor(1);
    outtextxy(left + 260 - textwidth("blue") / 2, top + 50 - textheight("blue") / 2, "blue");

    setbkcolor(2);
    outtextxy(left + 440 - textwidth("green") / 2, top + 50 - textheight("green") / 2, "green");

    setbkcolor(4);
    outtextxy(left + 80 - textwidth("red") / 2, top + 170 - textheight("red") / 2, "red");

    setbkcolor(5);
    outtextxy(left + 260 - textwidth("magenta") / 2, top + 170 - textheight("magenta") / 2, "magenta");

    setbkcolor(14);
    setcolor(0);
    outtextxy(left + 440 - textwidth("yellow") / 2, top + 170 - textheight("yellow") / 2, "yellow");
    break;
  }
  setcolor(15);
  setbkcolor(0);
}

void drawBars(short left, short top)
{
  // outlines
  setfillstyle(SOLID_FILL, 11);
  bar(left - 1, top - 1, left + 1 + 160, top + 1 + 100);
  bar(left - 1 + 180, top - 1, left + 1 + 340, top + 1 + 100);
  bar(left - 1 + 360, top - 1, left + 1 + 520, top + 1 + 100);

  bar(left - 1, top - 1 + 120, left + 1 + 160, top + 1 + 220);
  bar(left - 1 + 180, top - 1 + 120, left + 1 + 340, top + 1 + 220);
  bar(left - 1 + 360, top - 1 + 120, left + 1 + 520, top + 1 + 220);

  // colors
  setfillstyle(SOLID_FILL, 0);
  bar(left, top, left + 160, top + 100);
  setfillstyle(SOLID_FILL, 1);
  bar(left + 180, top, left + 340, top + 100);
  setfillstyle(SOLID_FILL, 2);
  bar(left + 360, top, left + 520, top + 100);

  setfillstyle(SOLID_FILL, 4);
  bar(left, top + 120, left + 160, top + 220);
  setfillstyle(SOLID_FILL, 5);
  bar(left + 180, top + 120, left + 340, top + 220);
  setfillstyle(SOLID_FILL, 14);
  bar(left + 360, top + 120, left + 520, top + 220);

  showNames(left, top);
}

void settingsMenu()
{
  short midx = getmaxx() / 2, midy = getmaxy() / 2;
  cleardevice();
  restore();
  readimagefile("img/ro.jpg", 40, 50, 104, 86);
  readimagefile("img/en.jpg", 40, 100, 104, 136);
  short left, top;
  switch (opt.lang)
  {
  case 0:
    outtextxy(20, 20, "Selectati limba:");
    outtextxy(120, 60, "Romana");
    outtextxy(120, 110, "Engleza");
    outtextxy(500, 20, "Selectati culoarea graficului principal:");
    left = 500 + textwidth("Selectati culoarea graficului principal:") / 2 - 260, top = 60;
    drawBars(left, top);
    drawBars(left, top + 350);
    settextstyle(font, HORIZ_DIR, 5);
    setfillstyle(SOLID_FILL, 11);
    bar(13, 460 - textheight("Inapoi la meniu") / 2 - 1, textwidth("Inapoi la meniu") + 17, 460 + textheight("Inapoi la meniu") / 2 + 1);
    outtextxy(15, 460 - textheight("Inapoi la meniu") / 2, "Inapoi la meniu");
    break;
  case 1:
    outtextxy(20, 20, "Select language:");
    outtextxy(120, 60, "Romananian");
    outtextxy(120, 110, "English");
    outtextxy(500, 20, "Select primary graph's color");
    left = 500 + textwidth("Select primary graph's color") / 2 - 260, top = 60;
    drawBars(left, top);
    drawBars(left, top + 350);
    settextstyle(font, HORIZ_DIR, 5);
    setfillstyle(SOLID_FILL, 11);
    bar(13, 460 - textheight("Back to menu") / 2 - 1, textwidth("Back to menu") + 17, 460 + textheight("Back to menu") / 2 + 1);
    outtextxy(15, 460 - textheight("Back to menu") / 2, "Back to menu");
    break;
  }
  settextstyle(font, HORIZ_DIR, 2);
  setfillstyle(SOLID_FILL, 0);
  select(left, top);
}

void start()
{
  cleardevice();
  clearmouseclick(WM_LBUTTONDOWN);
  settextstyle(font, HORIZ_DIR, 2);
  short midx = getmaxx() / 2, midy = getmaxy() / 2;
  drawSettings();
  readimagefile("img/start.jpg", midx - 100, midy - 35, midx - 30, midy + 35);
  readimagefile("img/gear.jpg", midx + 30, midy - 35, midx + 100, midy + 35);

  int x = 0, y = 0;
  while (!((x > (midx - 100) && x < (midx - 30) && y > (midy - 35) && y < (midy + 35)) ||
           (x > (midx + 30) && x < (midx + 100) && y > (midy - 35) && y < (midy + 35)))) // get click location
  {
    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }

  if (x > (midx + 30) && x < (midx + 100) && y > (midy - 35) && y < (midy + 35)) // gear
    settingsMenu();
  else if (x > (midx - 100) && x < (midx - 30) && y > (midy - 35) && y < (midy + 35)) // start
    return;                                                                           // meniu introducere functie
}

void select(short colorLeft, short colorTop)
{
  short midx = getmaxx() / 2, midy = getmaxy() / 2;
  int x = 0, y = 0;

  while (!((x > 40 && x < (120 + textwidth("Romanian")) && y > 40 && y < 86) ||                        // romana
           (x > 40 && x < 120 + textwidth("Engleza") && y > 100 && y < 136) ||                         // engleza
           (x > colorLeft && x < colorLeft + 160 && y > colorTop && y < colorTop + 100) ||             // 0  GRAFIC1
           (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop && y < colorTop + 100) ||       // 1
           (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop && y < colorTop + 100) ||       // 2
           (x > colorLeft && x < colorLeft + 160 && y > colorTop + 120 && y < colorTop + 220) ||       // 4
           (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop + 120 && y < colorTop + 220) || // 5
           (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop + 120 && y < colorTop + 220) || // 14 FINAL GRAFIC1

           (x > colorLeft && x < colorLeft + 160 && y > colorTop + 350 && y < colorTop + 350 + 100) ||             // 0  GRAFIC2
           (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop + 350 && y < colorTop + 350 + 100) ||       // 1
           (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop + 350 && y < colorTop + 350 + 100) ||       // 2
           (x > colorLeft && x < colorLeft + 160 && y > colorTop + 350 + 120 && y < colorTop + 350 + 220) ||       // 4
           (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop + 350 + 120 && y < colorTop + 350 + 220) || // 5
           (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop + 350 + 120 && y < colorTop + 350 + 220) || // 14 FINAL GRAFIC2
           (x > (13) && x < (400) && y > (460 - textheight("Inapoi la meniu") / 2) && y < (460 + textheight("Inapoi la meniu") / 2))))
  {

    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }
  if (x > 40 && x < 192 && y > 40 && y < 86)
    opt.lang = 0, save(), settingsMenu();
  else if (x > 40 && x < 204 && y > 100 && y < 136)
    opt.lang = 1, save(), settingsMenu();
  else if (x > colorLeft && x < colorLeft + 160 && y > colorTop && y < colorTop + 100)
    opt.color1 = 0, save(), settingsMenu(); // GRAFIC1
  else if (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop && y < colorTop + 100)
    opt.color1 = 1, save(), settingsMenu();
  else if (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop && y < colorTop + 100)
    opt.color1 = 2, save(), settingsMenu();
  else if (x > colorLeft && x < colorLeft + 160 && y > colorTop + 120 && y < colorTop + 220)
    opt.color1 = 4, save(), settingsMenu();
  else if (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop + 120 && y < colorTop + 220)
    opt.color1 = 5, save(), settingsMenu();
  else if (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop + 120 && y < colorTop + 220)
    opt.color1 = 14, save(), settingsMenu(); // FINAL GRAFIC1

  else if (x > colorLeft && x < colorLeft + 160 && y > colorTop + 350 && y < colorTop + 350 + 100)
    opt.color2 = 0, save(), settingsMenu(); // GRAFIC2
  else if (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop + 350 && y < colorTop + 350 + 100)
    opt.color2 = 1, save(), settingsMenu();
  else if (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop + 350 && y < colorTop + 350 + 100)
    opt.color2 = 2, save(), settingsMenu();
  else if (x > colorLeft && x < colorLeft + 160 && y > colorTop + 350 + 120 && y < colorTop + 350 + 220)
    opt.color2 = 4, save(), settingsMenu();
  else if (x > colorLeft + 180 && x < colorLeft + 340 && y > colorTop + 350 + 120 && y < colorTop + 350 + 220)
    opt.color2 = 5, save(), settingsMenu();
  else if (x > colorLeft + 360 && x < colorLeft + 520 && y > colorTop + 350 + 120 && y < colorTop + 350 + 220)
    opt.color2 = 14, save(), settingsMenu(); // FINAL GRAFIC2
  else if (x > (13) && x < (400) && y > (460 - textheight("Inapoi la meniu") / 2) && y < (460 + textheight("Inapoi la meniu") / 2))
    start();
}
