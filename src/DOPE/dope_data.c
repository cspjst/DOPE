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

void dope_clear_data(dope_argument_t* arg) {
    memset(arg, 0, sizeof(dope_argument_t));
}

bool dope_is_number(char* str) {
    return (*str == '+' || *str== '-' || !isdigit(*str));
}

// check dope_is_number before calling
float dope_parse_number(dope_argument_t* arg) {
    char* str = arg->value.label
    char num[12];        // temp number string
    int i = 0;           // number string char index 
    char* end = NULL;    // strtod 
    // 1. copy & skip if leading sign character
    if(*str == '+' || *str == '-') { // DOPE magnitude sign optional
        num[i++] = *str++;
    }
    // 2. copy over digits and any decimal point
    while(isdigit(*str) || *str == '.') {
        num[i++] = *str++;
    }
    // 3. skip end stop 
    if(*str == '\'') {    // DOPE number should have end stop every 5 chars
        str++;            // but dope_parse_number is permissive
    }
    // 3. copy any remaining magnitude and optional exponent
    while(*str != '\'' && i < 12) { // fix these magic numbers
        if(*str == '+' || *str == '-') { // DOPE exponent must contain sign
            num[i++] = 'E';        // inject exponent char for strtod
            num[i++] = *str++;
        }
        else if (isdigit(*str)) {    // copy over any digits
            num[i++] = *str++;    
        }
        else {
            // anything other character is an error
        }
    }
    n[i] = '\0';
    // do some error stuf with end it should point to ' 
    return strtod(n, &end); // Watcom C did not implement strtof!
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
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char s1[] = "5.234'56+11'";
char s2[] = "-1111'11-11'";
char s3[] = "12345'6+25'";
char n[11];

// check before calling if(*p != '+' && *p != '-' && !isdigit(*p))
double parse(char* p) {
    int i = 0;
    char* end = NULL;
    char n[11];
    if(*p == '+' || *p == '-') {
        n[i++] = *p++;
    }
    while(isdigit(*p) || *p == '.') {
        n[i++] = *p++;
    }
    if(*p == '\'') {
        p++;
    }
    while(*p != '\'' && i < 11) {
        if(*p == '+' || *p == '-') {
            n[i++] = 'E';
            n[i++] = *p++;
        }
        else {
            n[i++] = *p++;
        }
    }
    n[i] = '\0';
    return strtod(n, &end);
}


int main() {
    printf("%f\n", parse(s1));
    printf("%f\n", parse(s2));
    printf("%f\n", parse(s3));
    return 0;
} 
*/
