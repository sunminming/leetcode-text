#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

void traceback(string &str, int index, stack<char> &sta, vector<char> &res)
{
   if(index == str.length())
   {
      //将sta的值放入res
      int sta_n = sta.size();
      char c;
      for(int i = 0; i < sta_n; ++i)
      {
          c = sta.top();
          sta.pop();
          res.push_back(c);
      }

      for(int i = 0; i < res.size(); ++i)
      {
         cout << res[i];
      }
      cout << endl;

      //装回去
      int res_n = res.size();
      while(sta_n)
      {
         sta_n--;
         c = res[--res_n];
         sta.push(c);
         res.pop_back();
      }
      return;
   }
   if(sta.empty())
   {
      sta.push(str[index]);
      traceback(str, index + 1, sta, res);
      sta.pop();
   }
   else
   {
      char c = sta.top();
      sta.pop();
      res.push_back(c);
      traceback(str, index, sta, res);
      res.pop_back();
      sta.push(c);

      sta.push(str[index]);
      traceback(str, index + 1, sta, res);
      sta.pop();
   }
   /*
   if(!sta.empty())
   {
      sta.push(str[index]);
      traceback(str, index + 1, sta, res);
      sta.pop();

      char c = sta.top();
      sta.pop();
      res.push_back(c);
      traceback(str, index, sta, res);
      res.pop_back();
      sta.push(c);
   }
   else
   {
      sta.push(str[index]);
      traceback(str, index + 1, sta, res);
      sta.pop();
   }
   */
}

int main(int argc, char **argv)
{
   string str;
   stack<char> sta;
   vector<char> res;
   int index = 0;
   cin >> str;
   
   traceback(str, index, sta, res);
   
   return 0;
}