/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned int n = atoi(argv[1]);
    for (int i = 31; i >= 0; i--)
        printf("%d", (n >> i) & 1);
    return 0;
}

