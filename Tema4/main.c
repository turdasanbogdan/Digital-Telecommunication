#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tam.h"


extern AT_COMMAND_DATA atSavedData;

void print_data(){
    for(int i=0; i<= atSavedData.line_count ; i++){
       if(atSavedData.data[i][0] == '\0') break;
       
        printf("%s\n\n", atSavedData.data[i]);
    }
}

void clear_data(){
    for(int i=0; i < atSavedData.line_count + 1; i++){
        memset(atSavedData.data[i], '\0', AT_COMMAND_MAX_LINE_SIZE);
    }

    atSavedData.line_count = 0;
    atSavedData.ok = 0;
}

int main(int argc, char ** argv){
    
    FILE *f;

    if(argc < 2){
        printf("please provide the file path");
        exit(0);
    }
     
    printf("%s \n", argv[1]);
    f = fopen(argv[1], "r");

    if( f == NULL){
        printf("File is not available \n");
        exit(0);
    }

    char c = fgetc(f);

    while(c != EOF ){
        
        int result;
        result = at_command_parse(c);
        c = fgetc(f);

       if(result == 1){
            print_data();
            clear_data();
            
            printf("OK\n\n");
            
        }
        else if(result == 2){
            print_data();
            clear_data();
            
            printf("Errors\n\n");
            
        }
        else if(result == 3 ){
            printf("syntax error here!\n");
            print_data();
            clear_data();
            
            return 0;
           
        }
        else if(result == 0){
            continue;
        }
        else{
            exit(0);
        }

        
       
    }
    fclose(f);
    
    return 0;
}
