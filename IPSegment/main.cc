#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

struct seg
{
   unsigned int begin;
   unsigned int end;
};

bool segcmp(struct seg &seg1, struct seg &seg2)
{
   return seg1.begin < seg2.begin;
}

int main(int argc, char **argv)
{
   int seg_n;
   char s;
   scanf("%d", &seg_n);
   s = getchar();

   struct seg *segs;
   segs = (struct seg *)malloc(seg_n * 2 * sizeof(unsigned int));
   memset(segs, 0, seg_n * 2 * sizeof(unsigned int));
   for(int i = 0; i < seg_n; ++i)
   {
      scanf("%d %d", &segs[i].begin, &segs[i].end);
      s = getchar();
   }

   sort(segs, segs + seg_n, segcmp);

   struct seg temp = segs[0];
   for(int index = 1; index < seg_n; ++index)
   {
      if(temp.end < segs[index].begin)
      {
         printf("%d %d\n", temp.begin, temp.end);
         temp = segs[index];
      }
      else
      {
         temp.end = max(segs[index].end, temp.end);
      }
   }
   printf("%d %d\n", temp.begin, temp.end);
}