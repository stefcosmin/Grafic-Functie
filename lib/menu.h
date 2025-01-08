#pragma once
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include "settings.h"
#include "drawgraph.h"
#define font 8

void integrala()
{
  settextjustify(LEFT_TEXT, TOP_TEXT);
  int midx = getmaxx() / 2, midy = getmaxy() / 2;
  cleardevice();
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Introduceti functia:") / 2, 30, "Introduceti functia:");
    break;
  case 1:
    outtextxy(midx - textwidth("Enter the function:") / 2, 30, "Enter the function:");
    break;
  }
  char buffer[100] = "";
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
      setfillstyle(SOLID_FILL, 0);
      bar(0, 70, 1280, 120);
      setbkcolor(0);
      outtextxy(midx - textwidth(buffer) / 2, 70, buffer);
    }
  }
  char text[100] = "";
  copieFun(buffer);
  mesaj_ev(1280, 720, opt.lang, text);
  if (strcmp(text, "Functia este scrisa corect!:)") == 0 || strcmp(text, "The function is written correctly!:)") == 0)
  {
    delay(100);
    setfillstyle(SOLID_FILL, 0);
    bar(0, getmaxy() / 2, 1280, 720);
    strcpy(func[0], buffer);
    settextstyle(font, HORIZ_DIR, 2);
    outtextxy(400, 200, "Valoarea integralei definite pe intervalul [0, 1] este:");
    sprintf(buffer, "%f", calculare_integrala_functie(0, 1, &v_functie));
    outtextxy(200 + textwidth("Valoarea integralei definite pe intervalul [0, 1] este:"), 200, buffer);
  }
  else
    integrala();
}

void init()
{
  int midy = getmaxy() / 2;
  int midx = getmaxx() / 2;
  cleardevice();
  setcolor(WHITE);
  settextstyle(font, HORIZ_DIR, 4);
  char *text;
  int padding;
  switch (opt.lang)
  {
  case 0:
    text = "O singura functie";
    break;
  case 1:
    text = "One function";
    break;
  }
  setfillstyle(SOLID_FILL, LIGHTCYAN);
  bar(midx - textwidth(text) / 2 - 2, midy - textheight(text) - 50 - 2, midx + textwidth(text) / 2 + 2, midy - 48);
  outtextxy(midx - textwidth(text) / 2, midy - textheight(text) - 50, text);

  switch (opt.lang)
  {
  case 0:
    text = "Doua functii";
    break;
  case 1:
    text = "Two functions";
    break;
  }

  bar(midx - textwidth(text) / 2 - 2, midy - textheight(text) + 50 - 2, midx + textwidth(text) / 2 + 2, midy + 52);
  outtextxy(midx - textwidth(text) / 2, midy - textheight(text) + 50, text);
  settextstyle(font, HORIZ_DIR, 2);

  int x = 0, y = 0;
  while (!((x > (midx - textwidth(text) / 2 - 2) && x < (midx + textwidth(text) / 2) && y > (midy - textheight(text) - 50 - 2) && y < (midx + textwidth(text) / 2 + 2, midy - 48)) || // o singura functie
           (x > (midx - textwidth(text) / 2 - 2) && x < (midx + textwidth(text) / 2) && y > (midy - textheight(text) + 50 - 2) && y < (midy + 52))))                                  // doua functii
  {
    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }

  if (x > (midx - textwidth(text) / 2 - 2) && x < (midx + textwidth(text) / 2) && y > (midy - textheight(text) - 50 - 2) && y < (midx + textwidth(text) / 2 + 2, midy - 48))
  {
    // single
  }
  else if (x > (midx - textwidth(text) / 2 - 2) && x < (midx + textwidth(text) / 2) && y > (midy - textheight(text) + 50 - 2) && y < (midy + 52))
  {
    // double
  }
}

