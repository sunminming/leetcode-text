#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
   int sum;
   int length, width, height;
   char s;
   scanf("%d", &sum);
   s = getchar();
   scanf("%d %d %d", &length, &width, &height);
   s = getchar();

   int blocks[sum + 1];
   memset(blocks, 0, (sum + 1) *sizeof(int));

   blocks[0] = 1;
   if(length < sum) blocks[length] = 1;
   else return 0;
   if(width < sum)
   {
      for(int i = length + 1; i < width; ++i)
      {
         blocks[i] = blocks[i - length];
      }
      blocks[width] = blocks[width - length] + 1;
   }
   else
   {
      for(int i = length + 1; i <= sum; ++i)
      {
         blocks[i] = blocks[i - length]; 
      } 
      return blocks[sum];
   }

   if(height < sum)
   {
      for(int i = width + 1; i < height; ++i)
      {
         blocks[i] = blocks[i - length] + blocks[i - width]; 
      } 
      blocks[height] = blocks[height - length] + blocks[height - width] + 1;
   }
   else
   {
      for(int i = width + 1; i <=sum; ++i)
      {
         blocks[i] = blocks[i - length] + blocks[i - width];
      } 
      return blocks[sum];
   }
   
   for(int i = height + 1; i <= sum; ++i)
   {
      blocks[i] = blocks[i - width] + blocks[i - length] + blocks[i - height]; 
   }

   /*
   for(int i = 0; i <= sum; ++i)
      printf("%d ", blocks[i]);
   printf("\n");
   */
   printf("%d\n", blocks[sum]);
}