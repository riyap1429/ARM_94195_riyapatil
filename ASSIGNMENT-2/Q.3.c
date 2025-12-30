/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    unsigned char reg = 0xABCD;
    unsigned lower4;
    unsigned upper4;
    lower4 = reg & 0x0F;
    printf("Lower 4 bits: 0x%X\n", lower4);
    upper4 = (reg & 0xF0) >> 4;
    printf("Upper 4 bits: 0x%X\n", upper4);
    return 0;
}

