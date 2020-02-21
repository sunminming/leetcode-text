#include <algorithm>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Flow
{
   char *src_ip;
   char *dest_ip;

   int src_port;
   int dest_port;

   Flow()
   {
      src_ip = (char *)malloc(16);
      memset(src_ip, '\0', 16);
      dest_ip = (char *)malloc(16);
      memset(dest_ip, '\0', 16);
      src_port = 0;
      dest_port = 0;
   }

   Flow(char *_src_ip, char *_dest_ip, int _src_port, int _dest_port)
   {
      src_ip = (char *)malloc(strlen(_src_ip) + 1);
      memset(src_ip, '\0', strlen(_src_ip) + 1);
      strcpy(src_ip, _src_ip);
      dest_ip = (char *)malloc(strlen(_dest_ip) + 1);
      memset(dest_ip, '\0', strlen(_dest_ip) + 1);
      strcpy(dest_ip, _dest_ip);

      src_port = _src_port;
      dest_port = _dest_port;
   }

   bool operator==(const Flow &that)const
   {
      return (strcmp(src_ip, that.src_ip) == 0) 
          && (strcmp(dest_ip, that.dest_ip) == 0) 
          && (src_port == that.src_port) && (dest_port == that.dest_port);
   }

   bool operator<(const Flow &that)const
   {
      int res; 
      if((res = strcmp(that.src_ip, src_ip)) != 0)
         return res;
    
      if((res = strcmp(that.dest_ip, dest_ip)) != 0)
         return res;
         
      if(src_port != that.src_port)
         return src_port < that.src_port;
      
      if(dest_port != that.dest_port)
         return dest_port < that.dest_port;
   }
};

struct mycmp
{
   bool operator()(struct Flow *a, struct Flow *b)const
   {
      int res;
      if((res = strcmp(b->src_ip, a->src_ip)) != 0)
         return res;
    
      if((res = strcmp(b->dest_ip, a->dest_ip)) != 0)
         return res;
         
      if(a->src_port != b->src_port)
         return a->src_port < b->src_port;
      
      if(a->dest_port != b->dest_port)
         return a->dest_port < b->dest_port;       
   } 
};

int main(int argc, char **argv)
{
   int pack_sum;
   char s;
   char src_ip[16], dest_ip[16];
   int src_port, dest_port;

   scanf("%d", &pack_sum);
   map<struct Flow, int> flow_number;

   memset(src_ip, '\0', 16);
   memset(dest_ip, '\0', 16);
   int res = 1;
   
   for(int i = 0; i < pack_sum; ++i)
   {
      scanf("%s %d %s %d", src_ip, &src_port, dest_ip, &dest_port);
      s = getchar();
      struct Flow flow1;
      strcpy(flow1.src_ip, src_ip);
      strcpy(flow1.dest_ip, dest_ip);
      flow1.src_port = src_port;
      flow1.src_port = dest_port;

      if(flow_number.find(flow1) == flow_number.end())
      {
         printf("%d\n", res);
         flow_number[flow1] = res++; 
      }
      else
         printf("%d\n", flow_number[flow1]);
   }
}