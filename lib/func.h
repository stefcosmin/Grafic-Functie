#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <graphics.h>
#include <winbgim.h>
#include <cstring>
#include <cmath>
#include <climits>
#define pi 3.141592
#define e 2.718281
#define epsilon 0.000001
#define infinit ULLONG_MAX
using namespace std;
char fun[256], func[256][7], asimp[256];
char vect[256];
int v[50];
double MINI, MAXI, minim, maxim;
double dim;
int unitate, midy, midx, width;
int STG = 0, DRP = 960, SUS = 0, JOS = 720, yoffset = 0;

void GraphBorder(double A, double B)
{

  dim = B - A;
  int i;
  width = DRP - STG;
  unitate = width / dim;

  midx = getmaxx() / 2;
  midy = getmaxy() / 2;
  DRP = getmaxx() - getmaxx() / 4;
  SUS = midy - abs(MAXI) * unitate + yoffset;
  STG = 0;
  JOS = midy + abs(MINI) * unitate + yoffset;
  // printf("drp:%d   stg:%d   sus:%d   jos:%d  midy:%d", DRP, STG, SUS, JOS, midy);
  // printf("     absmini:%f     unitate:%f", abs(MINI), unitate);
}

struct nod
{
  char inf;
  double info;
  nod *urm;
};
nod *infixata, *postfixata, *S;

void push(nod *&varf, char element)
{
  nod *Stiva;
  Stiva = new nod;
  Stiva->inf = element;
  Stiva->urm = varf;
  varf = Stiva;
}
void pushc(nod *&varf, double val)
{
  nod *stiva;
  stiva = new nod;
  stiva->info = val;
  stiva->urm = varf;
  varf = stiva;
}
void pop(nod *&varf)
{
  nod *Stiva = varf;
  varf = varf->urm;
  delete Stiva;
}

bool esteVidaS(nod *&Stiva)
{
  if (Stiva == NULL)
    return 1;
  else
    return 0;
}

void stivaVida(nod *&S)
{
  S = NULL;
}
void eliminare(nod *&postfixata)
{
  nod *q;
  q = postfixata;
  postfixata = postfixata->urm;
  delete q;
}

void inserare(nod *&postfixata, char element)
{
  nod *q = new nod;
  q->inf = element;
  q->urm = NULL;
  if (postfixata == NULL)
    postfixata = q;
  else
  {
    nod *p = postfixata;
    while (p->urm != NULL)
      p = p->urm;
    p->urm = q;
  }
}
bool esteVidaC(nod *&prim)
{
  if (prim == NULL)
    return 1;
  else
    return 0;
}

void coadaVida(nod *&prim)
{
  prim = NULL;
}

double operatie_speciala(char op, double x)
{
  if (op == 's')
    return sin(x);
  if (op == 'c')
    return cos(x);
  if (op == 'l')
    return log(x);
  if (op == 't')
    return tan(x);
  if (op == 'r')
    return sqrt(x);
  if (op == 'g')
    return 1.0 / tan(x);
  if (op == 'e')
    return exp(x);
}

double operatie(char op, double x, double y)
{
  if (op == '+')
    return x + y;
  if (op == '-')
    return x - y;
  if (op == '*')
    return x * y;
  if (op == '/')
    return x / y;
  if (op == '^')
    return pow(x, y);
}

void transformare_functie()
{
  int i = 0, j, nr = 0;
  double numar;
  while (i <= strlen(fun) - 1)
  {
    if (isdigit(fun[i]) != 0)
    {
      while (isdigit(fun[i]) != 0)
      {
        vect[nr] = fun[i];
        i++;
        j = 1;
        nr++;
      }
      vect[nr] = ' ';
      nr++;
    }
    else if (strchr("+-*^/)(", fun[i]))
    {
      vect[nr] = fun[i];
      nr++;
      i = i + 1;
      j = 1;
      vect[nr] = ' ';
      nr++;
    }
    else if (fun[i] == 'x')
    {
      vect[nr] = fun[i];
      nr++;
      j = 1;
      i++;
      vect[nr] = ' ';
      nr++;
    }
    else
    {
      if ('s' == fun[i])
      {
        vect[nr] = fun[i];
        nr++;
        i = i + 3;
        j = 3;
        vect[nr] = ' ';
        nr++;
      }
      else if ('c' == fun[i] && fun[i + 1] == 'o')
      {
        vect[nr] = fun[i];
        nr++;
        i = i + 3;
        j = 3;
        vect[nr] = ' ';
        nr++;
      }
      else if ('l' == fun[i])
      {
        vect[nr] = fun[i];
        nr++;
        i = i + 2;
        j = 2;
        vect[nr] = ' ';
        nr++;
      }
      else if ('t' == fun[i])
      {
        vect[nr] = fun[i];
        nr++;
        i = i + 2;
        j = 2;
      }
      else if ('r' == fun[i])
      {
        vect[nr] = fun[i];
        nr++;
        i = i + 3;
        j = 3;
      }
      else if ('c' == fun[i] && 't' == fun[i + 1])
      {
        vect[nr] = 'g';
        nr++;
        i = i + 3;
        j = 3;
      }
      else if ('e' == fun[i])
      {
        vect[nr] = fun[i];
        nr++;
        i = i + 3;
        j = 3;
      }
    }
  }

  for (i = 0; i <= strlen(vect) - 1; i++)
    if (vect[i] != ' ')
      inserare(infixata, vect[i]);
}

