#include <stdio.h>
int main(int argc, char * argv[]){
    int count=0; // count valid arguments
    for(int i =1;i<argc;i++){
        if(argv[i][0] == '-')
            continue;
        printf("%s\n",argv[i]);
        count++;
    }

    if(count != 0)
        printf("\n");
    return 0;
}