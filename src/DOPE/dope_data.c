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
    data->capacity = line_count;
    data->size = 0;
    data->si = 0;
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

bool dope_is_number(char* str) {
    return (*str == '+' || *str== '-' || !isdigit(*str));
}

// check dope_is_number before calling
void dope_parse_number(dope_argument_t* arg) {
    char* str = arg->value.label
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
            num[i++] = 'E';        // inject exponent char for strtod
            num[i++] = *str++;
        }
        else if (isdigit(*str)) {    // copy over any digits
            num[i++] = *str++;    
        }
        else {
            arg->error_code =DOPE_ERR_INVALID_NUMBER_FORMAT;
            return;
        }
    }
    // 5. zero terminate and convert to float
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

void dope_parse_label((dope_argument_t* arg) {
    arg->type = DOPE_DATA_INVALID;
    // 1. locate the stop code '
    int i = strcspn(arg->value.label, DOPE_STOP_STR)
    // 2. no stop code
    if(i == 0) { 
        arg->error_code = DOPE_ERR_MISSING_STOP_CODE;
    } 
    // 3. terminate string at stop code
    arg->label[i] = '\0'; 
    // 4. detect data finish 
    if(strcmp(arg->value.label, DOPE_FINISH_STR) == 0) {
        arg->type = DOPE_DATA_FINISH;
    }
    else {
        arg->type = DOPE_DATA_LABEL;
    }
    arg->error_code = DOPE_ERR_SUCCESS;
}

void dope_input_argument(dope_argument_t* arg, FILE* istream) {
    dope_clear_arg(arg);
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
    dope_parse_label
    return;
}

void dope_input_data(dope_data_t* data, FILE* istream) {
    if (!data || !stream) {
        dope_panic(0, DOPE_ERR_NO_INPUT, "NULL data or file");  
        return;
    }
    data->size = 0;
    while (data->size < data->capacity) {
        // 1. Parse next datum
        dope_input_arg(&data-args[data->size], stream);
        // 2. No input (EOF)
        if (data->args[data->size].error_code == DOPE_ERR_NO_INPUT) {
            dope_panic(data->size, data->args[data->size].error_code, "EOF without 'finish'");
            return;
        }
        // 3. error exit
        if (data->args[data->size].type == DOPE_DATA_INVALID) {
            dope_panic(data->size, data->args[data->size].error_code, "Invalid data");
            return;
        }
        // 4. stop on 'FINISH' marker
        if (data->args[data->size].type == DOPE_DATA_FINISH) {
            return;  
        }
        // 5. valid datum
        data->size++;
    }
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

void dope_print_data(dope_data_t* data) {
    for(int i = 0; i < data->size; i++) {
       printf("%i ", i + 1); // line number
       dope_print_arg(&data->args[i]);
   }
   printf("size=%i capacity=%i\n",data->size, data->capacity);
}