int prioritate_caracter(char a)
{
  if (strchr("+", a) || strchr("-", a))
    return 1;
  else if (strchr("*", a) || strchr("/", a))
    return 2;
  else if (strchr("^", a))
    return 3;
  else if (strchr("scltrge", a))
    return 4;
  else if (strchr("(", a) || strchr(")", a))
    return 5;
}

void transformare_din_infix_in_postfix()
{
  while (esteVidaC(infixata) == 0)
  {
    if (infixata->inf == 'x')
    {
      inserare(postfixata, 'x');
      eliminare(infixata);
    }

    else if (isdigit(infixata->inf))
    {
      inserare(postfixata, infixata->inf);
      eliminare(infixata);
    }
    else if (infixata->inf == ')')
    {
      while (S->inf != '(')
      {
        inserare(postfixata, S->inf);
        pop(S);
      }
      pop(S);
      eliminare(infixata);
    }

    else
    {
      while (esteVidaS(S) == 0 && S->inf != '(' && prioritate_caracter(S->inf) >= prioritate_caracter(infixata->inf))
      {
        inserare(postfixata, S->inf);
        pop(S);
      }
      push(S, infixata->inf);
      eliminare(infixata);
    }
  }
  while (esteVidaS(S) == 0)
  {
    inserare(postfixata, S->inf);
    pop(S);
  }
}

double calculare_val_fct_din_postf(double x)
{
  double val;
  while (!esteVidaC(postfixata))
  {
    if (postfixata->inf == 'x')
    {
      pushc(S, x);
      eliminare(postfixata);
    }
    else if (isdigit(postfixata->inf))
    {
      val = 0;
      while (isdigit(postfixata->inf))
      {
        char c = postfixata->inf;
        val = val * 10 + (c - '0');
        eliminare(postfixata);
      }
      pushc(S, val);
    }
    else if (strchr("+-*/^", postfixata->inf))
    {
      double val1, val2, valf;
      val1 = S->info;
      pop(S);
      val2 = S->info;
      pop(S);
      char op = postfixata->inf;
      valf = operatie(op, val2, val1);
      eliminare(postfixata);
      pushc(S, valf);
    }
    else if (strchr("sclrtge", postfixata->inf))
    {
      double val1, valf;
      val1 = S->info;
      pop(S);
      char op = postfixata->inf;
      valf = operatie_speciala(op, val1);
      eliminare(postfixata);
      pushc(S, valf);
    }
  }
  double rezultat = S->info;
  pop(S);
  return rezultat;
}
double v_functie(double x)
{
  transformare_functie();
  transformare_din_infix_in_postfix();
  return calculare_val_fct_din_postf(x);
}

int discontinuitate(double x)
{
  double ep = 1e-6;
  double limstg = v_functie(x - ep); // calculam limita la stanga
  double limdr = v_functie(x + ep);  // calculam limita la dreapta
  double valf = v_functie(x);        // calculam valoarea functiei in acel punct
  if ((isinf(limstg) || isinf(limdr)) || abs(limstg - limdr) > ep || (abs(limstg - limdr) <= ep && abs(valf - limstg) > ep))
    return 1; // daca limitele sunt infinite sau nu sunt egale sau ele sunt egale dar valoarea functiei in punct nu e la fel, atunci f e discontinua
  else
    return 0; // f continua
}

void minim_si_maxim(double A, double B) // aflam minimul si maximul functiei
{
  double x, y;
  MINI = 100000001;
  MAXI = -MINI;
  for (int i = 0; i <= (DRP - STG); i++)
  {
    x = A + i * (B - A) / (DRP - STG);
    y = v_functie(x);
    MAXI = max(MAXI, y);
    MINI = min(MINI, y);
  }
}

