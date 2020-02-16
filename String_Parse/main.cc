#include <stdio.h>
#include <malloc.h>
#include <error.h>
#include <string.h>
#include <ctype.h>

int unescape_c_quoted(char *buf, const char *str)
{
   int s_index = 1;
   int p_index = 0;
   if(str[0] != '\"' || str[strlen(str) - 1] != '\"') return -1;
   while(s_index < strlen(str) - 1)
   {
      if(str[s_index] != '\\')
         buf[p_index++] = str[s_index];
      else
      {
         switch(str[s_index + 1])
         {
            case '"' :
               buf[p_index++] = '"';
               break;
            case '\\' :
               buf[p_index++] = '\\';
               break;
            case '\'' :
               buf[p_index++] = '\'';
               break;
            case '?' :
               buf[p_index++] = '?';
               break;
            case 'a' :
               buf[p_index++] = '\a';
               break;
            case 'b' :
               buf[p_index++] = '\b';
               break;
            case 'f' :
               buf[p_index++] = '\f';
               break;
            case 'r' :
               buf[p_index++] = '\r';
               break;
            case 't' :
               buf[p_index++] = '\t';
               break;
            case 'v' :
               buf[p_index++] = '\v';
               break;
            case 'n' :
               buf[p_index++] = '\n';
               break;
            default :
               return -1;
               break;
         }
         ++s_index;
      }
      ++s_index;
   }
   return 0;
}

int main()
{
    char str[10000];
    char buf[10000];
    int len;

    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "input error\n");
        return 0;
    }
    len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        str[len - 1] = '\0';
        --len;
    }

    unescape_c_quoted(buf, str);
    printf("%s\n", buf);
    
    fprintf(stderr, "input:%s\noutput:%s\n", str, buf);
    return 0;
}