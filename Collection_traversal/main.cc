#include <stdio.h>
#include <stdlib.h>

int color_n, output_sum;//球的种类数量，需要的总量
int ball_n = 0; //剩余的球的总数

void output_res(int *res)
{
   for(int color = 0; color < color_n; ++color)
   {
      printf("%d", res[color]); 
   }
   printf("\n");
}

void traceback(int *balls, int cur_color, int *res, int cur_sum, const int sum)
{
   if(cur_color == color_n)//traver all color
   {
      output_res(res);
      return; 
   } 
   else
   {
      //int res_balls = ball_n - balls[cur_color];//ball number without this color
      int min_n;//the minimum number of requests in this turn
      //if(res_balls > output_sum)//remain ball could full the box
      //   min_n = 0;
      //else min_n = sum - res_balls;
      ball_n -= balls[cur_color];
      if(ball_n > output_sum)//if remain is greater than requirement
         min_n = 0;
      else
      {
         min_n = output_sum - ball_n;
      }
      
      for(int n = min_n; n <= balls[cur_color]; ++n)
      {
         res[cur_color] = n;
         if(n + cur_sum > sum) break;
         cur_sum += n;
         output_sum -= n;
         traceback(balls, cur_color + 1, res, cur_sum, sum);
         output_sum += n;
         cur_sum -= n;
      }
      res[cur_color] = 0;
      ball_n += balls[cur_color];
   }
}

int main(int argc, char **argv)
{
   char s;
   scanf("%d %d", &color_n, &output_sum);
   s = getchar();
   int balls[color_n];
   //int ball_n;
   for(int color = 0; color < color_n; ++color)
   {
      scanf("%d", &balls[color]);
      s = getchar();
      ball_n += balls[color];
   }

   int res[color_n];//the number of each ball in the box
   int cur_sum = 0;//the balls number in the box
   traceback(balls, 0, res, cur_sum, output_sum);
}