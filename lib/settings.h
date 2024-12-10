#include <cmath>
#include <cstdio>
#include <cstring>
#include <graphics.h>
#include <winbgim.h>

// 0 negru
// 1 rosu
// 4 albastru
// 5 magenta
// 6 albastru deschis
// 8 verde
// 9 maro
// 10 verde deschis
// 11 galben
// 12 cyan

struct settings
{
  string lang = "";
  int color;
} settings;

void start()
{
  readimagefile("img/gear.jpg", 0, 0, 500, 500);
}