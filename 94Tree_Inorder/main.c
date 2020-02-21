#include <stdlib.h>
#include <stdio.h>

 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

int main(int argc, char **argv){
   char val, s;
   scanf("%c", &val);
   while(1)
   {
      if(val == '?') printf("?");
      else
      {
          
      }
      
      s = getchar();
      scanf("%c", &val);
   }
}