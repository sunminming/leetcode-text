#include <stdio.h>
#include <string.h>

enum color {
    NONE, WHITE, BLACK,         //棋子颜色，NONE表示未落子
};
struct weiqi {
    enum color board[19][19];   //棋盘上每个位置的落子
};

/*
输入:
0000000000000000000
0000011000000000000
0000121111000000000
0012221021100000000
0120001112100000000
1200001222000000000
2000001200000000000
0000001200000000000
0000001220000000000
0000001122220000000
0000002111110000000
0000002100000000000
0000002100000000000
0000002100000000000
0000002100000000000
0000002100000000000
0000000100000000000
0000000100000000000
0000000100000000000
5,2

对应输出应该为:
298
*/

void go(struct weiqi *wq, int x, int y, enum color st, int *cnt)
{
   if(x >= 0 && x < 19 && y >= 0 && y < 19)
   {
      if(wq->board[y][x] == st || wq->board[y][x] == NONE)
      {
         if(wq->board[y][x] == NONE)
         {
            wq->board[y][x] = st;
            ++(*cnt);
         }
         switch(wq->board[y][x]) {
            case WHITE:
               wq->board[y][x] = BLACK;
               break;
            case BLACK:
               wq->board[y][x] = WHITE;
               break;
         }
         
         //up
         go(wq, x, y - 1, st, cnt);
         //down
         go(wq, x, y + 1, st, cnt);
         //left
         go(wq, x - 1, y, st, cnt);
         //right
         go(wq, x + 1, y, st, cnt);
      }
      else return;//this point is other color
   } 
   else return;//this point is out of checkerboard
}

int calc(struct weiqi *wq, int x, int y)
{
   //printf("wq->board[y][x] = %d\n", wq->board[y][x]);
   int cnt = 0;
   enum color st = wq->board[y][x];
   switch (wq->board[y][x]) {
      case WHITE:
         wq->board[y][x] = BLACK;
         break;
      case BLACK:
         wq->board[y][x] = WHITE;
         break;
      default:
         return -1;
   }
   //up
   go(wq, x, y - 1, st, &cnt);
   //down
   go(wq, x, y + 1, st, &cnt);
   //left
   go(wq, x - 1, y, st, &cnt);
   //right
   go(wq, x + 1, y, st, &cnt);
   return cnt;
}
int input(struct weiqi *wq, int *x, int *y)
{
    int row, col;
    int ret;
    char buf[21];
    memset(buf, 0, 21);
    for (row = 0; row < 19; ++row) {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            return -1;
        if (strlen(buf) < 19)
            return -1;
        for (col = 0; col < 19; ++col) {
            switch (buf[col]) {
            case '0':
                wq->board[row][col] = NONE;
                break;
            case '1':
                wq->board[row][col] = WHITE;
                break;
            case '2':
                wq->board[row][col] = BLACK;
                break;
            default:
                return -1;
            }
        }
    }
    ret = fscanf(stdin, "%d,%d", x, y);
    char s = getchar();
    if (ret != 2)
        return -1;
    //for (row = 0 ; row < 19; ++row) {
    //    for (col = 0; col < 19; ++col) {
    //        fprintf(stderr, "%d ", wq->board[row][col]);
    //    }
    //    fprintf(stderr, "\n");
    //}
    //fprintf(stderr, "x = %d, y = %d\n", *x, *y);
    return 0;
}

int main()
{
    struct weiqi wq;
    int x = 0, y = 0;
    int cnt;

    memset(&wq, 0, sizeof(wq));
    if (input(&wq, &x, &y) < 0) {
        fprintf(stderr, "error!\n");
        return 1;
    }
    cnt = calc(&wq, x, y);

    printf("%d\n", cnt);
    return 0;
}