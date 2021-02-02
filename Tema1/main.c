#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AT_data.h"
#include "AT_parse.h"

int main(int argc, char ** argv){
    
   
    FILE *f;

    if(argc < 2){
        printf("please provide the file path");
        exit(0);
    }
     
    printf("%s \n", argv[1]);
    f = fopen("./file.txt", "r");

    if( f == NULL){
        printf("File is not available \n");
        exit(0);
    }

    char cc = fgetc(f);

    while(cc != EOF ){
        printf(".. %c ..  ", cc);

        int res;

        res = at_command_parse(cc);
        printf(" -----> %d \n", res);

        if(res == 2){
            printf("Done with Errors");
            
            return 0;
        }
        else if(res == 1){
            printf("Done with OK");
            
            return 0;
        }
        else if(res == 0 ){
            printf("Not yet\n");
        }else{
            printf("What the beep is this ?");
        }

        
        cc = fgetc(f);
    }
    
   
 
 
    fclose(f);
    
    

    return 0;
}
