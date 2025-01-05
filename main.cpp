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
  // init();
  initial();
  getch();
  return 0;
}
