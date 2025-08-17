#include "dope_sheet.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


dope_sheet_t* dope_new_sheet() {
    return (dope_sheet_t*)calloc(1, sizeof(dope_sheet_t));
}

void dope_free_sheet(dope_sheet_t* sheet) {
    free(sheet);
}

void dope_print_sheet(dope_sheet_t* sheet) {
    int i = 0;
    while((*sheet)[i][0] != '\0') {
        printf("%i %s\n", i + 1, (*sheet)[i]);
        i++;
    }
}

void dope_trim_line(dope_line_t* line) {
    if (line == NULL || (*line)[0] == '\0') {
        return; // empty or not initialized
    }
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

void dope_input_sheet(dope_sheet_t* sheet, FILE* istream) {
    for(int i = 0; i < DOPE_PROGRAM_LINES_MAX; ++i) {
        printf("%i ", i + 1);
        dope_input_line((dope_line_t*)(*sheet)[i], istream);
        if((*sheet)[i][0] == 'S' || (*sheet)[i][0] == '\0') {
            break;
        }
    }
}