void minim_si_maxim_normalizate(double A, double B, double &minim, double &maxim)
{ // aflam minimul si maximul functiei transformate in coordonate pe ecran
  double x, y, ypct;
  x = A;
  y = v_functie(x);
  minim = 100000001;
  maxim = -minim;
  minim_si_maxim(A, B);
  for (int i = 0; i <= DRP - STG; i++)
  {
    x = A + i * (B - A) / (DRP - STG);
    y = v_functie(x);
    ypct = (int)(JOS - SUS) * y / (MAXI - MINI) + (MAXI * SUS - MINI * JOS) / (MAXI - MINI);
    minim = min(minim, ypct);
    maxim = max(maxim, ypct);
  }
}

void desenare_grafic_functie(double A, double B, int culoaregrafic)
{

  int i;
  double x, y, xe, ye, xpct, ypct;
  minim_si_maxim_normalizate(A, B, minim, maxim);
  x = A;
  y = v_functie(A);
  minim_si_maxim(A, B);
  xe = (DRP - STG) * x / (B - A) + (B * STG - A * DRP) / (B - A);
  ye = (JOS - SUS) * y / (MAXI - MINI) + (MAXI * SUS - MINI * JOS) / (MAXI - MINI);
  for (i = 0; i <= DRP - STG; i++)
  {
    x = A + i * (B - A) / (DRP - STG);
    y = v_functie(x);
    xpct = (DRP - STG) * x / (B - A) + (B * STG - A * DRP) / (B - A);
    ypct = JOS - (JOS - SUS) * (y - MINI) / (MAXI - MINI);

    /*if (discontinuitate(x))
    {
      setcolor(COLOR(18, 18, 18));
      // line(xe, SUS + 2, xe, JOS - 2);
      if (culoarechenar == 1)
        setcolor(RED);
      else if (culoarechenar == 2)
        setcolor(GREEN);
      else if (culoarechenar == 3)
        setcolor(BLUE);
      else if (culoarechenar == 4)
        setcolor(MAGENTA);
      rectangle(STG, SUS, DRP, JOS);
    }*/

    if (ypct == minim)
    {
      setcolor(WHITE);
      line(xe, ye, xpct, ypct);
    }
    else if (ypct == maxim)
    {
      setcolor(WHITE);
      line(xe, ye, xpct, ypct);
    }
    else
    {
      setcolor(culoaregrafic);
      line(xe, ye, xpct, ypct);
    }
    xe = xpct;
    ye = ypct;
  }
}

