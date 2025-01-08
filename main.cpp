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

int main()
{
  initwindow(1280, 720, "Calculator grafic functie");
  start();
  menu();
  getch();
  closegraph();
  return 0;
}
