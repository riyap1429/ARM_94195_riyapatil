/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    unsigned char reg = 0x2A;  

    reg = reg | (1 << 4);
    printf("After setting bit 4  : 0x%X\n", reg);

    
    reg = reg & ~(1 << 1);
    printf("After clearing bit 1 : 0x%X\n", reg);

   
    reg = reg ^ (1 << 5);
    printf("After toggling bit 5 : 0x%X\n", reg);

    return 0;
}
