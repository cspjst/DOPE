#include "dope_repl.h"
#include "dope_constants.h"
#include "dope_interpret.h"
#include "dope_types.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static const char DOPE_STRING_INTRO[] = "DOPE Interpreter version 0.1\n";
static const char DOPE_STRING_HELP[] = "usage: (?)help, (L)oad, (S)ave, (I)nput, (E)dit, (P)rint, (R)un, (Q)uit\n";
static const char DOPE_STRING_PROMPT[] = "Enter file name:\n";

void dope_load(dope_program_t* program, dope_data_t* data) {
    char file_path[DOPE_LINE_SIZE];
    printf("%s", DOPE_STRING_PROMPT);
    scanf("%s", file_path);
    FILE* f = fopen(file_path, "r");
    if(!f && printf("%s\n", strerror(errno))) return;
    dope_input_program(program, f);
    dope_input_data(data, f);
    fclose(f);
}

void dope_save(dope_program_t* program, dope_data_t* data) {
    char file_path[DOPE_LINE_SIZE];
    printf("%s", DOPE_STRING_PROMPT);
    scanf("%s", file_path);
    FILE* f = fopen(file_path, "w");
    if(!f && printf("%s\n", strerror(errno))) return;
    dope_print_program(program, f);
    dope_print_data(data, f);
    fclose(f);
}

void dope_input(dope_program_t* program, dope_data_t* data) {
    printf("Enter program:\n");
    dope_input_program(program, stdin);
    printf("Enter data:\n");
    dope_input_data(data, stdin);
}

void dope_edit(dope_program_t* program, dope_data_t* data) {
    dope_size_t line;
    printf("Program line number? (%i..%i)",1, program->size);
    scanf("%i", &line);
    if(line) {

    }
    printf("Data line number? (%i..%i)",1, data->size);
    scanf("%i", &line);
    scanf
    if(line) {

    }
}

void dope_list(dope_program_t* program, dope_data_t* data) {
    dope_print_program(program, stdout);
    dope_print_data(data, stdout);
}

void dope_repl(dope_program_t* program, dope_data_t* data) {
    char key;

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
            case 'I': dope_input(program, data);
            break;
            case 'E': dope_edit(program, data);
            break;
            case 'P': dope_list(program, data);
            break;
            case 'R': dope_interpret(DOPE_VARTAB_SIZE, program, data);
            break;
            case 'Q':
            break;
            //default: printf("invalid: %c", key);
            //break;
        }
    }
}
