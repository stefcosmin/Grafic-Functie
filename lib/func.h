#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <winbgim.h>
#include <string.h>
#include <cmath>
#include <climits>
#define pi 3.141592
#define e 2.718281
#define epsilon 0.000001
using namespace std;
char fun[256];
char vect[256];
int v[50];
double MINI, MAXI, minim, maxim;
double dim;
int unitate, midy, midx;
int STG = 0, DRP = 960, SUS = 200, JOS = 520;

void GraphBorder(double A, double B)
{

  dim = B - A;
  int i;
  unitate = (DRP - STG) / dim;

  midx = getmaxx() / 2;
  midy = getmaxy() / 2;
  DRP = getmaxx() - getmaxx() / 4;
  SUS = midy - abs(MAXI) * unitate;
  STG = 0;
  JOS = midy + abs(MINI) * unitate;
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
  int SUS = 0, STG = 0, JOS = getmaxy(), DRP = getmaxx() - getmaxx() / 4;
  setcolor(BLACK);

  line(STG - A * unitate, SUS, STG - A * unitate, JOS); // OY
  // sagetile OY
  line(STG - A * unitate - 2, SUS + 2, STG - A * unitate, SUS);
  line(STG - A * unitate + 2, SUS + 2, STG - A * unitate, SUS);
  int i;
  i = midy;
  while (i <= JOS)
    line(STG - A * unitate - 2, i, STG - A * unitate + 2, i), i += unitate;
  i = midy;
  while (i >= SUS)
    line(STG - A * unitate - 2, i, STG - A * unitate + 2, i), i -= unitate;
  // final oy

  line(STG, SUS + (JOS - SUS) / 2, DRP, SUS + (JOS - SUS) / 2); // OX
  // sagetile OX
  line(DRP - 2, SUS + (JOS - SUS) / 2 - 2, DRP, SUS + (JOS - SUS) / 2);
  line(DRP - 2, SUS + (JOS - SUS) / 2 + 2, DRP, SUS + (JOS - SUS) / 2);
  dim = B - A;
  unitate = (DRP - STG) / dim;
  for (int i = STG + unitate; i <= DRP; i += unitate)
  {
    line(i, SUS + (JOS - SUS) / 2 - 2, i, SUS + (JOS - SUS) / 2 + 2);
  }
}

void copieFun(char *t)
{
  strcpy(fun, t);
}
