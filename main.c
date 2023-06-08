#include "stdio.h"

extern void test();
int main(int argc, char **argv)
{
    printf("Starting test\n");
    test();
    printf("Done\n");
    return 0;
}