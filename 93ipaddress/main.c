#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void backtrace(char *s, int s_n, char *res_s, 
                int point_n, char **res, int *returnSize){
   
   if(point_n == 3 && s_n != strlen(s)) return; 
   //there are too many numbers left
   if((strlen(s) - strlen(res_s) + point_n) > 3 * (3 - point_n)) return;                 
   if(s_n == strlen(s))//all digital has been processed
   {
      if(point_n < 3) return;//
      res[*returnSize] = malloc(strlen(res_s) + 1);
      memset(res[*returnSize], '\0', strlen(res_s) + 1);
      strcpy(res[*returnSize], res_s);
      (*returnSize)++;
      return;
   }

   int res_n = strlen(res_s);
   //the last seg


   res_s[res_n++] = '.';
   ++point_n;
   
   int i = 0;

   if(s[s_n + i] == '0')//if next is 0, must add a point without other digitl
   {
      res_s[res_n + i] = s[s_n + i];
      backtrace(s, s_n + i + 1, res_s, point_n, res, returnSize);
   }
   else
   {
      for(; (i < 2) && ((s_n + i) < strlen(s)); ++i)
      {
         res_s[res_n + i] = s[s_n + i];
         backtrace(s, s_n + i + 1, res_s, point_n, res, returnSize);
      }
      if((s_n + i) < strlen(s))
      {
         char seg[4];
         memset(seg, '\0', 4);
         memcpy(seg, s + s_n, 3);
         if(atoi(seg) < 256)
         {
            res_s[res_n + i] = s[s_n + i];
            backtrace(s, s_n + i + 1, res_s, point_n, res, returnSize);
         }
      }
   }
   for(int j = strlen(res_s) - 1; res_s[j] != '.' && j >= 0; --j)
   {
      res_s[j] = '\0';
   }
   res_s[strlen(res_s) - 1] = '\0';
}

char **restoreIpAddresses(char *s, int *returnSize){

   *returnSize = 0;

   if(strlen(s) < 4) return NULL;
   int point_n = 0;
   
   char *res_s;
   res_s = malloc(strlen(s) + 4);
   memset(res_s, 0, strlen(s) + 4);
   res_s[0] = s[0];

   char **res = malloc(330 * sizeof(char *));;
   memset(res, 0, 330 * sizeof(char *));

   backtrace(s, 1, res_s, point_n, res, returnSize);
   if(s[0] == '0')
   {
      return res;
   }
   else{
      res_s[1] = s[1];
      backtrace(s, 2, res_s, point_n, res, returnSize);
      res_s[2] = s[2];
      if(atoi(res_s) < 256)
         backtrace(s, 3, res_s, point_n, res, returnSize);
      return res;
   }
}

int main(int argc, char **argv)
{
   char **res;
   
   char input[13];
   memset(input, '\0', 13);
   int input_n = read(STDIN_FILENO, input, 13);
   input[input_n - 1] = '\0';
   int *returnSize = malloc(sizeof(int *));
   *returnSize = 0;
   res = restoreIpAddresses(input, returnSize);
   

   free(res);
   free(returnSize);
   return 0;
}