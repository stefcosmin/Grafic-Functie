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
char func[100];
int main()
{
  initwindow(1280, 720, "Calculator grafic functie");
  start();
  init(func);
  menu(func);
  copieFun(func);
  drawFun();
  getch();
  closegraph();
  return 0;
}