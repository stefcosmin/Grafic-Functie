#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <climits>
#include <cctype>
#include <conio.h>
#include "lib/menu.h"
char s[256];
char *t;
void citire()
{
  std::cin.getline(s, 255);
  t = s;
}

int main()
{
  initwindow(1280, 720, "Calculator grafic functie");
  init();
  citire();
  menu(t);
  getch();
  closegraph();
  return 0;
}