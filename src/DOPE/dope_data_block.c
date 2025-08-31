#include "dope_data_block.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

bool dope_is_number(char* string) {
    return (*string == '+' || *string == '-');
}

void dope_parse_number(dope_argument_t* arg) {
    // 1. tokenize into magnitude and 10x exponent
    char* magnitude = strtok(arg->value.string, DOPE_DELIM_STR);
    char* exponent = strtok(NULL, DOPE_DELIM_STR);
    // 2. validate format
    int ndigits = 0;
    int npoints = 0;
    if (!magnitude || !exponent) {
        arg->type = DOPE_DATA_INVALID;
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        return;
    }
    // 3. Check minimum lengths and signs of magnitude and exponent
    if (
        strlen(magnitude) < 2
        || strlen(exponent) != 3
        || (magnitude[0] != '+' && magnitude[0] != '-')
        || (exponent[0] != '+' && exponent[0] != '-'))
    {
        arg->type = DOPE_DATA_INVALID;
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        return;
    }
    // 4. Process each magnitude character after the sign
    for (int i = 1; magnitude[i] != '\0'; i++) {
        if (magnitude[i] == '.') {
            if (++npoints > 1) {
                arg->type = DOPE_DATA_INVALID;
                arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
                return;
            }
        } else if (isdigit((unsigned char)magnitude[i])) {
            if (++ndigits > 6) {
                arg->type = DOPE_DATA_INVALID;
                arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
                return;
            }
        } else {
            arg->type = DOPE_DATA_INVALID;
            arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
            return;
        }
    }
    // 5. // Must have at least one digit
    if (ndigits == 0) {
        arg->type = DOPE_DATA_INVALID;
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        return;
    }
    // 6. Process each exponent character after the sign
    for (int i = 1; i < 3; i++) {
        if (!isdigit((unsigned char)exponent[i])) {
            arg->type = DOPE_DATA_INVALID;
            arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
            return;
        }
    }
    // 7. Check exponent range
    int e = atoi(exponent);
    if (e < -36 || e > 36)  {
        arg->type = DOPE_DATA_INVALID;
        arg->error_code = DOPE_ERR_EXPONENT_OUT_OF_RANGE;
    }
    // 8. Valid input (at last) parse and calculate
    char* end;
    float m = strtof(magnitude, &end);
    if (*end != '\0') {
        arg->type = DOPE_DATA_INVALID;
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        return;
    }
    arg->type = DOPE_DATA_NUMBER;
    arg->value.number = m * power_of_10(e);
}

void dope_input_argument(dope_argument_t* arg, FILE* istream) {
    dope_clear_data(arg);
    // 1. read the line and catch truncated and invalid character errors
    uint8_t length = dope_read_line(arg->value.string, istream);
    if(dope_is_truncated(arg->value.string)) {
        arg->error_code = DOPE_ERR_LINE_TOO_LONG;
        dope_consume_remaining(istream);
        return;
    }
    // 2. sanitize line
    arg->value.string[strcspn(arg->value.string, "\n")] = '\0';
    // 3. parse if number
    if(dope_is_number(&arg->value.string)) {
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
        arg->value.string,
        arg->error_code,dope_error_message(arg->error_code)
    );
}
