#pragma once
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include "settings.h"
#include "drawgraph.h"
#define font 8

void clearBuffer(char *buffer)
{
  for (int i = 0; i < 100; i++)
    buffer[i] = '\0';
}

void toLow(char *buffer)
{
  for (int i = 0; i < strlen(buffer); i++)
  {
    if (isalpha(buffer[i]) && isupper(buffer[i]))
      buffer[i] = tolower(buffer[i]);
  }
}

void singleFunc(char *buffer)
{
  cleardevice();
  setcolor(WHITE);
  char *text;
  switch (opt.lang)
  {
  case 0:
    text = "Introduceti functia pentru a incepe";
    break;
  case 1:
    text = "Enter the function";
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
}

void doubleFunc(char *func1, char *func2)
{
  cleardevice();
  setcolor(WHITE);
  char *text;
  switch (opt.lang)
  {
  case 0:
    text = "Introduceti prima functie";
    break;
  case 1:
    text = "Enter the first function";
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
        func1[strlen(func1) - 1] = '\0';
      }
      else
        func1[strlen(func1)] = c, func1[strlen(func1)] = '\0';
      cleardevice();
      outtextxy(getmaxx() / 2 - textwidth(text) / 2, 50, text);
      outtextxy(getmaxx() / 2 - textwidth(func1) / 2, 80, func1);
    }
  }
  toLow(func1);
  // final prima functie

  switch (opt.lang)
  {
  case 0:
    text = "Introduceti a doua functie";
    break;
  case 1:
    text = "Enter the second function";
    break;
  }

  settextstyle(font, HORIZ_DIR, 4);
  outtextxy(getmaxx() / 2 - textwidth(text) / 2, 120, text);
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
        func2[strlen(func2) - 1] = '\0';
      }
      else
        func2[strlen(func2)] = c, func2[strlen(func2)] = '\0';
      cleardevice();
      outtextxy(getmaxx() / 2 - textwidth(text) / 2, 50, text);
      outtextxy(getmaxx() / 2 - textwidth(func1) / 2, 80, func1);
      outtextxy(getmaxx() / 2 - textwidth(text) / 2, 120, text);
      outtextxy(getmaxx() / 2 - textwidth(func2) / 2, 160, func2);
    }
  }
  toLow(func2);
}

void init(char *func1, char *func2)
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
    singleFunc(func1);
  }
  else if (x > (midx - textwidth(text) / 2 - 2) && x < (midx + textwidth(text) / 2) && y > (midy - textheight(text) + 50 - 2) && y < (midy + 52))
  {
    doubleFunc(func1, func2);
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

  char buffer[100];
  clearBuffer(buffer);

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
  clearBuffer(buffer);
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

  char buffer[100];
  clearBuffer(buffer);

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
  clearBuffer(buffer);
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

void menu(char *func1)
{
  short midx = getmaxx() / 2;
  short midy = getmaxy() / 2;
  cleardevice();
  settextstyle(font, HORIZ_DIR, 4);
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Functia introdusa:") / 2, 20, "Functia introdusa:");
    break;
  case 1:
    outtextxy(midx - textwidth("Entered function:") / 2, 20, "Entered function:");
    break;
  }

  outtextxy(midx - textwidth(func1) / 2, 60, func1);
  setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Doriti reprezentarea functiei pe un anumit interval?") / 2, 140, "Doriti reprezentareaa functiei pe un anumit interval?");
    break;
  case 1:
    outtextxy(midx - textwidth("Do you want to represent function on a custom interval") / 2, 140, "Do you want to represent function on a custom interval");
    break;
  }

  settextstyle(font, HORIZ_DIR, 6);

  switch (opt.lang)
  {
  case 0:
    bar(midx - textwidth("DA") - 25, midy - 60 - textheight("DA"), midx - 15, midy - 50);
    bar(midx + 15, midy - 60 - textheight("NU"), midx + textwidth("NU") + 25, midy - 50);

    outtextxy(midx - textwidth("DA") - 20, midy - 55 - textheight("DA"), "DA");
    outtextxy(midx + 20, midy - 55 - textheight("NU"), "NU");
    break;
  case 1:
    bar(midx - textwidth("YES") - 25, midy - 60 - textheight("YES"), midx - 15, midy - 50);
    bar(midx + 15, midy - 60 - textheight("NO"), midx + textwidth("NO") + 25, midy - 50);

    outtextxy(midx - textwidth("YES") - 20, midy - 55 - textheight("YES"), "YES");
    outtextxy(midx + 20, midy - 55 - textheight("NO"), "NO");
    break;
  }

  int x = 0, y = 0;
  while (!((x > (midx - textwidth("DA") - 25) && x < (midx - 15) && y > (midy - 60 - textheight("YES")) && y < (midy - 50)) || (x > (midx + 15) && x < (midx + textwidth("NU") + 25) && y > (midy - 60 - textheight("NU")) && y < (midy - 50))))
  {

    while (!ismouseclick(WM_LBUTTONDOWN))
      ;
    getmouseclick(WM_LBUTTONDOWN, x, y);
  }
  if (x > (midx - textwidth("YES") - 25) && x < (midx - 15) && y > (midy - 60 - textheight("YES")) && y < (midy - 50))
  {
    introduInfSup(lower, upper, func1);
  }
  else if (x > (midx + 15) && x < (midx + textwidth("NU") + 25) && y > (midy - 60 - textheight("NU")) && y < (midy - 50))
  {
  }
}

void menu(char *func1, char *func2)
{

  short midx = getmaxx() / 2;
  short midy = getmaxy() / 2;
  cleardevice();
  settextstyle(font, HORIZ_DIR, 4);
  switch (opt.lang)
  {
  case 0:
    outtextxy(midx - textwidth("Functia principala introdusa:") / 2, 20, "Functia principala introdusa:");
    outtextxy(midx - textwidth("Functia secundara introdusa:") / 2, 100, "Functia secundara introdusa:");
    break;
  case 1:
    outtextxy(midx - textwidth("Primary entered function:") / 2, 20, "Primary entered function:");
    outtextxy(midx - textwidth("Secondary entered function:") / 2, 100, "Secondary entered function:");
    break;
  }

  outtextxy(midx - textwidth(func1) / 2, 50, func1);
  outtextxy(midx - textwidth(func2) / 2, 130, func2);
  setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
  introduInfSup(lower, upper, func1, func2);
}