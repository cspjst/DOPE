#ifndef DOPE_SHEET_H
#define DOPE_SHEET_H

#include "dope_constants.h"
#include "dope_types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


dope_program_t* dope_new_program() {
    return (dope_program_t*)calloc(1, sizeof(dope_program_t));
}

void dope_free_program(dope_program_t* program) {
    free(program);
}

void dope_print_program(dope_program_t* program) {
    int i = 0;
    while((*program)[i][0] != '\0') {
        printf("%i %s\n", i + 1, (*program)[i]);
        i++;
    }
}

void dope_trim_line(dope_line_t* line) {
    int end = strlen(*line);
    while (end > 0 && isspace((*line)[end - 1])) {
        end--;
    }
    (*line)[end] = '\0';
}

void dope_input_line(dope_line_t* line, FILE* istream) {
    fgets(*line, DOPE_LINE_SIZE, istream);
    dope_trim_line(line);
}

void dope_input_program(dope_program_t* program, FILE* istream) {
    for(int i = 0; i < DOPE_PROGRAM_LINES_MAX; ++i) {
        printf("%i ", i + 1);
        dope_input_line((dope_line_t*)(*program)[i], istream);
        if((*program)[i][0] == 'S' || (*program)[i][0] == '\0') {
            break;
        }
    }
}

#endif
