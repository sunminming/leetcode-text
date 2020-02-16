#include <stdio.h>
#include <string.h>
#include <malloc.h>

int match(const char *str, const char *pattern)
{
    int s_len = strlen(str);
    int p_len = strlen(pattern);
    if(s_len == 1 && p_len == 1) return 0;//only \n in str and pattern
    if(s_len != 1 && p_len == 1) return -1;//pattern only has \n, but str has other chars
    if(s_len == 1 && p_len != 1)//str only has \n, but pattern has other chars
    {
        if(p_len == 2 && pattern[0] == '*') return 0;//pattern only has "*\n".(* matchs NULL)
        else return -1;
    }
    else//(s_len != 1 && p_len != 1)
    {
        if(pattern[0] == '?') //pattern[0] is '?'
            return match(str + 1, pattern + 1);
        if(str[0] == pattern[0])//cur chars are same
            return match(str + 1, pattern + 1);
        if(str[0] != pattern[0])//pattern[0] is not '?'
        {
            if(pattern[0] == '*')
            {
                //the last char is \n
                if(p_len == 2) return 0;
                char next_c = pattern[1];//next_c must not be \n
                int res = -1;
                for(int i = 0; i < s_len; ++i)
                {
                    if(str[i] == next_c)
                    {
                        if(match(str + i, pattern + 1) == 0)
                        {
                            return 0;
                        }
                    }
                }
                return -1;
            }
            else return -1;
        }
        else return -1;
    }
}

int input(char **src, char **ptn)
{
    char buf[10240];
    
    *src = NULL;
    *ptn = NULL;
    if (fgets(buf, sizeof(buf), stdin) == 0)
        goto failed_;
    *src = strdup(buf);
    if (fgets(buf, sizeof(buf), stdin) == 0)
        goto failed_;
    *ptn = strdup(buf);
    return 0;
failed_:
    if (*src)
        free(*src);
    if (*ptn)
        free(*ptn);
    *src = NULL;
    *ptn = NULL;
    return -1;
}

int main(int argc, char *argv[])
{
    char *src = NULL;
    char *ptn = NULL;
    
    if (input(&src, &ptn) < 0) {
        fprintf(stderr, "error\n");
        return 0;
    }

    if (match(src, ptn) == 0) {
        printf("match\n");
    } else {
        printf("unmatch\n");
    }
    return 0;
}