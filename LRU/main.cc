#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <iterator>
#include <iostream>
using namespace std;

struct node
{
   int key;
   int val;
   struct node *pre;
   struct node *post;
};

void get_mem(unordered_map<int, struct node *> &mem_index, struct node *head, int key)
{
   unordered_map<int, struct node *>::iterator target;
   if((target = mem_index.find(key)) != mem_index.end())
   {
      printf("%d\n", target->second->val);
      //move target from link
      struct node *pre = target->second->pre;
      struct node *post = target->second->post;
      pre->post = target->second->post;//pre`s post = target`s post
      post->pre = target->second->pre;//post`s pre = target`s pre
      //insert target after head
      target->second->post = head->post;
      target->second->pre = head;
      head->post->pre = target->second;
      head->post = target->second;
   }
   else
   {
      printf("%d\n", -1);
   }
   return;
}

void del_mem(unordered_map<int, struct node *> &mem_index, struct node *tail)
{
   struct node *target = tail->pre;
   tail->pre = target->pre;
   target->pre->post = tail;
   mem_index.erase(target->key);
   /*
   for(unordered_map<int, struct node *>::iterator it = mem_index.begin(); it != mem_index.end(); ++it)
   {
      if(it->second == target)
      {
         mem_index.erase(it);
         break; 
      } 
   }
   */
   free(target);
}

void updata_mem(unordered_map<int, struct node *> &mem_index, struct node *head, 
               unordered_map<int, struct node *>::iterator it, int val)
{
   struct node *target = it->second;
   target->val = val;
   
   struct node *pre = target->pre;
   struct node *post = target->post;
   pre->post = target->post;//pre`s post = target`s post
   post->pre = target->pre;//post`s pre = target`s pre
   target->post = head->post;
   target->pre = head;
   head->post->pre = target;
   head->post = target;
}

void set_mem(unordered_map<int, struct node *> &mem_index, struct node *head, 
            int key, int val)
{
   struct node *new_mem = (struct node *)malloc(sizeof(struct node *));
   new_mem->key = key;
   new_mem->val = val;
   //insert new_mem after head
   new_mem->post = head->post;
   new_mem->pre = head;
   head->post->pre = new_mem;
   head->post = new_mem;

   mem_index.insert({key, new_mem});
}

int main(int argc, char **argv)
{
   unordered_map<int, struct node *> mem_index;
   struct node *head, *tail;
   int cap, operat_n;
   char s;
   cin >> cap >> operat_n;

   head = new node();
   head->val = -1;
   head->pre = NULL;
   head->post = NULL;

   tail = new node();
   tail->val = -1;
   tail->pre = head;
   tail->post = NULL;
   head->post = tail;
   for(int n = 0; n < operat_n; ++n)
   {
      char operat;
      int key, val;
      cin >> operat;
      if(operat == 'g')//get
      {
         cin >> key;
         get_mem(mem_index, head, key);
      } 
      else//set
      {
         cin >> key >> val;
         unordered_map<int, struct node *>::iterator it = mem_index.find(key);
         if(it != mem_index.end()) updata_mem(mem_index, head, it, val);
         else
         {
            if(mem_index.size() < cap) set_mem(mem_index, head, key, val);
            else
            {
               del_mem(mem_index, tail);
               set_mem(mem_index, head, key, val);
            }
         }    
      }
      /*
      struct node *it = head->post;
      while(it != tail)
      {
          printf("%d ", it->val);
          it = it->post;
      }
      */
   }
   return 0;
}