void desenare_axe(double A, double B)
{
  dim = B - A;
  unitate = (DRP - STG) / dim;
  int SUS = 0, STG = 0, JOS = getmaxy(), DRP = getmaxx() - getmaxx() / 4;
  setcolor(BLACK);

  line(STG - A * unitate, SUS, STG - A * unitate, JOS); // OY
  // sagetile OY
  line(STG - A * unitate - 2, SUS + 2, STG - A * unitate, SUS);
  line(STG - A * unitate + 2, SUS + 2, STG - A * unitate, SUS);
  int i;
  i = midy;
  while (i <= JOS)
  {
    char buffer[10] = "";
    sprintf(buffer, "%d", (midy - i + yoffset) / unitate);
    line(STG - A * unitate - 2, i, STG - A * unitate + 2, i);
    settextstyle(font, HORIZ_DIR, 1);
    setbkcolor(COLOR(190, 190, 190));
    if (6 * unitate >= width / 2)
    {
      outtextxy(STG - A * unitate + 2, i, buffer);
    }
    else if ((20 * unitate >= width / 2))
    {
      if (((midy - i + yoffset) / unitate) % 2 == 0)
        outtextxy(STG - A * unitate + 2, i, buffer);
    }
    else if ((40 * unitate >= width / 2))
    {
      if (((midy - i + yoffset) / unitate) % 10 == 0)
        outtextxy(STG - A * unitate + 2, i, buffer);
    }
    else if (((midy - i + yoffset) / unitate) % 20 == 0)
    {
      outtextxy(STG - A * unitate + 2, i, buffer);
    }
    i += unitate;
  }

  i = midy - unitate;

  while (i >= SUS)
  {
    char buffer[10] = "";
    sprintf(buffer, "%d", (midy - i + yoffset) / unitate);
    line(STG - A * unitate - 2, i, STG - A * unitate + 2, i);
    settextstyle(font, HORIZ_DIR, 1);
    setbkcolor(COLOR(190, 190, 190));
    if (6 * unitate >= width / 2)
    {
      outtextxy(STG - A * unitate + 2, i, buffer);
    }
    else if ((20 * unitate >= width / 2))
    {
      if (((midy - i + yoffset) / unitate) % 2 == 0)
        outtextxy(STG - A * unitate + 2, i, buffer);
    }
    else if ((40 * unitate >= width / 2))
    {
      if (((midy - i + yoffset) / unitate) % 8 == 0)
        outtextxy(STG - A * unitate + 2, i, buffer);
    }
    else if (((midy - i + yoffset) / unitate) % 20 == 0)
    {
      outtextxy(STG - A * unitate + 2, i, buffer);
    }
    i -= unitate;
  }
  // final oy

  line(STG, SUS + (JOS - SUS) / 2 + yoffset, DRP, SUS + (JOS - SUS) / 2 + yoffset); // OX
  // sagetile OX
  line(DRP - 2, SUS + (JOS - SUS) / 2 - 2 + yoffset, DRP, SUS + (JOS - SUS) / 2 + yoffset);
  line(DRP - 2, SUS + (JOS - SUS) / 2 + 2 + yoffset, DRP, SUS + (JOS - SUS) / 2 + yoffset);

  int *oy = new int;
  *oy = STG - A * unitate;
  i = *oy + unitate;
  while (i <= DRP - textwidth("-88"))
  {
    char buffer[10] = "";
    sprintf(buffer, "%d", (i - *oy) / unitate);
    line(i, SUS + (JOS - SUS) / 2 - 2 + yoffset, i, SUS + (JOS - SUS) / 2 + 2 + yoffset);
    settextstyle(font, HORIZ_DIR, 1);

    setbkcolor(COLOR(190, 190, 190));
    if (12 * unitate >= width / 2)
    {
      outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }
    else if ((30 * unitate >= width / 2))
    {
      if (((i - *oy) / unitate) % 2 == 0)
        outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }
    else if ((70 * unitate >= width / 2))
    {
      if (((i - *oy) / unitate) % 8 == 0)
        outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }
    else if (((i - *oy) / unitate) % 20 == 0)
    {
      outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }
    i += unitate;
  }
  i = *oy - unitate;
  while (i >= STG)
  {
    char buffer[10] = "";
    sprintf(buffer, "%d", (i - *oy) / unitate);
    line(i, SUS + (JOS - SUS) / 2 - 2 + yoffset, i, SUS + (JOS - SUS) / 2 + 2 + yoffset);
    settextstyle(font, HORIZ_DIR, 1);
    setbkcolor(COLOR(190, 190, 190));

    if (12 * unitate >= width / 2)
    {
      outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }
    else if ((30 * unitate >= width / 2))
    {
      if (((i - *oy) / unitate) % 2 == 0)
        outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }
    else if ((70 * unitate >= width / 2))
    {
      if (((i - *oy) / unitate) % 8 == 0)
        outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }
    else if (((i - *oy) / unitate) % 20 == 0)
    {
      outtextxy(i, SUS + (JOS - SUS) / 2 + 8 + yoffset, buffer);
    }

    i -= unitate;
  }
  delete (oy);
}

char temp[256] = "";

double asimptota_orizontala()
{
  double c, a, b, k, l, ok = 0;
  int i, j, ok1 = 0;
  if (strchr(temp, '/') && !strchr(temp, 's') && !strchr(temp, 'c') && !strchr(temp, 'l') && !strchr(temp, 'r') && !strchr(temp, 't'))
  {
    for (i = 0; i <= strlen(temp) - 1; i++)
      if (temp[i] != '/')
      {
        if (temp[i] == 'x' && ok == 0)
        {
          if (temp[i + 1] == '^')
          {
            k = temp[i + 2] - '0';
            ok = 1;
          }
          else
          {
            k = 1;
            ok = 1;
          }
          if (temp[i - 1] == '*')
          {
            a = temp[i - 2] - '0';
          }
          else
            a = 1;
        }
      }
      else
        break;

    for (j = i + 1; j <= strlen(temp) - 1; j++)
      if (temp[j] == 'x' && ok1 == 0)
      {
        if (temp[j + 1] == '^')
        {
          l = temp[j + 2] - '0';
          ok1 = 1;
        }
        else
        {
          l = 1;
          ok1 = 1;
        }
        if (temp[j - 1] == '*')
          b = temp[j - 2] - '0';
        else
          b = 1;
      }
    if (k == l)
      c = a / b;
    else if (k < l)
      c = 0;
    else
      c = epsilon;
    if (c == floor(c))
      return c;
    else
      return infinit;
  }
}

