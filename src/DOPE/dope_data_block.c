#include "dope_data_block.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

dope_data_t* dope_new_data_block(uint8_t line_count) {
    dope_data_t* data = malloc(sizeof(dope_data_t));
    if(!data) {
        return NULL;
    }
    data->args = calloc(line_count, sizeof(dope_argument_t));
    if(!data->args) {
        free(data);
        return NULL;
    }
    data->capacity = line_count;
    data->size = 0;
    data->si = 0;
    return data;
}

void dope_free_data_block(dope_data_t* data_block) {
    if (data_block) {
        free(data_block->args);
        free(data_block);
    }
}

void dope_clear_data(dope_argument_t* arg) {
    memset(arg, 0, sizeof(dope_argument_t));
}

bool dope_is_number(char* str) {
    return (*str == '+' || *str== '-');
}

void dope_parse_mag(dope_argument_t* arg, char* magnitude) {
    arg->type = DOPE_DATA_INVALID; // assume invalid
    // 0. null checks
    if (!magnitude) {
        arg->error_code = DOPE_ERR_NULL;
        strcpy(arg->value.label, " char* magnitude!");
        return;
    }
    // 1. Check is a number
    if(!dope_is_number(magnitude)) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " MAG no sign!");
        return;
    }
    // 2. Check minimum length
    if(strlen(magnitude) < 2) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " MAG size < 2!");
        return;
    }
    // 3. Process each magnitude character after the sign
    int npoints = 0;
    int ndigits = 0;
    for (int i = 1; magnitude[i] != '\0'; i++) {
        if (magnitude[i] == '.') {
            if (++npoints > 1) {
                arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
                strcat(arg->value.label, " MAG multiple dcp!");
                return;
            }
        } else if (isdigit((unsigned char)magnitude[i])) {
            if (++ndigits > 6) {
                arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
                strcat(arg->value.label, " MAG >6 digits!");
                return;
            }
        } else {
            arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
            return;
        }
    }
    // 5. Must have at least one digit
    if (ndigits == 0) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " MAG not all digits!");
        return;
    }
    // 6. check conversion
    char* end;
    float m = strtof(magnitude, &end);
    if (*end != '\0') {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " MAG fail strtof!");
        return;
    }
    arg->type = DOPE_DATA_NUMBER;
    arg->error_code = DOPE_ERR_SUCCESS;
    strcpy(arg->value.label, "");
    arg->value.number = m;
}

void dope_parse_exp(dope_argument_t* arg, char* exponent) {
    // 1. permit default (+00) or already invalid
    if(!exponent || arg->type == DOPE_DATA_INVALID) {
        return;
    }
    arg->type = DOPE_DATA_INVALID; // assume invalid
    // 2. sign check
    if(!dope_is_number(exponent)) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcpy(arg->value.label, exponent);
        strcat(arg->value.label, " EXP no sign!");
        return;
    }
    // 3. Check correct length
    if(strlen(exponent) != 3) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcpy(arg->value.label, exponent);
        strcat(arg->value.label, " EXP size != 3!");
        return;
    }
    // 4. Process each exponent character after the sign
    for (int i = 1; i < 3; i++) {
        if (!isdigit((unsigned char)exponent[i])) {
            arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
            strcpy(arg->value.label, exponent);
            strcat(arg->value.label, " EXP not all digits!");
            return;
        }
    }
    // 5. Check exponent range
    int e = atoi(exponent);
    if (e < -36 || e > 36)  {
        arg->error_code = DOPE_ERR_EXPONENT_OUT_OF_RANGE;
        strcpy(arg->value.label, exponent);
        return;
    }
    // 6. valid exponent
    arg->type = DOPE_DATA_NUMBER;
    arg->value.number *= power_of_10(e);
}

void dope_parse_number(dope_argument_t* arg) {
    // 1. tokenize into magnitude and 10x exponent (if there is one)
    char* magnitude = strtok(arg->value.label, DOPE_DELIM_STR);
    char* exponent = strtok(NULL, DOPE_DELIM_STR);
    // 2. parse each token
    dope_parse_mag(arg, magnitude);
    dope_parse_exp(arg, exponent);
}

void dope_input_argument(dope_argument_t* arg, FILE* istream) {
    dope_clear_data(arg);
    // 1. read the line and catch truncated and invalid character errors
    uint8_t length = dope_read_line(&arg->value.label, istream);
    if(dope_is_truncated(&arg->value.label)) {
        arg->error_code = DOPE_ERR_LINE_TOO_LONG;
        dope_consume_remaining(istream);
        return;
    }
    // 2. sanitize line
    arg->value.label[strcspn(arg->value.label, "\n")] = '\0';
    // 3. parse if number
    if(dope_is_number(arg->value.label)) {
        arg->type = DOPE_DATA_NUMBER;
        dope_parse_number(arg);
        return;
    }
    // 4. otherwise plain string
    arg->type = DOPE_DATA_LABEL;
    // dope_parse_label
    return;
}

void dope_print_arg(dope_argument_t* arg) {
    printf("%i %lf %s %i %s\n",
        arg->type,
        arg->value.number,
        arg->value.label,
        arg->error_code,
        dope_error_message(arg->error_code)
    );
}
