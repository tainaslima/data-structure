#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 50

void pushInt(int *pilha, int *topo, int x)
{
  if(*topo >= TAM)
  {
    printf("O tamanho da pilha foi ultrapassado.\n");
    exit(1);
  }
  pilha[*topo] = x;
  (*topo)++;

}

void pushChar(char *pilha, int *topo, char x)
{
  if(*topo >= TAM)
  {
    printf("O tamanho da pilha foi ultrapassado.\n");
    exit(1);
  }
  pilha[*topo] = x;
  (*topo)++;

}

int pop(int *topo)
{
  if(*topo == 0)
  {
    return 0;
  }
  else
  {
    (*topo)--;
    return 1;
  }
}
int fazOperacao(int a, int b, char op)
{
  if (op == '+')
  {
    return a+b;
  }
  else if (op == '-')
  {
    return a-b;
  }
  else if (op == '*')
  {
    return a*b;
  }
  else if (op == '/')
  {
    return b == 0? 0 : a/b;
  }
  printf("Operação inválida\n");
  return -1;
}
int ehNumero (char a)
{
  return a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9'? 1:0;
}
void calculaExp(char *expr, int *pOperand, int *tOperand, char *pOperad, int *tOperad)
{
  int i = 0, k;
  int result;
  char *numeroChar;
  char *digitoChar = (char *) malloc (sizeof(char));
  while(i <= strlen(expr))
  {
    numeroChar = (char *) malloc (sizeof(char)*TAM);

    if((expr[i] != '(') && (expr[i] != ')') )
    {
      if(ehNumero(expr[i]) == 1)
      {
        k = i+1;
        *numeroChar = expr[i];
        while(ehNumero(expr[k]) == 1)
        {
           *digitoChar = expr[k];
            numeroChar = strcat(numeroChar,digitoChar);
            k++;
        }
        pushInt(pOperand, tOperand, atoi(numeroChar));
        i = k;
      }
      else
      {
        pushChar(pOperad, tOperad, expr[i]);
        i++;
      }
    }
    else if (expr[i] == ')')
    {
      if ((*tOperand >= 2) && (*tOperad >= 1))
      {
          result = fazOperacao(pOperand[*tOperand-2], pOperand[*tOperand-1], pOperad[*tOperad-1]);
          pop(tOperand);
          pop(tOperand);
          pop(tOperad);
          pushInt(pOperand, tOperand, result);
      }
      i++;
    }
    else if(expr[i] == '(')
    {
          i++;
    }

    free(numeroChar);
  }
  free(digitoChar);
}

int main()
{
  char *expr = (char *) malloc (sizeof(char)*TAM);

  int *pOperand = (int *) malloc (sizeof(int)*TAM);
  int *tOperand = (int *) malloc (sizeof(int));

  char *pOperad = (char *) malloc (sizeof(char)*TAM);
  int *tOperad = (int *) malloc (sizeof(int));

  if(!expr || !pOperand || !pOperad || !tOperand || !tOperad)
  {
    return 1;
  }

  *tOperand = 0;
  *tOperad = 0;

  scanf("%s", expr);

  calculaExp(expr, pOperand, tOperand, pOperad, tOperad);

  printf("%d\n", pOperand[*tOperand-1]);

  free(expr);
  free(pOperand);
  free(pOperad);
  free(tOperand);
  free(tOperad);

  return 0;
}
