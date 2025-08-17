#include "dope_data_sheet.h"
#include "dope_constants.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

dope_data_sheet_t* dope_new_data_sheet(int line_count) {
    dope_data_sheet_t* sheet = malloc(sizeof(dope_data_sheet_t));
    if (!sheet) return NULL;

    sheet->lines = calloc(line_count, sizeof(dope_data_line_t));
    if (!sheet->lines) {
        free(sheet);
        return NULL;
    }

    sheet->capacity = line_count;
    sheet->count = 0;
    return sheet;
}

void dope_free_data_sheet(dope_data_sheet_t* sheet) {
    if (sheet) {
        free(sheet->lines);
        free(sheet);
    }
}

void dope_trim_field(dope_data_field_t* field) {
    if (field == NULL || (*field)[0] == '\0') {
        return; // empty or not initialized
    }
    // 1. strip trailing whitespace
    char* end = *field + strlen(*field) - 1;
    while (end >= *field && isspace((unsigned char)*end)) {
        end--;
    }
    end[1] = '\0';
    // 2. Strip leading whitespace
    char* start = *field;
    while (isspace((unsigned char)*start)) {
        start++;
    }
    // 3. Shift remaining characters (if needed)
    if (start != *field) {
        memmove(*field, start, strlen(start) + 1);
    }
}

void dope_print_data_line(dope_data_line_t* line) {
    printf("| %i | %s | %s | %s |\n",
        (*line).run, (*line).fields[0], (*line).fields[1], (*line).fields[2]);
}

void dope_print_data_sheet(dope_data_sheet_t* data) {
    for(int i = 0; i < data->count; ++i) {
        printf("%i ", i);
        dope_print_data_line(&(*data).lines[i]);  // Pass address of the element
    }
}

void dope_input_data_ubyte(uint8_t * ubyte, FILE* istream) {
    if (ubyte && istream) {
        if (fscanf(istream, "%hhu", ubyte) != 1) {
            *ubyte = 0;
        }
        while (fgetc(istream) != '\n' && !feof(istream));
    }
}

void dope_input_data_field(dope_data_field_t* field, FILE* istream) {
    if (!field || !istream) {
        return; // NULL inputs
    }
    // 1. handle EOF or error on istream
    if (!fgets(*field, DOPE_FIELD_SIZE, istream)) {
        (*field)[0] = '\0';  // ensure field is tidy ""
        return;
    }
    // 2. check for truncation (newline absence)
    if (!strchr(*field, '\n')) {
        while (fgetc(istream) != '\n' && !feof(istream));  // Flush excess input if buffer was filled
    }
    // 3. tidy up input
    dope_trim_field(field);
}

void dope_input_data_line(dope_data_line_t* line, FILE* istream) {
    printf("Run No. ");
    dope_input_data_ubyte(&(*line).run, istream);
    printf("Variable ");
    dope_input_data_field(&(*line).fields[0], istream);
    printf("Magnitude (or label) ");
    dope_input_data_field(&(*line).fields[1], istream);
    printf("Exponent ");
    dope_input_data_field(&(*line).fields[2], istream);
}

void dope_input_data_sheet(dope_data_sheet_t* data, FILE* istream) {
    for (size_t i = 0; i < data->capacity; ++i) {
        dope_input_data_line(&data->lines[i], istream);
        data->count++;
        if(data->count > data->capacity) {}
        if (strcmp(data->lines[i].fields[1], "FINISH") == 0 || data->lines[i].run == 0) {
            break;
        }
    }
}
