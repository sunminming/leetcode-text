#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

bool matchdict(string &str, vector<string> &dict, vector<bool> &flag, int index)
{
   if(index == str.length()) return true;
   if(index > str.length()) return false;
   flag[index] = true;

   for(vector<string>::iterator it = dict.begin(); it != dict.end(); ++it)
   {
      int word_len = (*it).length();
      if(flag[index + word_len] == false && (*it) == str.substr(index, word_len))
      {
         return matchdict(str, dict, flag, index + word_len);
      }
   }
   return false;
}

int main(int argc, char **argv)
{
   unsigned int dict_n;
   char s;
   vector<string> dict;
   scanf("%d", &dict_n);
   s = getchar();
   
   string str;
   for(unsigned int i = 0; i < dict_n; ++i)
   { 
      cin >> str;
      dict.push_back(str);
   }
   cin >> str;
   
   vector<bool> flag(str.length(), false);
   
   bool res = matchdict(str, dict, flag, 0);

   if(res) printf("yes\n");
   else printf("no\n");
   return 0;
}