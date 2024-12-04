#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <climits>
#include <cctype>
#include <conio.h>
#include "lib/menu.h"
char t[100];
int main()
{
  initwindow(1280, 720, "Calculator grafic functie");
  init(t);
  menu(t);
  getch();
  closegraph();
  return 0;
}