double asimptota_verticala()
{
  double c, a = 0, b = 0;
  int i, j, ok1 = 0;
  if (strchr(temp, '/') && !strchr(temp, 's') && !strchr(temp, 'c') && !strchr(temp, 'l') && !strchr(temp, 'r') && !strchr(temp, 't'))
  {
    for (i = 0; i <= strlen(temp) - 1; i++)
      if (temp[i] == '/')
        break;
    for (j = strlen(temp) - 1; j >= i + 1; j--)
      if (isdigit(temp[j]) && temp[j - 1] != '^' && ok1 == 0)
      {
        if (temp[j - 1] == '-')
        {
          a = temp[j] - '0';
          a = -a;
          ok1++;
        }
        else
        {
          a = temp[j] - '0';
          ok1++;
        }
      }
      else if (temp[j] == 'x' && temp[j - 1] != '*' && ok1 == 0)
      {
        if (temp[j - 1] == '+')
        {
          a = 1;
          ok1++;
        }
        else if (temp[j - 1] == '-')
        {
          a = -1;
          ok1++;
        }
      }
      else if (isdigit(temp[j]) && temp[j - 1] != '^' && ok1 == 1)
      {
        if (temp[j - 1] == '-')
        {
          b = temp[j] - '0';
          b = -b;
          ok1++;
        }
        else
        {
          b = temp[j] - '0';
          ok1++;
        }
      }
      else if (temp[j] == 'x' && temp[j - 1] != '*' && ok1 == 1)
      {
        if (temp[j - 1] == '-')
        {
          b = -1;
          ok1++;
        }
        else
        {
          b = 1;
          ok1++;
        }
      }

    if (b != 0)
      c = a / b;
    else
      c = a;
    return c;
  }
}

double calculare_integrala_functie(double A, double B, double (*f)(double))
{
  if ((B - A) < epsilon)
    return (B - A) * ((*f)(A) + (*f)(B)) / 2.0;
  else
  {
    double punct = (A + B) / 2.0;
    return calculare_integrala_functie(A, punct, f) + calculare_integrala_functie(punct, B, f);
  }
}

void desenare_asimptote(double A, double B)
{

  double unitate1, punctmijloc1, punctmijloc;
  int SUS = 0, STG = 0, JOS = getmaxy(), DRP = getmaxx() - getmaxx() / 4;
  punctmijloc = (SUS + JOS) / 2;
  int c = asimptota_orizontala();

  c *= unitate;

  if (c != epsilon && c != infinit)
  {
    setcolor(GREEN);
    line(STG, punctmijloc - c + yoffset, DRP, punctmijloc - c + yoffset);
  }

  if (c != 0 || c == infinit)
  {
    unitate1 = (STG + DRP) / dim;
    punctmijloc1 = (STG + DRP) / 2;
    int a = asimptota_verticala();
    a = a * unitate;
    setcolor(BLUE);
    line(punctmijloc1 - a, SUS + yoffset, punctmijloc1 - a, JOS + yoffset);
  }
}

