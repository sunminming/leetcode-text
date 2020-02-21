#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct ListNode {
   int val;
   struct ListNode *next;
};

struct ListNode *reverseBetween(struct ListNode *head, int m, int n){
   
   int cycls = n - m;
   if(cycls == 0) return head;
   struct ListNode *p, *q, *j, *h;
   h = malloc(sizeof(struct ListNode));
   h->val = -1;
   h->next = head;
   head = h;
   int i = 0;
   while(i < m - 1)
   {
      h = h->next;
      ++i;
   }
   p = h->next;
   j = p->next;
   q = j->next;
   if(cycls == 1)
   {
      h->next = j;
      p->next = q;
      j->next = p;
      return head->next;
   }
   if(q->next == NULL)
   {
      h->next = q;
      q->next = j;
      j->next = p;
      p->next = NULL;
      return head->next;
   }
   
   i = 0;
   while(i < cycls && q)
   {
      j->next = p;
      p = j;
      j = q;
      q = q->next;
      ++i;
   }
   
   //j->next = p;
   if(i < cycls)
   {
      j->next = p;
      h->next->next =NULL;
      h->next = j;
      return head->next;
   }
   h->next->next = j;
   h->next = p;
   return head->next;
}

int main(){
   struct ListNode *head = malloc(sizeof(struct ListNode));
   head->val = 0;
   head->next = NULL;
   struct ListNode *q = head;
   char s = ' ';
   for(int i = 0; s != '\n'; ++i)
   {   
      int val; 
      scanf("%d", &val);
      s = getchar();
      struct ListNode *p = malloc(sizeof(struct ListNode));
      p->val = val;
      q->next = p;
      q = q->next;
   } 
   
   int m, n;
   scanf("%d %d", &m, &n);
   struct ListNode *p = reverseBetween(head->next, m, n);
   while(p)
   {
      printf("%d ", p->val);
      p = p->next;
   }
   printf("\n");
}
