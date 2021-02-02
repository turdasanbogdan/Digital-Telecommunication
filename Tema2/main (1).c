#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AT_data.h"
#include "AT_parse.h"


extern AT_COMMAND_DATA at_data;

void at_print_words(){
    for(int i=0; i< AT_COMMAND_MAX_LINES; i++){
       if(at_data.data[i][0] == '\0') break;
       
        printf("%s\n", at_data.data[i]);
    }
}

void at_release(){
    for(int i=0; i < at_data.line_count; i++){
        memset(at_data.data[i], '\0', AT_COMMAND_MAX_LINE_SIZE);
    }

    at_data.line_count = 0;
    at_data.ok = 0;
}

int main(int argc, char ** argv){
    
   
   
    
    FILE *f;

    if(argc < 2){
        printf("please provide the file path");
        exit(0);
    }
     
    printf("%s \n", argv[1]);
    f = fopen("./fisier.txt", "r");

    if( f == NULL){
        printf("File is not available \n");
        exit(0);
    }

    char cc = fgetc(f);

    while(cc != EOF ){
        int res;

        res = at_command_parse(cc);

        if(res == 2){
            at_print_words();
            at_release();
            
            printf("Done with Errors\n\n");
            
        }
        else if(res == 1){
            at_print_words();
            at_release();
            
            printf("Done with OK\n\n");
            
        }
        else if(res == 0 ){
           
        }else{
            printf("What the beep is this ?\n\n");
        }

        
        cc = fgetc(f);
    }
    
    
 
 
    fclose(f);
    
    

    return 0;
}
