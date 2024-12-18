#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <climits>
#include <cctype>
#include <conio.h>
#include "lib/menu.h"
#include "lib/func.h"
#include "lib/settings.h"
#include "lib/drawgraph.h"
char func1[100] = "";
char func2[100] = "";
int main()
{
  initwindow(1280, 720, "Calculator grafic functie");
  start();
  init(func1, func2);
  switch (strlen(func2))
  {
  case 0:
    menu(func1);
    copieFun(func1);
    cleardevice();
    drawFun();
    getch();
    closegraph();
    break;
  default:
    menu(func1, func2);
    cleardevice();
    drawFun(func1, func2);
    getch();
    closegraph();
  }
  /*singleFunc(func);
  menu(func);
  copieFun(func);
  drawFun();
  getch();
  closegraph();*/
  return 0;
}