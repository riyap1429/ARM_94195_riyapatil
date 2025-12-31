/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>

unsigned char evenParity(unsigned char b)
{
    int count = 0;
    unsigned char t = b;

    while (t)
    {
        count += t & 1;
        t >>= 1;
    }

    if (count % 2 != 0)
        b |= 0x80;

    return b;
}

int main()
{
    unsigned int n;
    scanf("%u", &n);
    printf("%u", evenParity((unsigned char)n));
    return 0;
}


