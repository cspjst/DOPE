#include "dope_repl.h"
#include "dope_constants.h"
#include "dope_interpret.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static const char DOPE_STRING_INTRO[] = "DOPE Interpreter version 0.1\n";
static const char DOPE_STRING_HELP[] = "usage: (?)help, (L)oad, (S)ave, (E)nter, (P)rint, (R)un, (Q)uit\n";

void dope_load(dope_program_t* program, dope_data_t* data) {
    printf("Enter file name:\n");
    FILE* f = fopen(,"r");
    if(!f) {
        strerror(errno);
        return;
    }
    dope_input_program(program, f);
    dope_input_data(data, f);
    fclose(f);
}

void dope_save(dope_program_t* program, dope_data_t* data) {
    printf("Enter file name:\n");
    FILE* f = fopen(,"w");
    if(!f) {
        strerror(errno);
        return;
    }
    dope_print_program(program, f);
    dope_print_data(data, f);
    fclose(f);
}

void dope_enter(dope_program_t* program, dope_data_t* data) {
    printf("Enter program:\n");
    dope_input_program(program, stdin);
    printf("Enter data:\n");
    dope_input_data(data, stdin);
}

void dope_list(dope_program_t* program, dope_data_t* data) {
    dope_print_program(program, stdout);
    dope_print_data(data, stdout);
}

void dope_repl(dope_program_t* program, dope_data_t* data) {
    char key = '\0';

    printf("%s%s", DOPE_STRING_INTRO, DOPE_STRING_HELP);

    while(key != 'Q') {
        key = toupper(getchar());
        switch(key) {
            case '?': printf("%s", DOPE_STRING_HELP);
            break;
            case 'L': dope_load(program, data);
            break;
            case 'S': dope_save(program, data);
            break;
            case 'E': dope_enter(program, data);
            break;
            case 'P': dope_list(program, data);
            break;
            case 'R': dope_interpret(DOPE_VARTAB_SIZE, program, data);
            break;
            case 'Q':
            break;
            default: printf("invalid: %c", key);
            break;
        }
    }
}
