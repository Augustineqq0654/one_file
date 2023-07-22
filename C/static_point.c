#include <stdio.h>
#include <stdlib.h>

static char * byte = NULL;
void init()
{
    byte = (char*)malloc(10);
}
int main()
{
    printf("%#x\t%#x\t\n", &byte, byte);
    init();
    printf("%#x\t%#x\t%d\n", &byte, byte, *byte);
    *byte = 100;
    printf("%#x\t%#x\t%d\n", &byte, byte, *byte);
    free(byte);
    return 0;
}