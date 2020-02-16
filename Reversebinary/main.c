#include <stdio.h>
#include <string.h>

unsigned int reverse(unsigned int num)
{
    unsigned int res;
    res = ((num >> 1) & 0x55555555) | ((num << 1) & 0xaaaaaaaa);
    res = ((res >> 2) & 0x33333333) | ((res << 2) & 0xcccccccc);
    res = ((res >> 4) & 0x0f0f0f0f) | ((res << 4) & 0xf0f0f0f0);
    res = ((res >> 8) & 0x00ff00ff) | ((res << 8) & 0xff00ff00);
    res = ((res >> 16) & 0x0000ffff) | ((res << 16) & 0xffff0000);
    return res;
}

int main(int argc, char *argv[])
{
    unsigned int num = 0;
    unsigned int ret = 0;

    if (1 != fscanf(stdin, "0x%x", &num)) {
        fprintf(stderr, "input error\n");
        return 0;
    }
    ret = reverse(num);
    printf("%08x\n", ret);
    return 0;
}