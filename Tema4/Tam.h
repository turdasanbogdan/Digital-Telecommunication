#include <stdint.h>
#include <stdint.h>

#ifndef Tam_h
#define Tam_h

#define AT_COMMAND_MAX_LINES 100
#define AT_COMMAND_MAX_LINE_SIZE 200

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

extern AT_COMMAND_DATA atSavedData;

uint8_t at_command_parse(char current_character);

#endif

