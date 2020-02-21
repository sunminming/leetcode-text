#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

struct tree_node
{
   int val;
   struct tree_node *lchild;
   struct tree_node *rchild; 
};

void preorder(struct tree_node *root)
{
   stack<struct tree_node *> s;
   s.push(root);
   while(!s.empty())
   {
      struct tree_node *node = s.top();
      s.pop();
      if(node != NULL) 
      {
         printf("%d\n", node->val);
         s.push(node->rchild);
         s.push(node->lchild);
      }
      else printf("#\n");
   }
}

int main(int argc, char **argv)
{
   int node_n;
   char s;
   string val;
   scanf("%d", &node_n);
   s = getchar();
   if(node_n == 0)
   {
      printf("#\n");
      return 0;
   }
   
   vector<string> node_sval;
   for(int i = 0; i < node_n; ++i)
   {
      cin >> val;
      node_sval.push_back(val);
   }

   queue<struct tree_node *> nodes;
   
   struct tree_node *root = (struct tree_node *)malloc(sizeof(struct tree_node));
   root->val = stoi(node_sval[0]);
   root->lchild = NULL;
   root->rchild = NULL;
   nodes.push(root);
   int index = 1;
   
   while(index < node_n && nodes.size() != 0)
   {
      struct tree_node *head = nodes.front();
      nodes.pop();
      val = node_sval[index];
      if(val[0] != '#')
      {
         struct tree_node *node = (struct tree_node *)malloc(sizeof(struct tree_node));
         node->val = stoi(val);
         node->lchild = NULL;
         node->rchild = NULL;
         head->lchild = node;
         nodes.push(node);
      }
      ++index;
      if(index >= node_n) break;

      val = node_sval[index];
      if(val[0] != '#')
      {
         struct tree_node *node = (struct tree_node *)malloc(sizeof(struct tree_node));
         node->val = stoi(val);
         node->lchild = NULL;
         node->rchild = NULL;
         head->rchild = node;
         nodes.push(node);
      }
      ++index;
      ++head;
   }

   /*
   for(int i = 0; i < tail; ++i)
   {
      printf("%d ", nodes[i]->val);//, nodes[i]->lchild->val, nodes[i]->rchild->val);
      if(nodes[i]->lchild) printf("%d ", nodes[i]->lchild->val);
      if(nodes[i]->rchild) printf("%d ", nodes[i]->rchild->val);
      printf("\n");
   }
   */
   preorder(root);
   return 0;
}