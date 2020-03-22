#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

unsigned int align_n(unsigned int size, int n)
{
   unsigned int res; 
   memset(&res, 255, 4);
   res = res << n;
   res = size & res;
   if(res < size) res += (1 << n);
   return res;
}

int main(int argc, char **argv)
{
   unsigned int size, res;
   int n; 
   scanf("0x%x,%d", &size, &n);
   
   printf("0x%x\n", align_n(size, n));
}