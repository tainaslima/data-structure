#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#define COLOR(pointer) (pointer == NULL? 'N' : pointer->color)*/

typedef struct _node
{
  int key;
  char color;
  struct _node * left;
  struct _node * right;
}node;

char COLOR(node *pointer)
{
  return pointer == NULL? 'N' : pointer->color;
}
void printPreOrder(node *root)
{
  if(root != NULL)
  {
    printf("%d %c\n", root->key, root->color);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}
node* rightRotation(node *root)
{
  node *left = root->left;

  root->left = left->right;
  left->right = root;
  left->color = root->color;
  root->color = 'R';
  root = left;
  return root;
}

node* leftRotation(node *root)
{
  node *right = root->right;

  root->right = right->left;
  right->left = root;
  right->color = root->color;
  root->color = 'R';
  root = right;
  return root;
}

node* changeColor(node *root)
{
  root->color = 'R';
  (root->left)->color = 'N';
  (root->right)->color = 'N';
  return root;
}

node * insert_LLRB(node *root, int x)
{
  if(root == NULL)
  {
    root = (node *) malloc (sizeof(node));
    if(!root)
    {
      printf("insertLLRB_: Não foi possível alocar memória.\n");
      exit(1);
    }
    root->key = x;
    root->left = root->right = NULL;
    root->color = 'R';
    return root;
  }

  if(x < root->key)
  {
    root->left = insert_LLRB(root->left, x);
  }
  else
  {
    root->right = insert_LLRB(root->right, x);
  }

  if((COLOR(root->left) == 'N') && (COLOR(root->right) == 'R'))
  {
    root = leftRotation(root);
  }

  if((COLOR(root->left) == 'R') && (COLOR((root->left)->left) == 'R'))
  {
    root = rightRotation(root);
  }
  if((COLOR(root->left) == 'R') && (COLOR(root->right) == 'R'))
  {
    root = changeColor(root);
  }

  return root;
}

node* insertLLRB(node *root, int x)
{
  root = insert_LLRB(root, x);
  return root;
}

int main ()
{
  int newKey = 0;
  node *root = NULL;

  while(scanf("%d\n", &newKey) != EOF)
  {
    do{}while(getchar() != '\n');
    root = insertLLRB(root, newKey);
    root->color = 'N';
  }
  /*while(newKey != -1)
  {
    printf("Digite a chave a ser inserida ou -1 para sair:\n");
    scanf("%d", &newKey);
    if(newKey == -1)
    {
      break;
    }
    root = insertLLRB(root, newKey);
    root->color = 'N';
  }
  /*printf("sai do while %d\n", root->key);*/
  printPreOrder(root);
  return 0;
}
