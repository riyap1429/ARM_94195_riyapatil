/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
unsigned int reg= 0X05;
unsigned int result1,result2;

 printf("input:");
 printf("0x%02X\n",reg);
 
   result1= reg<<2;
  printf("output after shifting left  :");
  
     printf("0x%02X\n",result1);
     
     result2= reg>>1;
  printf("output after shifting right :");
   printf("0x%02X\n",result2);
     
  

}