#include "dope_data_block.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

dope_data_block_t* dope_new_data_block(uint8_t line_count) {
    dope_data_block_t* data = malloc(sizeof(dope_data_block_t));
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

void dope_free_data_block(dope_data_block_t* data_block) {
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
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " NULL magnitude token!");
        return;
    }
    // 1. Check is a number
    if(!dope_is_number(magnitude)) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " SIGN missing!");
        return;
    }
    // 2. Check minimum length
    if(strlen(magnitude) < 2) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " SIZE magnitude < 2!");
        return;
    }
    // 3. Process each magnitude character after the sign
    int npoints = 0;
    int ndigits = 0;
    for (int i = 1; magnitude[i] != '\0'; i++) {
        if (magnitude[i] == '.') {
            if (++npoints > 1) {
                arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
                strcat(arg->value.label, " MORE than one decimal point!");
                return;
            }
        } else if (isdigit((unsigned char)magnitude[i])) {
            if (++ndigits > 6) {
                arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
                strcat(arg->value.label, " MORE than 6 digits!");
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
        strcat(arg->value.label, " ZERO digits!");
        return;
    }
    // 6. check conversion
    char* end;
    float m = strtof(magnitude, &end);
    if (*end != '\0') {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        return;
    }
    arg->type = DOPE_DATA_NUMBER;
    arg->error_code = DOPE_ERR_SUCCESS;
    strcpy(arg->value.label, "");
    arg->value.number = m;
}

void dope_parse_exp(dope_argument_t* arg, char* exponent) {
    // 0. null checks
    if (!exponent) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " NULL exponent token!");
        return;
    }
    // 1. no parse 0 size exponent or if invalid magnitude.
    if(
        strlen(exponent) == 0     // okay to default to +00 if empty exponent field 
        || arg->type == DOPE_DATA_INVALID
    ) {
        return;
    }
    arg->type = DOPE_DATA_INVALID; // assume invalid
    // 2. Check is a number
    if(!dope_is_number(exponent)) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " SIGN missing!");
        return;
    }
    // 3. Check correct length
    if(strlen(exponent) != 3) {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        strcat(arg->value.label, " SIZE exponent != 3!");
        return;
    }
    // 4. Process each exponent character after the sign
    for (int i = 1; i < 3; i++) {
        if (!isdigit((unsigned char)exponent[i])) {
            arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
            strcat(arg->value.label, " NOT a digit!");
            return;
        }
    }
    // 5. Check exponent range
    int e = atoi(exponent);
    if (e < -36 || e > 36)  {
        arg->error_code = DOPE_ERR_EXPONENT_OUT_OF_RANGE;
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
    return;
}

void dope_print_arg(dope_argument_t* arg) {
    printf("%i %f %s %i %s\n",
        arg->type,
        arg->value.number,
        arg->value.label,
        arg->error_code,
        dope_error_message(arg->error_code)
    );
}
