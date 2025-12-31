/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>

void printBinary(unsigned int n)
{
    for (int i = 31; i >= 0; i--)
        printf("%d", (n >> i) & 1);
}

int main()
{
    unsigned int n;
    scanf("%u", &n);
    printBinary(n);
    return 0;
}
