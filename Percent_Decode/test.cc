#include <stdio.h>
using namespace std;

int main()
{
   char top[] = "32";
   char s;
   sscanf(top, "%x", &s);
   printf("%c", s); 
}