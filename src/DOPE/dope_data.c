#include "dope_data.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

dope_data_t* dope_new_data(uint8_t line_count) {
    dope_data_t* data = malloc(sizeof(dope_data_t));
    if(!data) {
        return NULL;
    }
    data->args = calloc(line_count, sizeof(dope_argument_t));
    if(!data->args) {
        free(data);
        return NULL;
    }
    data->si = 0;
    data->capacity = line_count;
    data->size = 0;
    return data;
}

void dope_free_data(dope_data_t* data) {
    if (data) {
        free(data->args);
        free(data);
    }
}

void dope_clear_arg(dope_argument_t* arg) {
    memset(arg, 0, sizeof(dope_argument_t));
}

// check dope_is_number before calling
void dope_parse_number(dope_argument_t* arg) {
    char* str = arg->value.label;
    arg->type = DOPE_DATA_INVALID;
    char num[DOPE_FIELD_SIZE];    // temp number string
    int i = 0;                    // number string char index
    char* end = NULL;             // strtod
    // 1. copy & skip if leading sign character
    if(*str == '+' || *str == '-') { // DOPE magnitude sign optional
        num[i++] = *str++;
    }
    // 2. copy over digits and any decimal point
    while(isdigit(*str) || *str == '.') {
        num[i++] = *str++;
    }
    // 3. skip end stop
    if(*str == DOPE_STOP) {    // DOPE number should have stop code every 5 chars
        str++;                 // but dope_parse_number is permissive
    }
    // 4. copy any remaining magnitude and optional exponent
    while(*str != DOPE_STOP && i < DOPE_FIELD_SIZE) {
        if(*str == '+' || *str == '-') {
            num[i++] = 'E';        // inject exponent char for strtod
            num[i++] = *str++;
        }
        else if(isdigit(*str)) {    // copy over any digits
            num[i++] = *str++;
        }
        else {
            arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
            return;
        }
    }
    // 5. zero terminate and convert to dope_float_t
    num[i] = '\0';
    arg->value.number = strtod(num, &end); // Watcom C did not implement strtof!
    // 6. strtod consumed nothing or stopped early
    if (end == num || *end != '\0') {
        arg->error_code = DOPE_ERR_INVALID_NUMBER_FORMAT;
        return;
    }
    arg->type = DOPE_DATA_NUMBER;
    arg->error_code = DOPE_ERR_SUCCESS;
}

void dope_parse_label(dope_argument_t* arg) {
    arg->type = DOPE_DATA_INVALID;
    // 1. locate the stop code '
    int i = strcspn(arg->value.label, DOPE_STOP_STR);
    // 2. no input
    if(i == 0) {
        arg->error_code = DOPE_ERR_NO_INPUT;
        return;
    }
    // 3. no stop code
    if(i == strlen(arg->value.label)) {
        arg->error_code = DOPE_ERR_MISSING_STOP_CODE;
        return;
    }
    // 4. terminate string at stop code
    arg->value.label[i] = '\0';
    // 5. detect data finish
    if(strcmp(arg->value.label, DOPE_FINISH_STR) == 0) {
        arg->type = DOPE_DATA_FINISH;
    }
    else {
        arg->type = DOPE_DATA_LABEL;
    }
    arg->error_code = DOPE_ERR_SUCCESS;
}

void dope_input_arg(dope_argument_t* arg, FILE* istream) {
    arg->type = DOPE_DATA_INVALID; // default to invalid
    // 1. read the line and catch truncated and invalid character errors
    uint8_t length = dope_read_line(&arg->value.label, istream);
    if(length == 0) {
        arg->error_code = DOPE_ERR_NO_INPUT;
        return;
    }
    if(dope_is_truncated(&arg->value.label)) {
        arg->error_code = DOPE_ERR_LINE_TOO_LONG;
        dope_consume_remaining(istream);
        return;
    }
    // 2. trim line
    arg->value.label[strcspn(arg->value.label, "\n")] = '\0';
    // 3. parse if number
    if(dope_is_number(arg->value.label)) {
        dope_parse_number(arg);
        return;
    }
    // 4. otherwise plain string
    dope_parse_label(arg);
    return;
}

void dope_input_data(dope_data_t* data, FILE* istream) {
    if (!data || !istream) {
        dope_panic(0, DOPE_ERR_NO_INPUT, "NULL data or file");
        return;
    }
    data->size = 0;
    while (data->size < data->capacity) {
        printf("%i ", data->size + 1);
        // 1. Parse next datum
        dope_input_arg(&data->args[data->size], istream);
        // 2. No input (EOF)
        if (data->args[data->size].error_code == DOPE_ERR_NO_INPUT) {
            dope_panic(data->size, data->args[data->size].error_code, "EOF without finish'");
            if(istream == stdin) {
                continue;
            }
            else break;
        }
        // 3. error
        if (data->args[data->size].type == DOPE_DATA_INVALID) {
            dope_panic(data->size, data->args[data->size].error_code, data->args[data->size].value.label);
            if(istream == stdin) continue;
            else break;
        }
        // 4. stop on finish' marker
        if (data->args[data->size].type == DOPE_DATA_FINISH) {
            data->size++;
            return;
        }
        // 5. valid datum
        data->size++;
    }
}

dope_line_t* dope_next_label(dope_data_t* data) {
    if(data->args[data->si].type != DOPE_DATA_LABEL) {
        dope_panic(data->si, DOPE_ERR_TYPE_MISMATCH, "(expected label type)");
        exit(EXIT_FAILURE);
    }
    return &data->args[data->si++].value.label;
}

dope_float_t* dope_next_number(dope_data_t* data) {
    return NULL;
}

void dope_print_raw_arg(dope_argument_t* arg, FILE* ostream) {
    fprintf(ostream, "%i %G >%s< E%i %s\n",
        arg->type,
        arg->value.number,
        arg->value.label,
        arg->error_code,
        dope_error_message(arg->error_code)
    );
}

void dope_print_data_line(dope_argument_t* arg, FILE* ostream) {
    switch((int)arg->type) {
    case DOPE_DATA_NUMBER:
        fprintf(ostream, "%G\n", arg->value.number);
        break;
    case DOPE_DATA_LABEL:
         fprintf(ostream, "%s\n", arg->value.label);
         break;
    case DOPE_DATA_FINISH:
        fprintf(ostream, "FINISH\n");
        break;
    case DOPE_DATA_INVALID:
    default:
        dope_panic(i + 1, arg->error_code, "");
   }
}

void dope_print_data(dope_data_t* data, FILE* ostream) {
    for(int i = 0; i < data->size; i++) {
        fprintf(ostream, "%i ", i + 1);
        dope_print_data_line(&data->args[i], ostream);
        switch((int)data->args[i].type) {
        case DOPE_DATA_NUMBER:
            fprintf(ostream, "%G\n",data->args[i].value.number);
            break;
        case DOPE_DATA_LABEL:
             fprintf(ostream, "%s\n",data->args[i].value.label);
             break;
        case DOPE_DATA_FINISH:
            fprintf(ostream, "FINISH\n");
            break;
        case DOPE_DATA_INVALID:
        default:
            dope_panic(i + 1, data->args[i].error_code, "");
       }
   }
   //fprintf(ostream, "size=%i capacity=%i\n",data->size, data->capacity);
}
