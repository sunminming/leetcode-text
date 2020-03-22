#include <algorithm>
#include <map>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

class Flow
{
   public:
      string src_ip;
      string dest_ip;

      int src_port;
      int dest_port;

      bool operator==(const Flow &that)const
      {
         return (src_ip == that.src_ip) 
            && (dest_ip == that.dest_ip) 
            && (src_port == that.src_port) && (dest_port == that.dest_port);
      }

      bool operator < (const Flow &that)const
      {
         if(src_ip != that.src_ip)
            return src_ip < that.src_ip;
    
         if(dest_ip != that.dest_ip)
            return dest_ip < that.dest_ip;
         
         if(src_port != that.src_port)
            return src_port < that.src_port;
      
         return dest_port < that.dest_port;
      }
};

int main(int argc, char **argv)
{
   int pack_sum;
   char s;
   
   scanf("%d", &pack_sum);
   map<Flow, int> flow_number;

   int res = 1;
   vector<Flow> flows;
   for(int i = 0; i < pack_sum; ++i)
   {
      Flow flow;
      cin >> flow.src_ip >> flow.src_port >> flow.dest_ip >> flow.dest_port;
      flows.push_back(flow);
   }

   for(int i = 0; i < pack_sum; ++i)
   {
      if(flow_number.find(flows[i]) == flow_number.end())
      {
         printf("%d\n", res);
         flow_number.insert({flows[i], res++});
      }
      else printf("%d\n", flow_number[flows[i]]);
   }
}