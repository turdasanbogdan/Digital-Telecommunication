#include "AT_parse.h"
#include "AT_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
AT_COMMAND_DATA  at_data;

uint8_t at_command_parse(char current_character){
    
    static int state = 0;
    static int nr_char;
    
    switch(state)
    {
        case 0:
        
            if(current_character == 0x0D){
               // printf("state: %d", state);
                state = 1;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            break;
        
            
        
        case 1:
        
            if(current_character == 0x0A){
                state = 2;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
         
        case 2:
            
           
            if(current_character == '+'){
                    state = 3;
            }
            else if(current_character == 'O'){
                state = 4;
            }
            else if(current_character == 'E'){
                state = 5;
            }
            else if(current_character > 30 && current_character < 127) // ASCII code for null, space, cancel etc (all of that species) and DEL
            {
                at_data.data[at_data.line_count][nr_char++] = current_character;
                state = 6;
            }
            else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
       
        // <--------- OK --------->
            
        case 4:
            if(current_character == 'K'){
                state = 40;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
        case 40:
            if(current_character == 0x0D){
                state = 41;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }

            break;
            
        case 41:
            if(current_character == 0x0A){
                state = 0;
                return STATE_MACHINE_READY_OK;
            }else {
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            
            break;
            
            
            // <--------- ERROR --------->
        
        case 5:
            if(current_character == 'R'){
                state = 50;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
           
            break;
            
        
        case 50:
            if(current_character == 'R'){
                state = 51;
            }else {
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
        case 51:
            if(current_character == 'O'){
                state = 52;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
        case 52:
            if(current_character == 'R'){
                state = 53;
            }else {
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
        case 53:
            if(current_character == 0x0D){
                state = 54;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }

            break;
            
        case 54:
            if(current_character == 0x0A){
                state = 0;
                return STATE_MACHINE_READY_WITH_ERRORS;
            }else {
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            
            break;
            
         
            // <--------- CHARACTER --------->
            
        
        case 3:
            
            if(current_character != 0x0A ){
                at_data.data[at_data.line_count][nr_char++] = current_character;
                state = 30;
            }else {
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
    
            
        case 30:
            if(current_character == 0x0D){
                at_data.data[at_data.line_count][nr_char++] = 0X00;
                state = 31;
                at_data.line_count++;
                nr_char = 0;
            }
            else if(current_character == 0x0A){
                nr_char = 0;
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            else{
                if(nr_char < AT_COMMAND_MAX_LINE_SIZE - 1){
                    at_data.data[at_data.line_count][nr_char++] = current_character;
                }else{
                    if(at_data.data[at_data.line_count][AT_COMMAND_MAX_LINE_SIZE - 1] != 0X00){
                        at_data.data[at_data.line_count][AT_COMMAND_MAX_LINE_SIZE - 1] = 0X00;
                    }
                }
            }
            
            
            break;
        
        case 31:
            if(current_character == 0x0A){
                state = 32;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }

            break;
           
        case 32:
            if(current_character == '+'){
                state = 3;
            }
            else if(current_character == 0x0D){
                state = 33;
            }
            else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
        case 33:
            if(current_character == 0x0A){
                state = 34;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }

            break;
            
        case 34:
            if(current_character == 'O'){
                state = 4;
            }
            else if(current_character == 'E'){
                state = 5;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            break;
            
            
            // <--------- CHARACTER SPECIAL CASE --------->
        
        case 6:
            
            if(current_character ==  0x0D){
               
                state = 60;
                at_data.data[at_data.line_count++][nr_char++] = '\0';
                nr_char = 0;
            }else if(current_character > 30 && current_character < 127){
                at_data.data[at_data.line_count][nr_char++] = current_character;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
        case 60:
            
            if(current_character == 0x0A ){
                state = 61;
            }else {
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            break;
            
        case 61:
            
            if(current_character == 0x0D){
                state  = 62;
            }else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            break;
           
        case 62:
            
            if(current_character == 0x0A ){
                state = 63;
            }else {
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            break;
            
            break;
          
        case 63:
            
            if(current_character == 'O'){
                state = 4;
            }
            else if(current_character == 'E'){
                state = 5;
            }
            else{
                return  STATE_MACHINE_EXIT_SYNTAX_ERROR;
            }
            
            break;
            
            
       
    }
   
    return STATE_MACHINE_NOT_READY;
}
