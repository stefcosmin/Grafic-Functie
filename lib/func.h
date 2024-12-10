#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
char vect[256];
struct nod
{
  char inf;
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

void transformare_functie(char *fun)
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
      else if ('c' == fun[i])
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
  else if (strchr("sclt", a))
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

void afisarePostfixata()
{
  while (!esteVidaS(postfixata))
  {
    cout << postfixata->inf << " ";
    pop(postfixata);
  }
}