#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <climits>
#include <cctype>
#include <conio.h>
#include "lib/menu.h"
#include "lib/func.h"
char t[100];
int main()
{
  initwindow(1280, 720, "Calculator grafic functie");
  init(t);
  menu(t);
  transformare_functie(t);
  transformare_din_infix_in_postfix();
  while (!esteVidaS(postfixata))
  {
    cout << postfixata->inf << " ";
    pop(postfixata);
  }
  getch();
  closegraph();
  return 0;
}