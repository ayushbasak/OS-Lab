// This is a ROT13 Cipher
#include <stdio.h>
#include <ctype.h>
int main(){
    int c;
    while(1){
        c = getchar();
        if(c == EOF) break;
        if(isalpha(c)){
            if(islower(c)){
                if(c >= 109)
                    c -= 13;
                else
                    c += 13;
            }
            else{
                if(c >= 77)
                    c -= 13;
                else
                    c += 13;
            }
        }
        putchar(c);
    }
    return 0;
}