void copieFun(char *t)
{
  strcpy(fun, t);
  strcpy(temp, fun);
}
int gres[100];
int k = 0;
void evaluator()
{
  int nrpd = 0, nrpi = 0, gr = 0, i;
  k = 0;
  for (int i = 0; i < strlen(fun); i++)
  {
    if (fun[i] == '(')
      nrpd++;
    else if (fun[i] == ')')
      nrpi++;
    else if (fun[i] == '(' && fun[i + 1] == ')')
      gr = 1, gres[++k] = gr;

    else if (fun[i] == ')' && fun[i + 1] == '(')
      gr = 2, gres[++k] = gr;
    else if (fun[i] == '(' && fun[i + 1] == '+')
      gr = 3, gres[++k] = gr;
    else if (fun[i] == '(' && fun[i + 1] == '-')
      gr = 4, gres[++k] = gr;
    else if (fun[i] == '(' && fun[i + 1] == '*')
      gr = 5, gres[++k] = gr;
    else if (fun[i] == '(' && fun[i + 1] == '/')
      gr = 6, gres[++k] = gr;
    else if (fun[i] == '(' && fun[i + 1] == '^')
      gr = 7, gres[++k] = gr;
    else if (fun[i] == ')' && fun[i + 1] == 's')
      gr = 8, gres[++k] = gr;
    else if (fun[i] == ')' && fun[i + 1] == 'c')
      gr = 9, gres[++k] = gr;
    else if (fun[i] == ')' && fun[i + 1] == 't')
      gr = 10, gres[++k] = gr;
    else if (fun[i] == ')' && fun[i + 1] == 'l')
      gr = 11, gres[++k] = gr;
    else if (fun[i] == ')' && fun[i + 1] == 'e')
      gr = 12, gres[++k] = gr;
    else if (fun[i] == ')' && fun[i + 1] == 'r')
      gr = 13, gres[++k] = gr;
    else if (fun[i] == ')' && fun[i + 1] == 'x')
      gr = 14, gres[++k] = gr;
    else if (fun[i] == ')' && isdigit(fun[i + 1]))
      gr = 15, gres[++k] = gr;
    else if (fun[i] == '+' && fun[i + 1] == '+')
      gr = 16, gres[++k] = gr;
    else if (fun[i] == '+' && fun[i + 1] == '-')
      gr = 17, gres[++k] = gr;
    else if (fun[i] == '+' && fun[i + 1] == '*')
      gr = 18, gres[++k] = gr;
    else if (fun[i] == '+' && fun[i + 1] == '/')
      gr = 19, gres[++k] = gr;
    else if (fun[i] == '+' && fun[i + 1] == '^')
      gr = 20, gres[++k] = gr;
    else if (fun[i] == '-' && fun[i + 1] == '+')
      gr = 21, gres[++k] = gr;
    else if (fun[i] == '-' && fun[i + 1] == '-')
      gr = 22, gres[++k] = gr;
    else if (fun[i] == '-' && fun[i + 1] == '*')
      gr = 23, gres[++k] = gr;
    else if (fun[i] == '-' && fun[i + 1] == '/')
      gr = 24, gres[++k] = gr;
    else if (fun[i] == '-' && fun[i + 1] == '^')
      gr = 25, gres[++k] = gr;
    else if (fun[i] == '*' && fun[i + 1] == '+')
      gr = 26, gres[++k] = gr;
    else if (fun[i] == '*' && fun[i + 1] == '-')
      gr = 27, gres[++k] = gr;
    else if (fun[i] == '*' && fun[i + 1] == '*')
      gr = 28, gres[++k] = gr;
    else if (fun[i] == '*' && fun[i + 1] == '/')
      gr = 29, gres[++k] = gr;
    else if (fun[i] == '*' && fun[i + 1] == '^')
      gr = 30, gres[++k] = gr;
    else if (fun[i] == '/' && fun[i + 1] == '+')
      gr = 31, gres[++k] = gr;
    else if (fun[i] == '/' && fun[i + 1] == '-')
      gr = 32, gres[++k] = gr;
    else if (fun[i] == '/' && fun[i + 1] == '*')
      gr = 33, gres[++k] = gr;
    else if (fun[i] == '/' && fun[i + 1] == '/')
      gr = 34, gres[++k] = gr;
    else if (fun[i] == '/' && fun[i + 1] == '^')
      gr = 35, gres[++k] = gr;
    else if (fun[i] == '^' && fun[i + 1] == '+')
      gr = 36, gres[++k] = gr;
    else if (fun[i] == '^' && fun[i + 1] == '-')
      gr = 37, gres[++k] = gr;
    else if (fun[i] == '^' && fun[i + 1] == '*')
      gr = 38, gres[++k] = gr;
    else if (fun[i] == '^' && fun[i + 1] == '/')
      gr = 39, gres[++k] = gr;
    else if (fun[i] == '^' && fun[i + 1] == '^')
      gr = 40, gres[++k] = gr;
    else if (strchr("sctlre", fun[i]) && strchr("sclre", fun[i + 1]))
      gr = 41, gres[++k] = gr;
    else if (fun[i] == 's' && fun[i - 1] != 'o' && (fun[i + 1] != 'i' || fun[i + 2] != 'n'))
      gr = 42, gres[++k] = gr;
    else if (fun[i] == 'c')
    {
      if (fun[i + 1] == 'o' && fun[i + 2] != 's')
        gr = 43, gres[++k] = gr;
      else if (fun[i + 1] == 't' && fun[i + 2] != 'g')
        gr = 44, gres[++k] = gr;
    }
    else if (fun[i] == 't' && fun[i + 1] != 'g')
      gr = 46, gres[++k] = gr;
    else if (fun[i] == 'l' && fun[i + 1] != 'n')
      gr = 47, gres[++k] = gr;
    else if (fun[i] == 'r' && (fun[i + 1] != 'a' || fun[i + 2] != 'd'))
      gr = 48, gres[++k] = gr;
    else if (fun[i] == 'e' && (fun[i + 1] != 'x' || fun[i + 2] != 'p'))
      gr = 49, gres[++k] = gr;
    else if (strchr("+-*/^", fun[i]) && fun[i + 1] == ')')
      gr = 50, gres[++k] = gr;
  }
  if (strchr("+-*/^", fun[0]))
    gr = 51, gres[++k] = gr;
  if (strchr("+-*/^", fun[strlen(fun) - 1]))
    gr = 52, gres[++k] = gr;
  if (nrpd != nrpi)
    gr = 53, gres[++k] = gr;
  if (k == 0)
    gr = 54, gres[++k] = gr;
}
int kev;
void ev_interval(int width, int height, double A, double B, int limba, char *text)
{
  kev = 0;
  if (A >= B)
  {
    settextstyle(8, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, kev);
    setcolor(WHITE);
    if (limba == 0)
      strcpy(text, "Intervalul nu este bine ales");
    else
      strcpy(text, "The range is not well chosen");
    outtextxy(width / 2, height / 2 + 100 + kev, text);
    kev += 27;
  }
  else
  {
    settextstyle(8, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, kev);
    setcolor(WHITE);
    if (limba == 0)
      strcpy(text, "Intervalul este bine ales");
    else
      strcpy(text, "The range is well chosen");
    outtextxy(width / 2, height / 2 + 100 + kev, text);
    kev += 27;
  }
}

