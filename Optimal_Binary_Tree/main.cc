#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <malloc.h>

struct node {
    int left, right, parent;
    int val;
};

void tree_print(const struct node arr[], int cnt)
{
    int i;
    for (i = 0; i < cnt; ++i) {
        fprintf(stderr, "%d: {left:%d,right:%d,parent:%d,val:%d}\n"
            , i, arr[i].left, arr[i].right, arr[i].parent, arr[i].val);
    }
}

void tree_output(FILE *fp, const struct node arr[], int old_cnt, int cnt)
{
    int i;
    fprintf(fp, "```mermaid\n");
    fprintf(fp, "graph TD\n");
    for (i = 0; i < cnt; ++i) {
        if (i < old_cnt)
            //fprintf(fp, "\tn%d[n%d:%d]\n", i, i, arr[i].val);
            printf("\tn%d[n%d:%d]\n", i, i, arr[i].val);
        else
            //fprintf(fp, "\tn%d((%d))\n", i, arr[i].val);
            printf("\tn%d((%d))\n", i, arr[i].val);

        if (arr[i].parent >= 0) {
            //fprintf(fp, "\tn%d --> n%d\n", i, arr[i].parent);
            printf("\tn%d --> n%d\n", i, arr[i].parent);
        }
    }
    //fprintf(fp, "```\n");
    printf("```\n");
}

int build_tree(struct node arr[], int cnt);

static int input(int **arr, int *size)
{
    int i;
    int ret;
    char s;
    //ret = fscanf(stdin, "%d\n", size);
    ret = scanf("%d", size);
    s = getchar();
    if (ret != 1)
        return -1;
    if (*size <= 0)
        return -1;
    *arr = (int *)malloc(sizeof(int) * (*size));
    for (i = 0; i < *size; ++i) {
        //fscanf(stdin, "%d ", &(*arr)[i]);
        scanf("%d", &(*arr)[i]);
        s = getchar();
    }
    return 0;
}
int main(int argc, char *argv[])
{
    int *vals = NULL;
    int cnt = 0;
    struct node *arr;
    int i;

    if (input(&vals, &cnt) < 0) {//input an array vals of length cnt
        fprintf(stderr, "input error\n");
        return 0;
    }
    arr = (struct node *)malloc(sizeof(struct node) * cnt * 3);

    for (i = 0; i < cnt; ++i) {
        arr[i].left = -1;
        arr[i].right = -1;
        arr[i].parent = -1;
        arr[i].val = vals[i];
    }

    int f_cnt = build_tree(arr, cnt);
    
    tree_output(stdout, arr, cnt, f_cnt);

    free(vals);
    free(arr);
    return 0;
}

//  建树，返回树的根节点
int build_tree(struct node arr[], int cnt)
{
    while (1) {
        int i;
        int min1 = -1;              //权值最小的节点编号
        int min2 = -1;              //权值第二小的节点编号
        int root_node = 0;          //根节点(没有父节点)的个数

        for (i = 0; i < cnt; ++i) {//to find the smallest two
            if (arr[i].parent >= 0)//has been processed
                continue;
            ++root_node;
            if (min1 < 0) {
                min1 = i;
            } else if (arr[i].val < arr[min1].val) {
                min2 = min1;
                min1 = i;
            } else if (min2 < 0) {
                min2 = i;
            } else if (arr[i].val < arr[min2].val) {
                min2 = i;
            }
        }
        if (root_node < 2)//all node has been processed
            break;
        arr[cnt].left = min2;
        arr[cnt].right = min1;
        arr[cnt].val = arr[min1].val + arr[min2].val;
        arr[cnt].parent = -1;
        arr[min1].parent = cnt;
        arr[min2].parent = cnt;
        ++cnt;
    }
    return cnt;
}