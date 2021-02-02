#include "AT_parse.h"
#include "AT_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
AT_COMMAND_DATA at_data;

void at_print_words(uint8_t at_data[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE], int n){
    for(int i=0; i< n; i++){
        printf("%s\n", at_data[i]);
    }
    
   
}


uint8_t at_command_parse(char current_character){
    
    static int state = 0;
    static int nr_char;
    
    switch(state)
    {
        case 0:
        
            if(current_character == 0x0D){
                printf("state: %d", state);
                state = 1;
            }else{
                return  STATE_MACHINE_READY_WITH_ERRORS;
            }
            break;
        
            
        
        case 1:
        
            if(current_character == 0x0A){
                printf("state: %d", state);
                state = 2;
            }else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
            
         
        case 2:
            
            if(current_character == '+'){
//                printf("state: %d", state);
//                if(at_data.line_count > AT_COMMAND_MAX_LINES){
//                    printf("enough strings\n");
//                    return STATE_MACHINE_NOT_READY;
//                }else {
                    state = 3;
               // }
            }
            else if(current_character == 'O'){
                printf("state: %d", state);
                state = 4;
            }
            else if(current_character == 'E'){
                printf("state: %d", state);
                state = 5;
                printf("state: %d", state);
            }
            else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
       
        // <--------- OK --------->
            
        case 4:
            if(current_character == 'K'){
                printf("state: %d", state);
                state = 40;
            }else{
                return  STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
            
        case 40:
            if(current_character == 0x0D){
                state = 41;
            }else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }

            break;
            
        case 41:
            if(current_character == 0x0A){
                printf("state: %d, and ok", state);
                return STATE_MACHINE_READY_OK;
            }else {
                printf("state: %d, but with err", state);
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            
            break;
            
            
            // <--------- ERROR --------->
        
        case 5:
            if(current_character == 'R'){
                printf("state: %d", state);
                state = 50;
            }else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
           
            break;
            
        
        case 50:
            if(current_character == 'R'){
                printf("state: %d", state);
                state = 51;
            }else {
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
            
        case 51:
            if(current_character == 'O'){
                printf("state: %d", state);
                state = 52;
            }else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
            
        case 52:
            if(current_character == 'R'){
                printf("state: %d", state);
                state = 53;
            }else {
                return  STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
            
        case 53:
            if(current_character == 0x0D){
                state = 54;
            }else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }

            break;
            
        case 54:
            if(current_character == 0x0A){
                printf("state: %d , and done good", state);
                return STATE_MACHINE_READY_WITH_ERRORS;
            }else {
                return STATE_MACHINE_READY_WITH_ERRORS;
                // i should print some err in case of this
            }
            
            
            break;
            
         
            // <--------- CHARACTER --------->
            
        
        case 3:
            
            if(current_character != 0x0A ){
                printf("state: %d",state );
                at_data.data[at_data.line_count][nr_char++] = current_character;
                state = 30;
            }else {
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
    
            
        case 30:
            if(current_character == 0x0D){
                printf("state: %d",state);
                at_data.data[at_data.line_count][nr_char++] = 0X00;
                state = 31;
                printf("state: %d, end of char \n",state);
                printf("%s \n", at_data.data[at_data.line_count]);
                at_data.line_count++;
                nr_char = 0;
            }
            else if(current_character == 0x0A){
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            else{
                if(nr_char < AT_COMMAND_MAX_LINE_SIZE - 1){
                    at_data.data[at_data.line_count][nr_char++] = current_character;
                }else{
                    if(at_data.data[at_data.line_count][AT_COMMAND_MAX_LINE_SIZE - 1] != 0X00){
                        at_data.data[at_data.line_count][AT_COMMAND_MAX_LINE_SIZE - 1] = 0X00;
                    }
                    printf("String size overload, please stop :( \n");
                }
                printf("charcter to consume ===> %c", current_character);
            }
            
            
            break;
        
        case 31:
            if(current_character == 0x0A){
                state = 32;
            }else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }

            break;
           
        case 32:
            if(current_character == '+'){
                printf("state: %d",state );
                state = 3;
                printf("new char, %d", state);
            }
            else if(current_character == 0x0D){
                state = 33;
            }
            else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }
            
            break;
            
        case 33:
            if(current_character == 0x0A){
                state = 34;
            }else{
                return STATE_MACHINE_READY_WITH_ERRORS;
            }

            break;
            
        case 34:
            if(current_character == 'O'){
                printf("state:  %d , Going to OK side \n", state);
                state = 4;
            }
            else if(current_character == 'E'){
                
                printf("state:  %d , Going to error side \n", state);
                state = 5;
            }else{
                return  STATE_MACHINE_READY_WITH_ERRORS;
            }
            at_print_words(at_data.data, at_data.line_count);
            printf("%d yoooooo: ", at_data.line_count);
            break;
        
       
    }
   
    return STATE_MACHINE_NOT_READY;
}
