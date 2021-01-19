#include <stdio.h>
#include <ctype.h>
int main(){
    int count =0;
    while(1){
        int c = getchar();
        if(c == EOF)
            break;
        if(!isalpha(c))
            ++count;
        putchar(c);
    }
    printf("\ntotal non alphabetic characters:\t%d\n",count);
    return 0;
}