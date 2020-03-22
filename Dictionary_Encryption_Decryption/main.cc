#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

void encry(char *keys)
{
   char encry[128];
   for(int i = 0; i < 26; ++i) encry['a' + i] = keys[i]; 
   for(int i = 0; i < 10; ++i) encry['0' + i] = keys[i + 26];

   char str[10000];
   memset(str, 0, 10000);
   scanf("%s", str);
   for(int i = 0; i < strlen(str); ++i) printf("%c", encry[str[i]]);
   printf("\n");
}

void decry(char *keys)
{
   char decry[128];
   for(int i = 0; i < 26; ++i) decry[keys[i]] = 'a' + i;
   for(int i = 0; i < 10; ++i) decry[keys[i + 26]] = '0' + i;

   char str[10000];
   memset(str, 0, 10000);
   scanf("%s", str);
   for(int i = 0; i < strlen(str); ++i) printf("%c", decry[str[i]]);
   printf("\n");
}

int main(int argv, char **argc)
{
   char keys[37], s;
   int mode;
   memset(keys, 0, 37);
   
   scanf("%s", keys);
   scanf("%d", &mode);
   if(mode == 1) encry(keys);
   else decry(keys);
}