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
  graphBorder();
  start();
  init(func);
  menu(func);
  copieFun(func);
  cleardevice();
  drawPZ();

  setfillstyle(SOLID_FILL, COLOR(190, 190, 190));
  bar(0, 0, DRP, JOS);
  desenare_grafic_functie(-2 * pi, 2 * pi, opt.color, 4);

  getch();
  closegraph();
  return 0;
}