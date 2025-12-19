/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>

int main()
{
    {
    unsigned char reg = 0xAA;
    unsigned int read_value, write_value;
    
          printf( "input :" );
    for(int i=7; i>=0;i--)
    {
        printf(("%d"),((reg>>i)&1));
        if(i==4) printf(" ");
    }
    printf("\n");
    {
    read_value= (reg>>2)& 0x07;
    printf( "read value from bits 2 to 4 :",read_value );
    for(int i=2; i>=0;i--)
    {
        printf(("%d"),((read_value>>i)&1));
        if(i==4) printf(" ");
    }
    printf("\n");
    }
    reg &=~(0x07<<2);
    reg |= (0x03<<2);
      printf( "write value from bits 2 to 4 :" );
     for(int i=7; i>=0;i--)
    {
        printf(("%d"),((reg>>i)&1));
        if(i==4) printf(" ");
    }
    printf("\n");
    
    return 0;
    }
}