void mesaj_ev(int width, int height, int limba, char *text)
{
  settextstyle(8, HORIZ_DIR, 3);
  k = 0;
  evaluator();
  settextjustify(CENTER_TEXT, kev);
  setcolor(WHITE);
  for (int i = 1; i <= k; i++)
  {
    if (limba == 0)
    {
      if (gres[i] == 1)
      {
        strcpy(text, "Nu poate aparea o paranteza deschisa urmata de una inchisa");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 2)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de una deschisa");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 3)
      {
        strcpy(text, "Nu poate aparea o paranteza deschisa urmata de +");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 4)
      {
        strcpy(text, "Nu poate aparea o paranteza deschisa urmata de -");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 5)
      {
        strcpy(text, "Nu poate aparea o paranteza deschisa urmata de *");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 6)
      {
        strcpy(text, "Nu poate aparea o paranteza deschisa urmata de /");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 7)
      {
        strcpy(text, "Nu poate aparea o paranteza deschisa urmata de ^");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 8)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de functia sin");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 9)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de functia cos sau ctg");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 10)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de functia tg");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 11)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de functia logaritmica");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 12)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de functia exponentiala");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 13)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de functia radical");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 14)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de variabila x");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 15)
      {
        strcpy(text, "Nu poate aparea o paranteza inchisa urmata de o cifra");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 16)
      {
        strcpy(text, "Nu poate aparea simbolul + urmat de +");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 17)
      {
        strcpy(text, "Nu poate aparea simbolul + urmat de -");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 18)
      {
        strcpy(text, "Nu poate aparea simbolul + urmat de *");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 19)
      {
        strcpy(text, "Nu poate aparea simbolul + urmat de /");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 20)
      {
        strcpy(text, "Nu poate aparea simbolul + urmat de ^");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 21)
      {
        strcpy(text, "Nu poate aparea simbolul - urmat de +");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 22)
      {
        strcpy(text, "Nu poate aparea simbolul - urmat de -");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 23)
      {
        strcpy(text, "Nu poate aparea simbolul - urmat de *");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 24)
      {
        strcpy(text, "Nu poate aparea simbolul - urmat de /");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 25)
      {
        strcpy(text, "Nu poate aparea simbolul - urmat de ^");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 26)
      {
        strcpy(text, "Nu poate aparea simbolul * urmat de +");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 27)
      {
        strcpy(text, "Nu poate aparea simbolul * urmat de -");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 28)
      {
        strcpy(text, "Nu poate aparea simbolul * urmat de *");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 29)
      {
        strcpy(text, "Nu poate aparea simbolul * urmat de /");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 30)
      {
        strcpy(text, "Nu poate aparea simbolul * urmat de ^");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 31)
      {
        strcpy(text, "Nu poate aparea simbolul / urmat de +");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 32)
      {
        strcpy(text, "Nu poate aparea simbolul / urmat de -");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 33)
      {
        strcpy(text, "Nu poate aparea simbolul / urmat de *");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 34)
      {
        strcpy(text, "Nu poate aparea simbolul / urmat de /");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 35)
      {
        strcpy(text, "Nu poate aparea simbolul / urmat de ^");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 36)
      {
        strcpy(text, "Nu poate aparea simbolul ^ urmat de +");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 37)
      {
        strcpy(text, "Nu poate aparea simbolul ^ urmat de -");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 38)
      {
        strcpy(text, "Nu poate aparea simbolul ^ urmat de *");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 39)
      {
        strcpy(text, "Nu poate aparea simbolul ^ urmat de /");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 40)
      {
        strcpy(text, "Nu poate aparea simbolul ^ urmat de ^");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 41)
      {
        strcpy(text, "Nu se pot folosi functiile trigonometrice in acest mod");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 42)
      {
        strcpy(text, "Functia sin este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 43)
      {
        strcpy(text, "Functia cos este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 44)
      {
        strcpy(text, "Functia ctg este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 45)
      {
        strcpy(text, "Functia cos sau ctg este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 46)
      {
        strcpy(text, "Functia tg este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 47)
      {
        strcpy(text, "Functia ln este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 48)
      {
        strcpy(text, "Functia rad este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 49)
      {
        strcpy(text, "Functia exp este scrisa gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 50)
      {
        strcpy(text, "Nu puteti scrie operatorii langa paranteza inchisa");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 51)
      {
        strcpy(text, "Inceputul functiei este gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 52)
      {
        strcpy(text, "Sfarsitul functiei este gresit");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 53)
      {
        strcpy(text, "Numarul parantezelor deschise nu este egal cu numarul parantezelor inchise");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 54)
      {
        strcpy(text, "Functia este scrisa corect!:)");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
    }
    else
    {
      if (gres[i] == 1)
      {
        strcpy(text, "An open parenthesis followed by a closed one cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 2)
      {
        strcpy(text, "A closed parenthesis followed by an open one cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 3)
      {
        strcpy(text, "An open parenthesis followed by + cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 4)
      {
        strcpy(text, "An open parenthesis followed by - cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 5)
      {
        strcpy(text, "An open parenthesis followed by * cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 6)
      {
        strcpy(text, "An open parenthesis followed by / cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 7)
      {
        strcpy(text, "An open parenthesis followed by ^ cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 8)
      {
        strcpy(text, "A  ')' followed by the sin function cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 9)
      {
        strcpy(text, "A  ')' followed by the cos or cot function cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 10)
      {
        strcpy(text, "A ')' followed by the tangent function cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 11)
      {
        strcpy(text, "A ')' followed by the logarithmic function cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 12)
      {
        strcpy(text, "A ')' followed by the exponential function cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 13)
      {
        strcpy(text, "A ')' followed by the radical function cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 14)
      {
        strcpy(text, "A ')' followed by the constant x cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 15)
      {
        strcpy(text, "A ')' followed by a number cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 16)
      {
        strcpy(text, "The + symbol followed by the + symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 17)
      {
        strcpy(text, "The + symbol followed by the - symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 18)
      {
        strcpy(text, "The + symbol followed by the * symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 19)
      {
        strcpy(text, "The + symbol followed by the / symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 20)
      {
        strcpy(text, "The + symbol followed by the ^ symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 21)
      {
        strcpy(text, "The - symbol followed by the + symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 22)
      {
        strcpy(text, "The - symbol followed by the - symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 23)
      {
        strcpy(text, "The - symbol followed by the * symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 24)
      {
        strcpy(text, "The - symbol followed by the / symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 25)
      {
        strcpy(text, "The - symbol followed by the ^ symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 26)
      {
        strcpy(text, "The * symbol followed by the + symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 27)
      {
        strcpy(text, "The * symbol followed by the - symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 28)
      {
        strcpy(text, "The * symbol followed by the * symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 29)
      {
        strcpy(text, "The * symbol followed by the / symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 30)
      {
        strcpy(text, "The * symbol followed by the ^ symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 31)
      {
        strcpy(text, "The / symbol followed by the + symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 32)
      {
        strcpy(text, "The / symbol followed by the - symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 33)
      {
        strcpy(text, "The / symbol followed by the * symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 34)
      {
        strcpy(text, "The / symbol followed by the / symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 35)
      {
        strcpy(text, "The / symbol followed by the ^ symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 36)
      {
        strcpy(text, "The ^ symbol followed by the + symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 37)
      {
        strcpy(text, "The ^ symbol followed by the - symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 38)
      {
        strcpy(text, "The ^ symbol followed by the * symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 39)
      {
        strcpy(text, "The ^ symbol followed by the / symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 40)
      {
        strcpy(text, "The ^ symbol followed by the ^ symbol cannot appear");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 41)
      {
        strcpy(text, "Trigonometric functions cannot be used in this way");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 42)
      {
        strcpy(text, "The sin function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 43)
      {
        strcpy(text, "The cos function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 44)
      {
        strcpy(text, "The ctg function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 45)
      {
        strcpy(text, "The cos or ctg function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 46)
      {
        strcpy(text, "The tg function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 47)
      {
        strcpy(text, "The ln function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 48)
      {
        strcpy(text, "The rad function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 49)
      {
        strcpy(text, "The exp function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 50)
      {
        strcpy(text, "You cannot write operators next to the closing parenthesis");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 51)
      {
        strcpy(text, "The beginning of the function is not well written");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 52)
      {
        strcpy(text, "The end of the function is not written correctly");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 53)
      {
        strcpy(text, "The number of '(' does not coincide with the nr. of ')'");
        if (kev <= 135)
        {
          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
      else if (gres[i] == 54)
      {
        strcpy(text, "The function is written correctly!:)");
        if (kev <= 135)
        {

          outtextxy(width / 2, height / 2 + 100 + kev, text);
          kev += 27;
        }
      }
    }
  }
}