#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dijkstra(int *map, int src, int *dist, int *relay)
{
   int visit[6];
   int min_dist = 100;
   int temp_relay;
   memset(visit, 0, sizeof(int) * 6);
   visit[src] = 1;
   for(int i  = 0; i < 6; ++i)
   {
      dist[i] = map[src * 6 + i];
   }

   for(int c = 0; c < 6; ++c)
   {
      min_dist = 100;
      for(int r = 0; r < 6; ++r)//the closer node
      {
         if(dist[r] < min_dist && visit[r] == 0)
         {
            min_dist = dist[r];
            temp_relay = r;
         }
      }
      visit[temp_relay] = 1;
      for(int n = 0; n < 6; ++n)
      {
         if(dist[n] > min_dist + map[temp_relay * 6 + n])
         {
            dist[n] = min_dist + map[temp_relay * 6 + n];
            relay[n] = temp_relay;
         }
      }
   }
}

int main(int argc, char **argv)
{
   int map[6][6];
   int relay[6];
   char src, dst, s;
   int dist[6];

   for(int i = 0; i < 6; ++i)
   {
      for(int j = 0; j < 6; ++j)
      {
         if(i == j) map[i][j] = 0;
         else map[i][j] = 100;
      }
   }
   //memset(relay, 0, sizeof(int) * 6);
   
   map[0][1] = 12;//A->B
   map[1][0] = 12;
   map[2][3] = 3;//C->D
   map[3][2] = 3;
   map[1][2] = 10;//B->C
   map[2][1] = 10;
   map[3][4] = 4;//D->E
   map[4][3] = 4;
   map[2][5] = 6;//C->F
   map[5][2] = 6;
   map[5][0] = 16;//F->A
   map[0][5] = 16;
   map[4][5] = 2;//E->F
   map[5][4] = 2;
   map[1][5] = 7;//B->F
   map[5][1] = 7;
   map[2][4] = 5;//C->E
   map[4][2] = 5;
   
   scanf("%c %c", &src, &dst);
   s = getchar();
   for(int i = 0; i < 6; ++i) relay[i] = src - 'A';
   dijkstra(map, src - 'A', dist, relay);

   printf("%d", dist[dst - 'A']);
   printf("\n");   
   /*
   for(int i = 0; i < 6; ++i)
   {
      printf("%c ", relay[i] + 'A');
   }
   */
   int res_path[6];
   memset(res_path, 0, 6 * sizeof(int));
   int _dst = dst - 'A';
   int n = 0;
   while(_dst != (src - 'A'))
   {
      res_path[n] = _dst;
      _dst = relay[_dst];
      ++n;
   }
   //for(int i = 0; i < n; ++i) printf("%c ", res_path[i] + 'A');
   --n;
   printf("%c ", src);
   for(; n >= 0; --n) printf("%c ", res_path[n] + 'A');
   printf("\n");
}