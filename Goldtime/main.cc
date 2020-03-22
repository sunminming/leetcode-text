#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main(int argc, char **argv)
{
   int size, cur_sum, res;
   char s;
   scanf("%d", &size);
   s = getchar();
   int nums[size];
   for(int i = 0; i < size; ++i)
   {
      scanf("%d", &nums[i]);
      s = getchar(); 
   }
   
   cur_sum = nums[0];
   res = cur_sum;
   for(int i = 1; i < size; ++i)
   {
      cur_sum = min(cur_sum + nums[i], nums[i]);
      res = min(res, cur_sum);
   }
   printf("%d\n", res);
   return 0;
}