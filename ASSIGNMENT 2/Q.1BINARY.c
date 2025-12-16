/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    unsigned char reg = 0x2A;   
    int i;

   
    reg = reg | (1 << 4);
    printf("After setting bit 4  : ");
    for (i = 7; i >= 0; i--)
        printf("%d", (reg >> i) & 1);
    

    
    reg = reg & ~(1 << 1);
    printf("After clearing bit 1 : ");
    for (i = 7; i >= 0; i--)
        printf("%d", (reg >> i) & 1);
   
   
    reg = reg ^ (1 << 5);
    printf("After toggling bit 5 : ");
    for (i = 7; i >= 0; i--)
        printf("%d", (reg >> i) & 1);
   

    return 0;
}
