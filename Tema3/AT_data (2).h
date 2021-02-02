//
//  AT_data.h
//  TD2
//
//  Created by Bogdan Turdasan on 01/11/2020.
//

#ifndef AT_data_h
#define AT_data_h

#define AT_COMMAND_MAX_LINES 100
#define AT_COMMAND_MAX_LINE_SIZE 128

#include <stdint.h>

typedef enum{
    STATE_MACHINE_NOT_READY,
    STATE_MACHINE_READY_OK,
    STATE_MACHINE_READY_WITH_ERRORS,
    STATE_MACHINE_EXIT_SYNTAX_ERROR
}STATE_MACHINE_RETURN_VALUE;

typedef struct{
    uint8_t ok;
    uint8_t data[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE];
    uint32_t line_count;
}AT_COMMAND_DATA;

extern AT_COMMAND_DATA at_data;
#endif /* AT_data_h */