void introduInfSup(float &inf, float &sup, char *func1)
{

  short midx = getmaxx() / 2;
  short midy = getmaxy() / 2;
  cleardevice();
  settextstyle(font, HORIZ_DIR, 4);
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Functia introdusa:") / 2, 20, "Functia introdusa:");
    outtextxy(midx - textwidth(func1) / 2, 60, func1);

    outtextxy(midx - textwidth("Introduceti limitele intervalului") / 2, 100, "Introduceti limitele intervalului");
    outtextxy(midx - textwidth("Limita inferioara:") / 2, 150, "Limita inferioara:");
    break;
  case 1:
    outtextxy(midx - textwidth("Entered function:") / 2, 20, "Functia introdusa:");
    outtextxy(midx - textwidth(func1) / 2, 60, func1);

    outtextxy(midx - textwidth("Enter interval's limits") / 2, 100, "Enter interval's limits");
    outtextxy(midx - textwidth("Lower limit:") / 2, 150, "Lower limit:");
    break;
  }

  char buffer[100] = "";
  while (1)
  {
    delay(10);
    if (kbhit())
    {
      char c = getch();
      if (c == 13)
        break;
      else if (c == 8)
      {
        buffer[strlen(buffer) - 1] = '\0';
      }
      else
        buffer[strlen(buffer)] = c, buffer[strlen(buffer)] = '\0';
      cleardevice();

      switch (opt.lang)
      {
      case 0:
        outtextxy(midx - textwidth("Functia introdusa:") / 2, 20, "Functia introdusa:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);
        outtextxy(midx - textwidth("Introduceti limitele intervalului") / 2, 100, "Introduceti limitele intervalului");
        outtextxy(midx - textwidth("Limita inferioara:") / 2, 150, "Limita inferioara:");
        outtextxy(midx + textwidth("Limita inferioara:") / 2 + 10, 150, buffer);
        break;
      case 1:
        outtextxy(midx - textwidth("Entered function:") / 2, 20, "Entered function:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);
        outtextxy(midx - textwidth("Enter interval's limits") / 2, 100, "Enter interval's limits");
        outtextxy(midx - textwidth("Lower limit:") / 2, 150, "Lower limit:");
        outtextxy(midx + textwidth("Limita inferioara:") / 2 + 10, 150, buffer);
        break;
      }
    }
  }
  inf = atof(buffer);
  char inferior[100];
  strcpy(inferior, buffer);
  strcpy(buffer, "");
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Limita superioara:") / 2, 180, "Limita superioara:");
    break;
  case 1:
    outtextxy(midx - textwidth("Upper limit:") / 2, 180, "Upper limit:");
    break;
  }

  while (1)
  {
    delay(10);
    if (kbhit())
    {
      char c = getch();
      if (c == 13)
        break;
      else if (c == 8)
      {
        buffer[strlen(buffer) - 1] = '\0';
      }
      else
        buffer[strlen(buffer)] = c, buffer[strlen(buffer)] = '\0';
      cleardevice();

      switch (opt.lang)
      {
      case 0:
        outtextxy(midx - textwidth("Functia introdusa:") / 2, 20, "Functia introdusa:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);
        outtextxy(midx - textwidth("Introduceti limitele intervalului") / 2, 100, "Introduceti limitele intervalului");
        outtextxy(midx - textwidth("Limita inferioara:") / 2, 150, "Limita inferioara:");
        outtextxy(midx + textwidth("Limita inferioara:") / 2 + 10, 150, inferior);
        outtextxy(midx - textwidth("Limita superioara:") / 2, 180, "Limita superioara:");
        outtextxy(midx + textwidth("Limita superioara:") / 2 + 10, 180, buffer);
        break;
      case 1:
        outtextxy(midx - textwidth("Entered function:") / 2, 20, "Entered function:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);
        outtextxy(midx - textwidth("Enter interval's limits") / 2, 100, "Enter interval's limits");
        outtextxy(midx - textwidth("Lower limit:") / 2, 150, "Lower limit:");
        outtextxy(midx + textwidth("Lower limit:") / 2 + 10, 150, inferior);
        outtextxy(midx - textwidth("Upper limit:") / 2, 180, "Upper limit:");
        outtextxy(midx + textwidth("Upper limit:") / 2 + 10, 180, buffer);
        break;
      }
    }
  }
  sup = atof(buffer);
  lower = inf, upper = sup;
}

void introduInfSup(float &inf, float &sup, char *func1, char *func2)
{
  short midx = getmaxx() / 2;
  short midy = getmaxy() / 2;
  cleardevice();
  settextstyle(font, HORIZ_DIR, 4);
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Functia principala introdusa:") / 2, 20, "Functia principala introdusa:");
    outtextxy(midx - textwidth(func1) / 2, 60, func1);

    outtextxy(midx - textwidth("Functia secundara introdusa:") / 2, 100, "Functia secundara introdusa:");
    outtextxy(midx - textwidth(func2) / 2, 130, func2);

    outtextxy(midx - textwidth("Introduceti limitele intervalului") / 2, 160, "Introduceti limitele intervalului");
    outtextxy(midx - textwidth("Limita inferioara:") / 2, 200, "Limita inferioara:");
    break;
  case 1:
    outtextxy(midx - textwidth("Primary entered function:") / 2, 20, "Primary entered function:");
    outtextxy(midx - textwidth(func1) / 2, 60, func1);

    outtextxy(midx - textwidth("Primary entered function:") / 2, 100, "Primary entered function:");
    outtextxy(midx - textwidth(func2) / 2, 60, func2);

    outtextxy(midx - textwidth("Enter interval's limits") / 2, 160, "Enter interval's limits");
    outtextxy(midx - textwidth("Lower limit:") / 2, 200, "Lower limit:");
    break;
  }

  char buffer[100] = "";

  while (1)
  {
    delay(10);
    if (kbhit())
    {
      char c = getch();
      if (c == 13)
        break;
      else if (c == 8)
      {
        buffer[strlen(buffer) - 1] = '\0';
      }
      else
        buffer[strlen(buffer)] = c, buffer[strlen(buffer)] = '\0';
      cleardevice();

      switch (opt.lang)
      {
      case 0:
        outtextxy(midx - textwidth("Functia principala introdusa:") / 2, 20, "Functia principala introdusa:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);

        outtextxy(midx - textwidth("Functia secundara introdusa:") / 2, 100, "Functia secundara introdusa:");
        outtextxy(midx - textwidth(func2) / 2, 130, func2);

        outtextxy(midx - textwidth("Introduceti limitele intervalului") / 2, 160, "Introduceti limitele intervalului");
        outtextxy(midx - textwidth("Limita inferioara:") / 2, 200, "Limita inferioara:");
        outtextxy(midx + textwidth("Limita inferioara:") / 2 + 10, 200, buffer);
        break;
      case 1:
        outtextxy(midx - textwidth("Primary entered function:") / 2, 20, "Primary entered function:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);

        outtextxy(midx - textwidth("Primary entered function:") / 2, 100, "Primary entered function:");
        outtextxy(midx - textwidth(func2) / 2, 60, func2);

        outtextxy(midx - textwidth("Enter interval's limits") / 2, 160, "Enter interval's limits");
        outtextxy(midx - textwidth("Lower limit:") / 2, 200, "Lower limit:");
        outtextxy(midx + textwidth("Limita inferioara:") / 2 + 10, 200, buffer);
        break;
      }
    }
  }
  inf = atof(buffer);
  char inferior[100];
  strcpy(inferior, buffer);
  strcpy(buffer, "");
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Limita superioara:") / 2, 230, "Limita superioara:");
    break;
  case 1:
    outtextxy(midx - textwidth("Upper limit:") / 2, 230, "Upper limit:");
    break;
  }

  while (1)
  {
    delay(10);
    if (kbhit())
    {
      char c = getch();
      if (c == 13)
        break;
      else if (c == 8)
      {
        buffer[strlen(buffer) - 1] = '\0';
      }
      else
        buffer[strlen(buffer)] = c, buffer[strlen(buffer)] = '\0';
      cleardevice();

      switch (opt.lang)
      {
      case 0:
        outtextxy(midx - textwidth("Functia principala introdusa:") / 2, 20, "Functia principala introdusa:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);

        outtextxy(midx - textwidth("Functia secundara introdusa:") / 2, 100, "Functia secundara introdusa:");
        outtextxy(midx - textwidth(func2) / 2, 130, func2);

        outtextxy(midx - textwidth("Introduceti limitele intervalului") / 2, 160, "Introduceti limitele intervalului");
        outtextxy(midx - textwidth("Limita inferioara:") / 2, 200, "Limita inferioara:");
        outtextxy(midx + textwidth("Limita inferioara:") / 2 + 10, 200, inferior);
        outtextxy(midx - textwidth("Limita superioara:") / 2, 230, "Limita superioara:");
        outtextxy(midx + textwidth("Limita superioara:") / 2 + 10, 230, buffer);
        break;
      case 1:
        outtextxy(midx - textwidth("Primary entered function:") / 2, 20, "Primary entered function:");
        outtextxy(midx - textwidth(func1) / 2, 60, func1);

        outtextxy(midx - textwidth("Primary entered function:") / 2, 100, "Primary entered function:");
        outtextxy(midx - textwidth(func2) / 2, 60, func2);

        outtextxy(midx - textwidth("Enter interval's limits") / 2, 160, "Enter interval's limits");
        outtextxy(midx - textwidth("Lower limit:") / 2, 200, "Lower limit:");
        outtextxy(midx + textwidth("Limita inferioara:") / 2 + 10, 200, inferior);
        outtextxy(midx - textwidth("Upper limit:") / 2, 230, "Upper limit:");
        outtextxy(midx + textwidth("Upper limit:") / 2 + 10, 230, buffer);
        break;
      }
    }
  }
  sup = atof(buffer);
}

void singleFunc()
{
  settextjustify(LEFT_TEXT, TOP_TEXT);
  cleardevice();
  setcolor(WHITE);
  char text[100] = "";
  char buffer[100] = "";
  switch (opt.lang)
  {
  case 0:
    strcpy(text, "Introduceti functia pentru a incepe");
    break;
  case 1:
    strcpy(text, "Enter the function");
    break;
  }

  settextstyle(font, HORIZ_DIR, 4);
  outtextxy(getmaxx() / 2 - textwidth(text) / 2, 50, text);
  while (1)
  {
    delay(10);
    if (kbhit())
    {
      char c = getch();
      if (c == 13)
        break;
      else if (c == 8)
      {
        buffer[strlen(buffer) - 1] = '\0';
      }
      else
        buffer[strlen(buffer)] = c, buffer[strlen(buffer)] = '\0';
      cleardevice();
      outtextxy(getmaxx() / 2 - textwidth(text) / 2, 50, text);
      outtextxy(getmaxx() / 2 - textwidth(buffer) / 2, 80, buffer);
    }
  }
  toLow(buffer);
  copieFun(buffer);

  strcpy(text, "");
  mesaj_ev(1280, 720, opt.lang, text);
  if (strcmp(text, "Functia este scrisa corect!:)") == 0 || strcmp(text, "The function is written correctly!:)") == 0)
    strcpy(func[0], buffer), strcpy(func[1], ""), strcpy(asimp, buffer);
  else
    singleFunc();
}

void menu()
{
  short midx = getmaxx() / 2;
  short midy = getmaxy() / 2;
  cleardevice();
  settextstyle(font, HORIZ_DIR, 4);
  setcolor(opt.accent);
  rectangle(midx - textwidth("Modul de grafic") / 2 - 5, midy - 125, midx + textwidth("Modul de grafic") / 2 + 5, midy - 75);
  rectangle(midx - textwidth("Calculate definite integral on [0,1]") / 2 - 5, midy - textheight("Calculate definite integral on [0,1]") - 20 - 5, midx + textwidth("Calculate definite integral on [0,1]") / 2 + 5, midy - 15);
  rectangle(midx - textwidth("Calculate the asymptotes of a function") / 2 - 5, midy + 15, midx + textwidth("Calculate the asymptotes of a function") / 2 + 5, midy + 15 + textheight("Calculate the asymptotes of a function") + 5);
  rectangle(midx - textwidth("Trasarea graficului unei functii pe un interval definit") / 2 - 5, midy + 75, midx + textwidth("Trasarea graficului unei functii pe un interval definit") / 2 + 5, midy + 85 + textheight("Trasarea graficului unei functii pe un interval definit") + 5);
  setcolor(WHITE);
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Modul de grafic") / 2, midy - 115, "Modul de grafic");
    outtextxy(midx - textwidth("Calculare integrala definita [0,1]") / 2, midy - textheight("Calculare integrala definita [0,1]") - 20, "Calculare integrala definita [0,1]");
    outtextxy(midx - textwidth("Calcularea asimptotelor unei functii") / 2, midy + 20, "Calcularea asimptotelor unei functii");
    outtextxy(midx - textwidth("Trasarea graficului unei functii pe un interval definit") / 2, midy + 80, "Trasarea graficului unei functii pe un interval definit");
    break;
  case 1:
    outtextxy(midx - textwidth("graph mode") / 2, midy - 115, "Graph mode");
    outtextxy(midx - textwidth("Calculate definite integral on [0,1]") / 2, midy - textheight("Calculate definite integral on [0,1]") - 20, "Calculate definite integral on [0,1]");
    outtextxy(midx - textwidth("Calculate the asymptotes of a function") / 2, midy + 20, "Calculate the asymptotes of a function");
    outtextxy(midx - textwidth("A funciton's graph on a defined interval") / 2, midy + 80, "A funciton's graph on a defined interval");

    break;
  }
  int x = 0, y = 0;
  while (!((x > (midx - textwidth("Modul de grafic") / 2 - 5) && x < (midx + textwidth("Modul de grafic") / 2 + 5) && y > (midy - 125) && y < (midy - 75)) ||                                                                                                                                                           // grafic
           (x > (midx - textwidth("Calculate definite integral on [0,1]") / 2 - 5) && x < (midx + textwidth("Calculate definite integral on [0,1]") / 2 + 5) && y > (midy - textheight("Calculate definite integral on [0,1]") - 20 - 5) && y < (midy - 15)) ||                                                         // integrala
           (x > (midx - textwidth("Calculate the asymptotes of a function") / 2 - 5) && x < (midx + textwidth("Calculate the asymptotes of a function") / 2 + 5) && y > (midy + 15) && y < (midy + 15 + textheight("Calculate the asymptotes of a function") + 5)) ||                                                   // asimptote
           (x > (midx - textwidth("Trasarea graficului unei functii pe un interval definit") / 2 - 5) && x < (midx + textwidth("Trasarea graficului unei functii pe un interval definit") / 2 + 5) && y > (midy + 75) && y < (midy + 85 + textheight("Trasarea graficului unei functii pe un interval definit") + 5)))) // grafic pe interval definit
  {
    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }
  if (x > (midx - textwidth("Modul de grafic") / 2 - 5) && x < (midx + textwidth("Modul de grafic") / 2 + 5) && y > (midy - 125) && y < (midy - 75))
  {
    graphMode();
  }
  else if (x > (midx - textwidth("Calculate definite integral on [0,1]") / 2 - 5) && x < (midx + textwidth("Calculate definite integral on [0,1]") / 2 + 5) && y > (midy - textheight("Calculate definite integral on [0,1]") - 20 - 5) && y < (midy - 15))
  {
    integrala();
  }
  else if (x > (midx - textwidth("Calculate the asymptotes of a function") / 2 - 5) && x < (midx + textwidth("Calculate the asymptotes of a function") / 2 + 5) && y > (midy + 15) && y < (midy + 15 + textheight("Calculate the asymptotes of a function") + 5))
  {
    singleFunc();
    settextjustify(LEFT_TEXT, TOP_TEXT);
    drawAsimp();
  }
  else if (x > (midx - textwidth("Trasarea graficului unei functii pe un interval definit") / 2 - 5) && x < (midx + textwidth("Trasarea graficului unei functii pe un interval definit") / 2 + 5) && y > (midy + 75) && y < (midy + 85 + textheight("Trasarea graficului unei functii pe un interval definit") + 5))
  {
    singleFunc();
    settextjustify(LEFT_TEXT, TOP_TEXT);
    introduInfSup(inf, sup, func[0]);
    char text[256] = "";
    ev_interval(1280, 720, inf, sup, opt.lang, text);
    if (strcmp(text, "Intervalul este bine ales") == 0 || strcmp(text, "The range is well chosen") == 0)
      drawFun();
  }
}
