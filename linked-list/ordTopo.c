#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMDIG 4

typedef struct _no
{
  int num;
  struct _no * prox;
}no;

void initVetorChar(char * vetor, int tamanho)
{
  int i;
  for(i = 0; i < tamanho; i++)
  {
    vetor[i] = '\0';
  }
}
void zeraVetor(int * vetor, int tamanho)
{
  int i = 0;

  for(i = 0; i < tamanho; i++)
  {
    vetor[i] = 0;
  }
}

void bubbleSort (no * vetor, int tamanho)
{
  int i, j;
  no temp;

  for(i = 0; i < tamanho-1; i++)
  {
    for(j = 0; j < tamanho-i-1; j++)
    {
      if(vetor[j].num > vetor[j+1].num)
      {
        temp = vetor[j];
        vetor[j] = vetor[j+1];
        vetor[j+1] = temp;
      }
    }
  }
}
int tamanhoDaLista(no * lista)
{
    int tamanho = 0;

    while (lista != NULL)
    {
      tamanho++;
      lista = lista->prox;
    }

    return tamanho;
}

void printGrafo(no ** grafo, int numVertices)
{
  int i, j = 1;
  no *verticeI;
  printf("-------------- GRAFO ----------------\n");
  for(i = 0; i < numVertices; i++)
  {
    verticeI = grafo[i];
    printf("Vertice %d:\n", i+1);
    if(verticeI == NULL)
    {
      printf("Esse vértice não possui adjacentes.\n");
    }
    while(verticeI != NULL)
    {
      printf("  Adjacente %d: %d\n", j,verticeI->num);
      verticeI = verticeI->prox;
      j++;
    }
    j = 1;
  }
}
no* ordenaAdjDoNo (no * adjsDoNo)
{
  int i, tamanho = 0;
  no * nos = adjsDoNo , * nos2 = NULL, *aux;
  no * adjVetor;

  tamanho = tamanhoDaLista(nos);
  nos = adjsDoNo;
  adjVetor = (no *) malloc (tamanho * sizeof(no));

  if(!adjVetor)
  {
    printf("ordenaAdjDoNo: Não pode alocar memória.\n");
    exit(1);
  }

  for(i = 0; i < tamanho; i++)
  {
    adjVetor[i] = *nos;
    nos = nos->prox;

  }

  bubbleSort(adjVetor, tamanho);

  for(i = tamanho-1; i >= 0; i--)
  {
    aux = (no *) malloc (sizeof(no*));
    aux->num = adjVetor[i].num;
    aux->prox = nos2;
    nos2 = aux;
  }

 return nos2;
}
no* preencheAdjDoNo(char * vertices, int * grauDosVertices)
{
  int j = 0,k = 0, numeroInt;
  no* aux, * linha = NULL;
  char * numeroStr = (char *) malloc (sizeof(char) * TAMDIG);
  char * temp = (char *) malloc (sizeof(char));

  if(!numeroStr || !temp)
  {
    printf("preencheAdjDoNo: Não pode alocar memória.\n");
    exit(1);
  }

  if(strlen(vertices) > 1)
  {
    while(vertices[j] != '\0')
    {
      k = 0;
      aux = (no *) malloc (sizeof(no));
      if(!aux)
      {
        printf("preencheAdjDoNo: Não pode alocar memória.\n");
        exit(1);
      }

      while((vertices[j+k] != ' ') && (vertices[j+k] != '\n') && (j+k < strlen(vertices)))
      {
        temp[0] = vertices[j+k];
        numeroStr = strcat(numeroStr, temp);
        k++;
      }
      numeroInt = atoi(numeroStr);
      aux->num = numeroInt;
      aux->prox = linha;
      linha = aux;

      grauDosVertices[numeroInt-1]++;

      free(numeroStr);
      numeroStr = (char *) malloc (sizeof(char) * TAMDIG);
      j+=k+1;
    }
    return linha;
  }
  else
  {
    return NULL;
  }

}

int verificaGraus(int * grau, int tamanho)
{
  int i = 0;

  for(i = 0; i < tamanho; i++)
  {
    if(grau[i] != -2)
    {
      return 0;
    }
  }
  return 1;
}

int * ordenacaoTopologica(no ** grafo, int * grau, int tamanho)
{
  int * verticesOrdenados = (int * ) malloc (sizeof(int)*tamanho);
  int i, j, pos = 0, inicio = 0;
  no *adjVertice;

  if(!verticesOrdenados)
  {
    printf("ordenacaoTopologica: Não pode alocar memória.\n");
    exit(1);
  }

  zeraVetor(verticesOrdenados, tamanho);
  while(!verificaGraus(grau, tamanho))
  {
    for (i = 0; i < tamanho; i++)
    {
      if(grau[i] == 0)
      {
        verticesOrdenados[pos] = i+1;
        pos++;
        grau[i] = -2;
      }
    }

    for(j = inicio; verticesOrdenados[j] != 0 && j < tamanho; j++)
    {
      adjVertice = grafo[verticesOrdenados[j]-1];

      while(adjVertice != NULL)
      {
        grau[adjVertice->num -1]--;
        adjVertice = adjVertice->prox;
      }
    }
    inicio = j;
  }

  return verticesOrdenados;
}
int main()
{
  int numVertices;
  char * vertices;

  no ** grafo;
  int * grau, * verticesOrdenados = NULL;

  int i = 1;

  printf("------------------- ORDENAÇÃO TOPOLÓGICA -------------------\n");
  printf("\nLeitura do grafo...\n\n");
  printf("Forneça o número de vértices do seu grafo:\n");
  scanf("%d", &numVertices);
  getchar();

  grafo = (no **) malloc (sizeof(no)*numVertices);
  grau = (int *) malloc (sizeof(int)*numVertices);
  vertices = (char *) malloc (sizeof(char*) * 2*numVertices+1);

  if(!grafo || !vertices || !grau)
  {
    printf("Main: Não pode alocar memória\n");
    exit(1);
  }

  zeraVetor(grau, numVertices);
  initVetorChar(vertices, 2*numVertices+1);

  while(i <= numVertices)
  {
    printf("----------------------------\n");
    printf("Forneça os adjacentes do vértice %d (separados por espaço e caso não tenha dê ENTER):\n", i);
    fgets(vertices, 2*numVertices+1, stdin);
    grafo[i-1] = preencheAdjDoNo(vertices, grau);
    grafo[i-1] = ordenaAdjDoNo(grafo[i-1]);
    i++;
  }

  /*printGrafo(grafo, numVertices);*/
  printf("\nFazendo a ordenação...\n\n");
  verticesOrdenados = ordenacaoTopologica(grafo, grau, numVertices);

  if(verticesOrdenados)
  {
    printf("Vértices ordenados:");
    for(i = 0; i < numVertices; i++)
    {
      printf("%d ", verticesOrdenados[i]);
    }
    printf("\n");
  }
  else{
    printf("Deu ruim!\n");
  }


  for(i = 0; i < numVertices; i++)
  {
    free(grafo[i]);
  }
  free(grafo);
  free(vertices);

  return 0;
}
