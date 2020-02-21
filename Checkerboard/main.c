#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int board[8][8];
int res = 0;
int dir[8][2]={-1, 0, 1, 0, 0, -1, 0, 1, -1, -1, -1, 1, 1, -1, 1, 1};//上，下，左，右，左上，右上，左下，右下

int max(int i, int j)
{
   return i > j?i:j; 
}

int find_sum(int x, int y, int dx, int dy, int color)
{
	int cnt = 1;
	x += dx; 
   y += dy;
	while(x >= 0 && x < 8 && y >= 0 && y < 8)
	{
      if(board[x][y] == 0) return 0;//blank return 0
		else
      {
         if(board[x][y] == color)//move until same color, return cnt
			   return cnt;
         else ++cnt;//is different color
      }
		x += dx;
		y += dy;
	}
	return 0;
}

void dfs(int cur_step, const int step_n)
{
	if(cur_step == step_n)
	{
		int cnt = 0;
		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 8; ++j)
			{
				if(board[i][j] == 2) ++cnt;
			}
		}
		res = max(res, cnt);
		return;
	}
   int temp_board[8][8];
   memset(temp_board, 0, 64 * sizeof(int));
	int color = 1;
	if(cur_step % 2 == 0) color = 2;
	else color = 1;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(board[i][j] == 0)//avaible
			{
				int flag = 0;
				for(int k = 0; k < 8; ++k)//eight direction
				{
					int cnt = find_sum(i, j, dir[k][0], dir[k][1], color);
					if(cnt > 1)
					{
						int x = i, y = j;
                  board[x][y] = color;
						for(int c = 0; c < cnt - 1; ++c)
						{
                     x += dir[k][0];
							y += dir[k][1];
                     board[x][y] = color;
							temp_board[x][y] = 1;
						}
						flag = 1;
					}
				}//
				if(flag)
				{
               dfs(cur_step + 1, step_n);
					for(int m = 0; m < 8; ++m)
					{
						for(int n = 0; n < 8; ++n)
                  {
                     if(temp_board[m][n])
                     {
                        //int cc = board[m][n];
                        board[m][n] = ((board[m][n] == 1?2:1));
                        //printf("Return board[%d][%d] to %d from %d\n", m, n, board[m][n], cc);
                     }
                  }
					}
					board[i][j] = 0;
               memset(temp_board, 0, 64 * sizeof(int));
				}
			}//
		}
	}
}

int main()
{
   int step_n;
	scanf("%d", &step_n);
   char s = getchar();
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			scanf("%d", &board[i][j]);
         s = getchar();
		}
	}

	dfs(0, 2 * step_n - 1);
	printf("%d\n", res);
	return 0;
}