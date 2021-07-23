#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
struct BST
{
  long long int key;
  struct BST *left, *right, *parent;
};

struct List
{
  struct BST *node;
  struct List *next;
};

struct BST *
newNode (long long int key)
{
  struct BST *temp = (struct BST *) malloc (sizeof (struct BST));
  temp->key = key;
  temp->left = temp->right = temp->parent = NULL;
  return temp;
}

void
Inorder (struct BST *node)
{
  if (node)
    {
      Inorder (node->left);
      printf ("%lld  ", node->key);
      Inorder (node->right);
    }
}

struct BST *
Search (struct BST *node, long long int X)
{

  while (node)
    {
      if (X == node->key)
	return node;
      else if (X < node->key)
	node = node->left;
      else
	node = node->right;
    }
  return NULL;
}


void
Insert (struct BST **node, long long int key)
{
  // If the BST is empty, create a  new BST
  if (!*node)
    *node = newNode (key);

  else
    {
      bool flag = true;
      struct BST *temp = *node;

      while (flag)
	{
	  if (key < temp->key)

	    if (temp->left)
	      temp = temp->left;
	    else
	      {
		temp->left = newNode (key);
		temp->left->parent = temp;
		flag = false;
	      }
	  else if (key > temp->key)
	    {
	      if (temp->right)
		temp = temp->right;
	      else
		{
		  temp->right = newNode (key);
		  temp->right->parent = temp;
		  flag = false;
		}

	    }
	  else
	    flag = false;

	}			// end of while loop

    }				//end of else
}				//end of Insert

void
DeleteNode (struct BST **root, struct BST *node)
{
  if (node->left && node->right)
    {
      struct BST *temp = node->left;
      while (temp->right)
	temp = temp->right;
      node->key = temp->key;
      node = temp;
    }

  struct BST *child, *p = node->parent;
  if (node->left)
    child = node->left;
  else
    child = node->right;
  if (*root == node)
    *root = child;
  if (child)
    child->parent = p;
  if (p)
    if (p->left == node)
      p->left = child;
    else
      p->right = child;
  free (node);

}

void
Delete (struct BST **root, long long int X)
{
  struct BST *node = *root;
  while (node)
    {
      if (X == node->key)
	DeleteNode (&*root, node);
      else if (X < node->key)
	node = node->left;
      else
	node = node->right;
    }
}

long long int
Rangecount (struct BST *node, long long int l, long long r)
{

  if (!node)
    return 0;

  if (node->key > r)
    return Rangecount (node->left, l, r);

  if (node->key < l)
    return Rangecount (node->right, l, r);


  return 1 + Rangecount (node->left, l, r) + Rangecount (node->right, l, r);


}


void
Rangelist (struct BST *node, long long int l, long long r, struct List **list)
{

  if (node)
    {

      if (node->key > r)
	Rangelist (node->left, l, r, &*list);

      else if (node->key < l)
	Rangelist (node->right, l, r, &*list);


      else
	{
	  Rangelist (node->right, l, r, &*list);
	  struct List *temp = (struct List *) malloc (sizeof (struct List));
	  temp->node = node;
	  temp->next = *list;
	  *list = temp;

	  Rangelist (node->left, l, r, &*list);
	}

    }

}

struct BST *
LCA (struct BST *node, struct BST *l, struct BST *r)
{
  if (!node || l->key > r->key)
    return NULL;

  // If r smaller than root, then LCA lies in left 
  if (node->key > r->key)
    return LCA (node->left, l, r);

  // If l greater than root, then LCA lies in right 
  if (node->key < l->key)
    return LCA (node->right, l, r);

  return node;
}

struct BST *
Successor (struct BST *node)
{
  if (!node)
    return node;
  if (node->right)
    {
      node = node->right;
      while (node->left)
	node = node->left;
      return node;
    }
  else
    {

      while (node->parent)
	{
	  if (node->parent->left == node)
	    return node->parent;
	  else
	    node = node->parent;
	}

      return node->parent;
    }
}

struct BST *
Predecessor (struct BST *node)
{
  if (!node)
    return node;
  if (node->left)
    {
      node = node->left;
      while (node->right)
	node = node->right;
      return node;
    }
  else
    {
      while (node->parent)
	{
	  if (node->parent->right == node)
	    return node->parent;
	  else
	    node = node->parent;
	}

      return node->parent;
    }
}

struct BST *
CreateBBST (long long int A[], long long int l, long long int r)
{
  struct BST *node = NULL;
  if (l <= r)
    {

      long long int m = (l + r) / 2;
      node = (struct BST *) malloc (sizeof (struct BST));
      node->key = A[m];

      node->left = CreateBBST (A, l, m - 1);

      node->right = CreateBBST (A, m + 1, r);
      if (node->right)
	node->right->parent = node;
      if (node->left)
	node->left->parent = node;
    }

  return node;
}

void
main ()
{
  long long int i, n = 20000, A[100000], l, r, c;
  struct BST *root = NULL;
  struct List *list;
  A[0] = 5314;
  for (i = 1; i < n; ++i)
    A[i] = rand () % 10 + 1 + A[i - 1];
  root = CreateBBST (A, 0, n - 1);
  Insert (&root, 13);
  Insert (&root, 452);
   Insert (&root, 7653);
}



