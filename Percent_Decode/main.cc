#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

void s_top(stack<char> &s_str)
{
   while(1)
   { 
      char tops[3];
      tops[3] = '\0';
      tops[0] = s_str.top();
      if((tops[0] >= '0') && (tops[0] <= '7'))
      {
         s_str.pop();
         tops[1] = s_str.top();
         if(((tops[1] >= 'A') && (tops[1] <= 'F')) || ((tops[1] >= '0') && (tops[1] <= '9'))|| ((tops[1] >= 'a') && (tops[1] <= 'f')))
         {
            s_str.pop(); 
            char c;
            sscanf(tops, "%x", &c);
            if(c != '%')
            { 
               s_str.push(c);
               return;
            }
         }
         else
         {
            s_str.push(tops[1]);
            s_str.push(tops[0]);
            return;
         }
      }
      else
      {
         s_str.push(tops[0]);
         return;
      }
   }
}

void decode()
{
   stack<char> s_str;
   char str[100000];
   memset(str, 0, 100000);
   scanf("%s", str);
   s_str.push(str[strlen(str) - 1]);
   s_str.push(str[strlen(str) - 2]);
   for(int i = strlen(str) - 3; i >= 0; --i)
   {
      if(str[i] == '%' && s_str.size() >= 2) s_top(s_str);
      else s_str.push(str[i]);
   }
   
   while(!s_str.empty())
   {
      printf("%c", s_str.top());
      s_str.pop(); 
   }
   printf("\n");
}

int main(int argc, char **argv)
{
   int num;
   scanf("%d", &num);
   while(num-- > 0) decode();
}